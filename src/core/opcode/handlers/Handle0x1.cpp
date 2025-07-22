#include "CPU.h"
#include "Opcode.h"
#include <cstdint>
#include <stdexcept>

void Opcode::handle1NNN(uint16_t opcode, CPU &cpu)
{
    // TODO: Jump to address NNN
    throw std::runtime_error("Unimplemented opcode (0x1NNN): " + std::to_string(opcode));
}