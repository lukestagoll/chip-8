#pragma once

#include "Memory.h"
#include "Display.h"

#include <cstdint>

class CPU {
public:
    static constexpr uint16_t PROGRAM_START_ADDRESS = 0x200;

    CPU(Memory &mem, Display &display);
    void cycle();
    void setDrawFlag(bool value) { draw_flag = value; }
    bool getDrawFlag() const { return draw_flag; }
    void setClearDisplayFlag(bool value) { clear_display_flag = value; }
    bool getClearDisplayFlag() const { return clear_display_flag; }

    void setVX(uint8_t index, uint8_t value) { V[index] = value; };
    void setI(uint16_t addr) { I = addr; };

private:
    Memory &memory;
    Display &display;
    
    uint8_t V[16];            // 16 8-bit registers

    uint16_t I;               // 16-bit index register
    uint16_t program_counter; // Program counter

    uint8_t delay_timer;      // Delay timer
    uint8_t sound_timer;      // Sound timer

    uint16_t stack[16];       // Stack for subroutine calls
    uint8_t stack_pointer;    // Stack pointer

    bool draw_flag = false;
    bool clear_display_flag = false;

    void
    initRegisters();
    void initStack();
};
