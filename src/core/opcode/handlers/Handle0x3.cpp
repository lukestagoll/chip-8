#include "CPU.h"
#include "Opcode.h"
#include <cstdint>
#include <stdexcept>

void Opcode::handle3XNN(uint16_t opcode, CPU &cpu)
{
    // TODO: Skip the following instruction if the value of register VX equals NN
    throw std::runtime_error("Unimplemented opcode (0x3XNN): " + std::to_string(opcode));
}