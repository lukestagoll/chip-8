#include "CPU.h"
#include "Opcode.h"
#include <cstdint>

CPUStatus Opcode::handle4XNN(uint16_t opcode, CPU &cpu)
{
    uint8_t index = (opcode >> 8) & 0xF;
    uint16_t value = opcode & 0xFF;
    if (cpu.notEqualsImmediate(index, value))
    {
        return cpu.skipNextInstruction();
    }
    return CPUStatus::OK;
}