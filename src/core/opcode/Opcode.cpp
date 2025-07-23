#include "Opcode.h"
#include <stdexcept>

void Opcode::execute(uint16_t opcode, CPU &cpu)
{
    switch (opcode & 0xF000)
    {
        case 0x0000:
            handle0x0(opcode, cpu);
            break;
        case 0x1000:
            handle1NNN(opcode, cpu);
            break;
        case 0x2000:
            handle2NNN(opcode, cpu);
            break;
        case 0x3000:
            handle3XNN(opcode, cpu);
            break;
        case 0x4000:
            handle4XNN(opcode, cpu);
            break;
        case 0x5000:
            handle5XY0(opcode, cpu);
            break;
        case 0x6000:
            handle6XNN(opcode, cpu);
            break;
        case 0x7000:
            handle7XNN(opcode, cpu);
            break;
        case 0x8000:
            handle0x8(opcode, cpu);
            break;
        case 0x9000:
            handle9XY0(opcode, cpu);
            break;
        case 0xA000:
            handleANNN(opcode, cpu);
            break;
        case 0xB000:
            handleBNNN(opcode, cpu);
            break;
        case 0xC000:
            handleCXNN(opcode, cpu);
            break;
        case 0xD000:
            handleDXYN(opcode, cpu);
            break;
        case 0xE000:
            handle0xE(opcode, cpu);
            break;
        case 0xF000:
            handle0xF(opcode, cpu);
            break;
        default:
            throw std::runtime_error("Unknown opcode: " + std::to_string(opcode));
    }
}