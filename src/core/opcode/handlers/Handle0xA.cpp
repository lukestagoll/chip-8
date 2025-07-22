#include "CPU.h"
#include "Opcode.h"
#include <cstdint>
#include <stdexcept>

void Opcode::handleANNN(uint16_t opcode, CPU &cpu)
{
    // TODO: Store memory address NNN in register I
    throw std::runtime_error("Unimplemented opcode (0xANNN): " + std::to_string(opcode));
}