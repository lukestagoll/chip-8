#include "Opcode.h"

CPUStatus Opcode::execute(uint16_t opcode, CPU &cpu)
{
    switch (opcode & 0xF000)
    {
        case 0x0000: return handle0x0(opcode, cpu);
        case 0x1000: return handle1NNN(opcode, cpu);
        case 0x2000: return handle2NNN(opcode, cpu);
        case 0x3000: return handle3XNN(opcode, cpu);
        case 0x4000: return handle4XNN(opcode, cpu);
        case 0x5000: return handle5XY0(opcode, cpu);
        case 0x6000: return handle6XNN(opcode, cpu);
        case 0x7000: return handle7XNN(opcode, cpu);
        case 0x8000: return handle0x8(opcode, cpu);
        case 0x9000: return handle9XY0(opcode, cpu);
        case 0xA000: return handleANNN(opcode, cpu);
        case 0xB000: return handleBNNN(opcode, cpu);
        case 0xC000: return handleCXNN(opcode, cpu);
        case 0xD000: return handleDXYN(opcode, cpu);
        case 0xE000: return handle0xE(opcode, cpu);
        case 0xF000: return handle0xF(opcode, cpu);
        default:     return cpu.unknownOperation(opcode);
    }
}