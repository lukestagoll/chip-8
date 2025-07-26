#include "CPU.h"
#include "Opcode.h"
#include <cstdint>

CPUStatus Opcode::handleANNN(uint16_t opcode, CPU &cpu)
{
    uint16_t addr = opcode & 0x0FFF;
    return cpu.setIndexRegister(addr);
}