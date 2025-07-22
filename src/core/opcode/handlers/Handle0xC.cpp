#include "CPU.h"
#include "Opcode.h"
#include <cstdint>
#include <stdexcept>

void Opcode::handleCXNN(uint16_t opcode, CPU &cpu)
{
    // TODO: Set VX to a random number with a mask of NN
    throw std::runtime_error("Unimplemented opcode (0xCXNN): " + std::to_string(opcode));
}