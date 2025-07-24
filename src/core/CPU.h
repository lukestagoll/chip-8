#pragma once

#include "Memory.h"
#include "Display.h"

#include <array>
#include <cstdint>

class CPU {
public:
    static constexpr uint16_t PROGRAM_START_ADDRESS = 0x200;
    static constexpr std::size_t NUM_REGISTERS = 16;
    static constexpr std::size_t STACK_DEPTH = 16;
    static constexpr uint8_t VF = 0xF;

    CPU(Memory &memory, Display &display);

    // --- Program Control / Flow Execution ---
    void cycle();
    void callSubroutine(uint16_t address);
    void exitSubroutine();
    void skipNextInstruction() { programCounter += 2; }
    void jump(uint16_t address) { programCounter = address; }

    // --- Display Operations ---
    void clearDrawFlag() { display.clearDrawFlag(); }
    bool getDrawFlag() const { return display.getDrawFlag(); }
    void clearDisplay() { display.clear(); }
    void drawSprite(uint8_t vx, uint8_t vy, uint8_t n);
    
    // --- General-purpose Register Access ---
    uint8_t getV(uint8_t index) const { return V[index]; }
    void setV(uint8_t index, uint8_t value) { V[index] = value; }
    void assignV(uint8_t x, uint8_t y) { V[x] = V[y]; }
    void setVF(uint8_t value) { V[VF] = value; }
    void setIndexRegister(uint16_t addr) { indexRegister = addr; }

    // --- Arithmetic and Logic Instructions ---
    void addImmediate(uint8_t index, uint8_t value) { V[index] += value; }
    void addRegisters(uint8_t x, uint8_t y);
    void subtractRegisters(uint8_t x, uint8_t y);
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


private:
    Memory &memory;
    Display &display;

    // Registers
    std::array<uint8_t, NUM_REGISTERS> V{}; // 16 8-bit registers
    uint16_t indexRegister = 0;     // I register
    uint16_t programCounter = PROGRAM_START_ADDRESS;

    // Timers
    uint8_t delayTimer = 0;
    uint8_t soundTimer = 0;

    // Subroutine Stack
    std::array<uint16_t, STACK_DEPTH> stack{};
    uint8_t stackPointer = 0;
};
