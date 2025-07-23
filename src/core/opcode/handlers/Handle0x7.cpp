#include "CPU.h"
#include "Opcode.h"
#include <cstdint>

// adds value NN to register VX
void Opcode::handle7XNN(uint16_t opcode, CPU &cpu)
{
    uint8_t index = (opcode >> 8) & 0xF;
    uint16_t value = opcode & 0xFF;
    cpu.addV(index, value);
}