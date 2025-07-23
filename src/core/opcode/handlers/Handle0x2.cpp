#include "CPU.h"
#include "Opcode.h"
#include <cstdint>

// execute subroutine at NNN
void Opcode::handle2NNN(uint16_t opcode, CPU &cpu)
{
    uint16_t address = opcode & 0x0FFF;
    cpu.callSubroutine(address);
}