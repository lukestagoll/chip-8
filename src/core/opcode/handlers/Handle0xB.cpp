#include "CPU.h"
#include "Opcode.h"
#include <cstdint>
#include <stdexcept>

void Opcode::handleBNNN(uint16_t opcode, CPU &cpu)
{
    // TODO: Jump to address NNN + V0
    throw std::runtime_error("Unimplemented opcode (0xBNNN): " + std::to_string(opcode));
}