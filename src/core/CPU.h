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
    void clearDrawFlag() { display.clearDrawFlag(); }
    bool getDrawFlag() const { return display.getDrawFlag(); }
    void skipNextInstruction() { programCounter += 2; }

    void setV(uint8_t index, uint8_t value) { V[index] = value; };
    void addV(uint8_t index, uint8_t value) { V[index] += value; };
    bool compareVXVY(uint8_t x, uint8_t y) { return V[x] == V[y]; };
    bool vEquals(uint8_t index, uint8_t value) { return V[index] == value; };
    bool vNotEquals(uint8_t index, uint8_t value) { return V[index] != value; };

    void setVF(uint8_t value) { V[15] = value; };
    void setIndexRegister(uint16_t addr) { indexRegister = addr; };

    void drawSprite(uint8_t vx, uint8_t vy, uint8_t n);
    void clearDisplay() { display.clear(); }

    void jump(uint16_t address) { programCounter = address; }

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

    void initRegisters();
    void initStack();
};
