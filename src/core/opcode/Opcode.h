#pragma once

#include "CPU.h"

namespace Opcode {
    CPUStatus execute(uint16_t opcode, CPU &cpu);

    // handles 00E0, 00EE
    CPUStatus handle0x0(uint16_t opcode, CPU &cpu);

    // handles 1NNN
    CPUStatus handle1NNN(uint16_t opcode, CPU &cpu);

    // handles 2NNN
    CPUStatus handle2NNN(uint16_t opcode, CPU &cpu);

    // handles 3XNN
    CPUStatus handle3XNN(uint16_t opcode, CPU &cpu);

    // handles 4XNN
    CPUStatus handle4XNN(uint16_t opcode, CPU &cpu);

    // handles 5XY0
    CPUStatus handle5XY0(uint16_t opcode, CPU &cpu);

    // handles 6XNN
    CPUStatus handle6XNN(uint16_t opcode, CPU &cpu);

    // handles 7XNN
    CPUStatus handle7XNN(uint16_t opcode, CPU &cpu);

    // handles 8XY0, 8XY1, 8XY2, 8XY3, 8XY4, 8XY5, 8XY6, 8XY7, 8XYE
    CPUStatus handle0x8(uint16_t opcode, CPU &cpu);

    // handles 9XY0
    CPUStatus handle9XY0(uint16_t opcode, CPU &cpu);

    // handles ANNN
    CPUStatus handleANNN(uint16_t opcode, CPU &cpu);

    // handles BNNN
    CPUStatus handleBNNN(uint16_t opcode, CPU &cpu);

    // handles CXNN
    CPUStatus handleCXNN(uint16_t opcode, CPU &cpu);

    // handles DXYN
    CPUStatus handleDXYN(uint16_t opcode, CPU &cpu);

    // handles EX9E, EXA1
    CPUStatus handle0xE(uint16_t opcode, CPU &cpu);

    // handles FX07, FX0A, FX15, FX18, FX1E, FX29, FX33, FX55, FX65
    CPUStatus handle0xF(uint16_t opcode, CPU &cpu);
}