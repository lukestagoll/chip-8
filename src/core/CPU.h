#pragma once

#include "Memory.h"
#include "Display.h"

#include <array>
#include <cstdint>

class CPU {
public:
    static constexpr uint16_t PROGRAM_START_ADDRESS = 0x200;

    CPU(Memory &mem, Display &display);
    void cycle();
    void setDrawFlag(bool value) { drawFlag = value; }
    bool getDrawFlag() const { return drawFlag; }
    void setClearDisplayFlag(bool value) { clearDisplayFlag = value; }
    bool getClearDisplayFlag() const { return clearDisplayFlag; }

    void setVX(uint8_t index, uint8_t value) { V[index] = value; };
    void setI(uint16_t addr) { indexRegister = addr; };

private:
    Memory &memory;
    Display &display;
    
    std::array<uint8_t, 16> V; // 16 8-bit registers

    uint16_t indexRegister;  // 16-bit index register
    uint16_t programCounter; // Program counter

    uint8_t delayTimer;      // Delay timer
    uint8_t soundTimer;      // Sound timer

    std::array<uint16_t, 16> stack; // Stack for subroutine calls

    uint8_t stackPointer;    // Stack pointer

    bool drawFlag = false;
    bool clearDisplayFlag = false;

    void
    initRegisters();
    void initStack();
};
