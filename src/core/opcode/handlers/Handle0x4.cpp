#include "CPU.h"
#include "Opcode.h"
#include <cstdint>
#include <stdexcept>

void Opcode::handle4XNN(uint16_t opcode, CPU &cpu)
{
    // TODO: Skip the following instruction if the value of register VX is not equal to NN
    throw std::runtime_error("Unimplemented opcode (0x4XNN): " + std::to_string(opcode));
}