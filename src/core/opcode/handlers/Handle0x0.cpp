#include "CPU.h"
#include "Opcode.h"
#include <cstdint>
#include <stdexcept>

void Opcode::handle0x0(uint16_t opcode, CPU &cpu)
{
    switch (opcode)
    {
        case 0x00E0:
            // TODO: clear screen
            throw std::runtime_error("Unimplemented opcode (0x00E0): " + std::to_string(opcode));
        case 0x00EE:
            // TODO: return from subroutine
            throw std::runtime_error("Unimplemented opcode (0x00EE): " + std::to_string(opcode));
        default:
            throw std::runtime_error("Unknown opcode: " + std::to_string(opcode));
    }
}
