#include "CPU.h"
#include "Opcode.h"
#include <cstdint>
#include <stdexcept>

void Opcode::handle5XY0(uint16_t opcode, CPU &cpu)
{
    // TODO: Skip the following instruction if the value of register VX is equal to the value of register VY
    throw std::runtime_error("Unimplemented opcode (0x5XY0): " + std::to_string(opcode));
}