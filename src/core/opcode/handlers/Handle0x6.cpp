#include "CPU.h"
#include "Opcode.h"
#include <cstdint>
#include <stdexcept>

void Opcode::handle6XNN(uint16_t opcode, CPU &cpu)
{
    // TODO: Store number NN in register VX
    throw std::runtime_error("Unimplemented opcode (0x6XNN): " + std::to_string(opcode));
}