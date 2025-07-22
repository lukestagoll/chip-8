#pragma once

#include "CPU.h"
#include "Memory.h"

namespace Opcode {
    void execute(uint16_t opcode, CPU &cpu, Memory &memory);

    // handles 00E0, 00EE
    void handle0x0(uint16_t opcode, CPU &cpu);

    // handles 1NNN
    void handle1NNN(uint16_t opcode, CPU &cpu);

    // handles 2NNN
    void handle2NNN(uint16_t opcode, CPU &cpu);

    // handles 3XNN
    void handle3XNN(uint16_t opcode, CPU &cpu);

    // handles 4XNN
    void handle4XNN(uint16_t opcode, CPU &cpu);

    // handles 5XY0
    void handle5XY0(uint16_t opcode, CPU &cpu);

    // handles 6XNN
    void handle6XNN(uint16_t opcode, CPU &cpu);

    // handles 7XNN
    void handle7XNN(uint16_t opcode, CPU &cpu);

    // handles 8XY0, 8XY1, 8XY2, 8XY3, 8XY4, 8XY5, 8XY6, 8XY7, 8XYE
    void handle0x8(uint16_t opcode, CPU &cpu);

    // handles 9XY0
    void handle9XY0(uint16_t opcode, CPU &cpu);

    // handles ANNN
    void handleANNN(uint16_t opcode, CPU &cpu);

    // handles BNNN
    void handleBNNN(uint16_t opcode, CPU &cpu);

    // handles CXNN
    void handleCXNN(uint16_t opcode, CPU &cpu);

    // handles DXYN
    void handleDXYN(uint16_t opcode, CPU &cpu);

    // handles EX9E, EXA1
    void handle0xE(uint16_t opcode, CPU &cpu);

    // handles FX07, FX0A, FX15, FX18, FX1E, FX29, FX33, FX55, FX65
    void handle0xF(uint16_t opcode, CPU &cpu);
}