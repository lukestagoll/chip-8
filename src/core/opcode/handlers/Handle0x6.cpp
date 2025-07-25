#include "CPU.h"
#include "Opcode.h"
#include <cstdint>

CPUStatus Opcode::handle6XNN(uint16_t opcode, CPU &cpu)
{
    uint8_t index = (opcode >> 8) & 0x0F;
    uint8_t value = opcode & 0x00FF;

    return cpu.setV(index, value);
}