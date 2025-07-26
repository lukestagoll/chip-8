#include "CPU.h"
#include "Opcode.h"
#include <cstdint>

CPUStatus Opcode::handle0x0(uint16_t opcode, CPU &cpu)
{
    switch (opcode)
    {
    case 0x00E0: return cpu.clearDisplay();
    case 0x00EE: return cpu.exitSubroutine();
    default:     return cpu.unknownOperation(opcode);
    }
}
