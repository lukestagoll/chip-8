#pragma once

#include "Memory.h"

#include <cstdint>

#define PROGRAM_START_ADDRESS 0x200

class CPU {
public:
    CPU();
    void attachMemory(Memory* mem) { memory = mem; }
    void cycle();

private:
    Memory *memory;
    
    uint8_t V[16]; // 16 8-bit registers

    uint16_t I;               // 16-bit index register
    uint16_t program_counter; // Program counter

    uint8_t delay_timer; // Delay timer
    uint8_t sound_timer; // Sound timer

    uint16_t stack[16];    // Stack for subroutine calls
    uint8_t stack_pointer; // Stack pointer

    void initRegisters();
    void initStack();
};
