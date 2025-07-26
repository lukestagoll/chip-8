#include "CPU.h"
#include "Opcode.h"
#include <cstdint>

CPUStatus Opcode::handleCXNN(uint16_t opcode, CPU &cpu)
{
    uint8_t x = (opcode & 0x0F00) >> 8;
    uint8_t nn = opcode & 0x00FF;
    return cpu.random(x, nn);
}