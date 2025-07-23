#include "CPU.h"
#include "Opcode.h"
#include <cstdint>

// jumps to address: NNN
void Opcode::handle1NNN(uint16_t opcode, CPU &cpu)
{
    uint16_t address = opcode & 0x0FFF;
    cpu.jump(address);
}