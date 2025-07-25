#include "CPU.h"
#include "Opcode.h"
#include <cstdint>
#include <stdexcept>

void Opcode::handle0xE(uint16_t opcode, CPU &cpu)
{
    uint8_t x = (opcode >> 8) & 0xF;
    switch (opcode & 0xF0FF)
    {
    case 0xE09E:
        if (cpu.isKeyPressed(x))
        {
            cpu.skipNextInstruction();
        }
        break;
    case 0xE0A1:
        if (!cpu.isKeyPressed(x))
        {
            cpu.skipNextInstruction();
        }
        break;
    default:
        throw std::runtime_error("Unknown opcode: " + std::to_string(opcode));
    }
}