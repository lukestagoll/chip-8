#pragma once

#include "Chip8Display.h"
#include "Keypad.h"
#include "Memory.h"
#include "Timer.h"
#include "CPUStatus.h"

#include <array>
#include <cstdint>
#include <cstdlib>

class CPU {
public:
    static constexpr uint16_t PROGRAM_START_ADDRESS = 0x200;
    static constexpr std::size_t NUM_REGISTERS = 16;
    static constexpr std::size_t STACK_DEPTH = 16;
    static constexpr uint8_t VF = 0xF;

    CPU(Memory &memory, Chip8Display &display, Timer &delayTimer, Timer &soundTimer, Keypad &keypad);

    // --- Program Control / Flow Execution ---

    /**
     * Executes one CPU cycle of the fetch-decode-execute process.
     * 1. Fetches a 16-bit instruction from memory at the current program counter
     * 2. Increments program counter by 2 bytes
     * 3. Decodes and executes the instruction via the Opcode handler
     *
     * @throws std::runtime_error if program counter exceeds memory bounds
     */
    CPUStatus cycle();

    /**
     * Calls a subroutine at the specified address.
     * Pushes the current program counter onto the stack and jumps to the target address.
     *
     * @param address The memory address to jump to
     * @throws std::overflow_error if the call stack is full (16 levels deep)
     */
    CPUStatus callSubroutine(uint16_t address);

    /**
     * Returns from a subroutine by restoring the program counter from the stack.
     * Pops the return address from the top of the stack.
     *
     * @throws std::underflow_error if attempting to return when stack is empty
     */
    CPUStatus exitSubroutine();
    CPUStatus skipNextInstruction() { programCounter_ += 2; return CPUStatus::OK; }
    CPUStatus jump(uint16_t address) { programCounter_ = address; return CPUStatus::OK; }
    CPUStatus jumpV(uint16_t address) { programCounter_ = address + V_[0]; return CPUStatus::OK; }

    // --- Display Operations ---
    bool getDrawFlag() const { return display_.getDrawFlag(); }
    CPUStatus clearDrawFlag() { display_.clearDrawFlag(); return CPUStatus::OK; }
    CPUStatus clearDisplay() { display_.clear(); return CPUStatus::OK; }

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
    CPUStatus drawSprite(uint8_t vx, uint8_t vy, uint8_t n);
    
    // --- General-purpose Register Access ---
    uint8_t getV(uint8_t index) const { return V_[index]; }
    CPUStatus setV(uint8_t index, uint8_t value) { V_[index] = value; return CPUStatus::OK; }

    /**
     * Stores the value of the second register in the first register
     * VX = VY
     *
     * @param x Target register index (result stored here)
     * @param y Source register index to copy
     */
    CPUStatus copyRegister(uint8_t x, uint8_t y) { V_[x] = V_[y]; return CPUStatus::OK; }
    CPUStatus setVF(uint8_t value) { V_[VF] = value; return CPUStatus::OK; }
    CPUStatus setIndexRegister(uint16_t addr) { indexRegister_ = addr; return CPUStatus::OK; }
    CPUStatus setIndexRegisterFromV(uint16_t index) { indexRegister_ = 0x050 + (V_[index] * 5); return CPUStatus::OK; }

    // --- Arithmetic and Logic Instructions ---
    CPUStatus addImmediate(uint8_t index, uint8_t value) { V_[index] += value; return CPUStatus::OK; }

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
    CPUStatus addRegisters(uint8_t x, uint8_t y);

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
    CPUStatus subtractRegisters(uint8_t x, uint8_t y);

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
    CPUStatus subtractReversed(uint8_t x, uint8_t y);

    CPUStatus shiftRight(uint8_t index);
    CPUStatus shiftLeft(uint8_t index);

    CPUStatus bitwiseOR(uint8_t x, uint8_t y) { V_[x] |= V_[y]; return CPUStatus::OK; }
    CPUStatus bitwiseXOR(uint8_t x, uint8_t y) { V_[x] ^= V_[y]; return CPUStatus::OK; }
    CPUStatus bitwiseAND(uint8_t x, uint8_t y) { V_[x] &= V_[y]; return CPUStatus::OK; }

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
    CPUStatus loadRegistersFromMemory(uint8_t index);

    /**
     * Stores values from registers V0 through VX (inclusive) into memory starting from the address stored in the index register.
     *
     * Does NOT modify the address stored in the index register (I) - consistency with modern interpreters.
     *
     * @param index The highest register index to save (inclusive).
     */
    CPUStatus saveRegistersToMemory(uint8_t index);

    /**
     * Store the binary encoded decimal (BCD) at VX in memory at I, I + 1, I + 2.
     *
     * For example, if VX = 123, set mem[I] = 1, mem[I+1] = 2, mem[I+2] = 2
     *
     * @param index The index of the register to encode.
     */
    CPUStatus writeBCDToMemory(uint8_t index);

    /**
     * Add the value of the register at VX to I.
     * 
     * I += VX
     *
     * @param index The index of the register to add.
     */
    CPUStatus addRegisterToIndex(uint8_t index);

    // --- Timer Operations ---
    CPUStatus storeDelay(uint8_t index) { V_[index] = delayTimer_.get(); return CPUStatus::OK; }
    CPUStatus setDelayTimer(uint8_t index) { delayTimer_.set(V_[index]); return CPUStatus::OK; }
    CPUStatus setSoundTimer(uint8_t index) { soundTimer_.set(V_[index]); return CPUStatus::OK; }

    // --- Keypad ---
    bool isKeyPressed(uint8_t index) { return keypad_.isPressed(V_[index]); }
    CPUStatus waitForKeyPress(uint8_t index);
    bool waiting();

    CPUStatus random(uint8_t x, uint8_t nn) { V_[x] = (rand() % 256) & nn; return CPUStatus::OK; }

    // --- Error Handling ---
    CPUStatus unknownOperation(uint8_t opcode);

    void init();

  private:
    Memory &memory_;
    Chip8Display &display_;
    Timer &delayTimer_;
    Timer &soundTimer_;
    Keypad &keypad_;

    // Registers
    std::array<uint8_t, NUM_REGISTERS> V_{}; // 16 8-bit registers
    uint16_t indexRegister_ = 0;     // I register
    uint16_t programCounter_ = PROGRAM_START_ADDRESS;

    // Subroutine Stack
    std::array<uint16_t, STACK_DEPTH> stack_{};
    uint8_t stackPointer_= 0;

    bool waitingForKeyPress_ = false;
    uint8_t waitingForKeyRelease_ = 0xFF;
};
