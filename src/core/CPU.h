#pragma once

#include "Display.h"
#include "Keypad.h"
#include "Memory.h"
#include "Timer.h"

#include <array>
#include <cstdint>
#include <cstdlib>

class CPU {
public:
    static constexpr uint16_t PROGRAM_START_ADDRESS = 0x200;
    static constexpr std::size_t NUM_REGISTERS = 16;
    static constexpr std::size_t STACK_DEPTH = 16;
    static constexpr uint8_t VF = 0xF;

    CPU(Memory &memory, Display &display, Timer &delayTimer, Timer &soundTimer, Keypad &keypad);

    // --- Program Control / Flow Execution ---

    /**
     * Executes one CPU cycle of the fetch-decode-execute process.
     * 1. Fetches a 16-bit instruction from memory at the current program counter
     * 2. Increments program counter by 2 bytes
     * 3. Decodes and executes the instruction via the Opcode handler
     *
     * @throws std::runtime_error if program counter exceeds memory bounds
     */
    void cycle();

    /**
     * Calls a subroutine at the specified address.
     * Pushes the current program counter onto the stack and jumps to the target address.
     *
     * @param address The memory address to jump to
     * @throws std::overflow_error if the call stack is full (16 levels deep)
     */
    void callSubroutine(uint16_t address);

    /**
     * Returns from a subroutine by restoring the program counter from the stack.
     * Pops the return address from the top of the stack.
     *
     * @throws std::underflow_error if attempting to return when stack is empty
     */
    void exitSubroutine();
    void skipNextInstruction() { programCounter += 2; }
    void jump(uint16_t address) { programCounter = address; }
    void jumpV(uint16_t address) { programCounter = address + V[0]; }

    // --- Display Operations ---
    void clearDrawFlag() { display.clearDrawFlag(); }
    bool getDrawFlag() const { return display.getDrawFlag(); }
    void clearDisplay() { display.clear(); }

    /**
     * Draws a sprite at the specified screen coordinates.
     * Sprites are 8 pixels wide and N pixels tall, using XOR drawing mode.
     * Screen coordinates wrap around if they exceed display boundaries.
     *
     * @param vx Register index containing X coordinate
     * @param vy Register index containing Y coordinate
     * @param n Height of the sprite in pixels (1-15)
     *
     * Sets VF register:
     * - 1 if any pixels were erased (collision detected)
     * - 0 if no pixels were erased
     */
    void drawSprite(uint8_t vx, uint8_t vy, uint8_t n);
    
    // --- General-purpose Register Access ---
    uint8_t getV(uint8_t index) const { return V[index]; }
    void setV(uint8_t index, uint8_t value) { V[index] = value; }

    /**
     * Stores the value of the second register in the first register
     * VX = VY
     *
     * @param x Target register index (result stored here)
     * @param y Source register index to copy
     */
    void copyRegister(uint8_t x, uint8_t y) { V[x] = V[y]; }
    void setVF(uint8_t value) { V[VF] = value; }
    void setIndexRegister(uint16_t addr) { indexRegister = addr; }
    void setIndexRegisterFromV(uint16_t index) { indexRegister = 0x050 + (V[index] * 5); }

    // --- Arithmetic and Logic Instructions ---
    void addImmediate(uint8_t index, uint8_t value) { V[index] += value; }

    /**
     * Adds the values of two registers and stores the result in the first register.
     * Sets the carry flag (VF) if the result overflows 8 bits.
     *
     * VX += VY
     *
     * @param x Target register index (result stored here)
     * @param y Source register index to add
     *
     * Sets VF register:
     * - 1 if addition overflows (sum > 255)
     * - 0 if no overflow occurs
     */
    void addRegisters(uint8_t x, uint8_t y);

    /**
     * Subtracts register Y from register X and stores the result in register X.
     * Sets the borrow flag (VF) based on whether a borrow occurred.
     *
     * VX -= VY
     *
     * @param x Target register index (minuend, result stored here)
     * @param y Source register index (subtrahend)
     *
     * Sets VF register:
     * - 1 if no borrow (VX >= VY)
     * - 0 if borrow occurred (VX < VY)
     */
    void subtractRegisters(uint8_t x, uint8_t y);

    /**
     * Subtracts register X from register Y and stores the result in register X.
     * This is the reverse of subtractRegisters.
     * 
     * VX = VY - VX
     *
     * @param x Target register index (result stored here)
     * @param y Source register index (minuend)
     *
     * Sets VF register:
     * - 1 if no borrow (VY >= VX)
     * - 0 if borrow occurred (VY < VX)
     */
    void subtractReversed(uint8_t x, uint8_t y);

    void shiftRight(uint8_t index);
    void shiftLeft(uint8_t index);

    void bitwiseOR(uint8_t x, uint8_t y) { V[x] |= V[y]; }
    void bitwiseXOR(uint8_t x, uint8_t y) { V[x] ^= V[y]; }
    void bitwiseAND(uint8_t x, uint8_t y) { V[x] &= V[y]; }

    // --- Comparison ---
    bool equalsRegisters(uint8_t x, uint8_t y) const;
    bool equalsImmediate(uint8_t index, uint8_t value) const;
    bool notEqualsImmediate(uint8_t index, uint8_t value) const;

    // --- Memory Operations ---
    /**
     * Loads values from memory starting from the address stored in the index register into registers V0 through VX (inclusive).
     *
     * Does NOT modify the address stored in the index register (I) - consistency with modern interpreters.
     *
     * @param index The highest register index to load (inclusive).
     */
    void loadRegistersFromMemory(uint8_t index);

    /**
     * Stores values from registers V0 through VX (inclusive) into memory starting from the address stored in the index register.
     *
     * Does NOT modify the address stored in the index register (I) - consistency with modern interpreters.
     *
     * @param index The highest register index to save (inclusive).
     */
    void saveRegistersToMemory(uint8_t index);

    /**
     * Store the binary encoded decimal (BCD) at VX in memory at I, I + 1, I + 2.
     *
     * For example, if VX = 123, set mem[I] = 1, mem[I+1] = 2, mem[I+2] = 2
     *
     * @param index The index of the register to encode.
     */
    void writeBCDToMemory(uint8_t index);

    /**
     * Add the value of the register at VX to I.
     * 
     * I += VX
     *
     * @param index The index of the register to add.
     */
    void addRegisterToIndex(uint8_t index);

    // --- Timer Operations ---
    void storeDelay(uint8_t index) { V[index] = delayTimer.get(); }
    void setDelayTimer(uint8_t index) { delayTimer.set(V[index]); }
    void setSoundTimer(uint8_t index) { soundTimer.set(V[index]); }

    // --- Keypad ---
    bool isKeyPressed(uint8_t index) { return keypad.isPressed(V[index]); }
    void waitForKeyPress(uint8_t index);
    bool waiting();

    void random(uint8_t x, uint8_t nn) { V[x] = (rand() % 256) & nn; }

private:
    Memory &memory;
    Display &display;
    Timer &delayTimer;
    Timer &soundTimer;
    Keypad &keypad;

    // Registers
    std::array<uint8_t, NUM_REGISTERS> V{}; // 16 8-bit registers
    uint16_t indexRegister = 0;     // I register
    uint16_t programCounter = PROGRAM_START_ADDRESS;

    // Subroutine Stack
    std::array<uint16_t, STACK_DEPTH> stack{};
    uint8_t stackPointer = 0;

    bool waitingForKeyPress = false;
    uint8_t waitingForKeyRelease = 0xFF;
};
