#include "CPU.h"
#include "Opcode.h"
#include <cstdint>

// skips the next instruction if V[X] == v[Y]
CPUStatus Opcode::handle5XY0(uint16_t opcode, CPU &cpu)
{
    uint8_t x = (opcode >> 8) & 0xF;
    uint8_t y = (opcode >> 4) & 0xF;
    if (cpu.equalsRegisters(x, y))
    {
        return cpu.skipNextInstruction();
    }
    return CPUStatus::OK;
}
