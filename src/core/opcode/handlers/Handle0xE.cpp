#include "CPU.h"
#include "Opcode.h"
#include <cstdint>

CPUStatus Opcode::handle0xE(uint16_t opcode, CPU &cpu)
{
    uint8_t x = (opcode >> 8) & 0xF;
    switch (opcode & 0xF0FF)
    {
    case 0xE09E:
        if (cpu.isKeyPressed(x)) return cpu.skipNextInstruction();
        return CPUStatus::OK;
    case 0xE0A1:
        if (!cpu.isKeyPressed(x)) return cpu.skipNextInstruction();
        return CPUStatus::OK;
    default:
        return cpu.unknownOperation(opcode);
    }
}