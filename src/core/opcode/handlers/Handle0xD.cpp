#include "CPU.h"
#include "Opcode.h"
#include <cstdint>

void Opcode::handleDXYN(uint16_t opcode, CPU &cpu)
{
    uint8_t vx = opcode >> 8 & 0xF;
    uint8_t vy = opcode >> 4 & 0xF;
    uint8_t n = opcode & 0xF;

    cpu.drawSprite(vx, vy, n);
}