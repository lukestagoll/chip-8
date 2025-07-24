#include "CPU.h"
#include "Opcode.h"
#include <cstdint>

// skips next instruction if V[X] == NN
void Opcode::handle3XNN(uint16_t opcode, CPU &cpu)
{
    uint8_t index = (opcode >> 8) & 0xF;
    uint16_t value = opcode & 0xFF;
    if (cpu.equalsImmediate(index, value))
    {
        cpu.skipNextInstruction();
    }
}