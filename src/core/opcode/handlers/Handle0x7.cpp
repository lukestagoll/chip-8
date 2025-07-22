#include "CPU.h"
#include "Opcode.h"
#include <cstdint>
#include <stdexcept>

void Opcode::handle7XNN(uint16_t opcode, CPU &cpu)
{
    // TODO: Add the value NN to register VX
    throw std::runtime_error("Unimplemented opcode (0x7XNN): " + std::to_string(opcode));
}