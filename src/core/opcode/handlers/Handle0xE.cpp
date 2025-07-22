#include "CPU.h"
#include "Opcode.h"
#include <cstdint>
#include <stdexcept>

void Opcode::handle0xE(uint16_t opcode, CPU &cpu)
{
    switch (opcode & 0xF0FF)
    {
    case 0xE09E:
        // TODO: Skip the following instruction if the key corresponding to the hex value currently stored in register VX is pressed
        throw std::runtime_error("Unimplemented opcode (0xEX9E): " + std::to_string(opcode));
    case 0xE0A1:
        // TODO: Skip the following instruction if the key corresponding to the hex value currently stored in register VX is not pressed
        throw std::runtime_error("Unimplemented opcode (0xEXA1): " + std::to_string(opcode));
    default:
        throw std::runtime_error("Unknown opcode: " + std::to_string(opcode));
    }
}