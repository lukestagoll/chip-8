#include "CPU.h"
#include "Opcode.h"
#include <cstdint>
#include <stdexcept>

void Opcode::handle2NNN(uint16_t opcode, CPU &cpu)
{
    // TODO: Execute subroutine starting at address NNN
    throw std::runtime_error("Unimplemented opcode (0x2NNN): " + std::to_string(opcode));
}