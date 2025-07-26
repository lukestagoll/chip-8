#include "CPU.h"
#include "Opcode.h"
#include <cstdint>

CPUStatus Opcode::handleBNNN(uint16_t opcode, CPU &cpu)
{
    uint16_t address = opcode & 0x0FFF;
    return cpu.jumpV(address);
}