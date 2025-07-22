#include "CPU.h"
#include "Opcode.h"
#include <cstdint>
#include <stdexcept>

void Opcode::handleDXYN(uint16_t opcode, CPU &cpu)
{
    /*
        TODO: Draw a sprite at position VX, VY with N bytes of sprite data starting at the address stored in I.
              Set VF to 01 if any set pixels are changed to unset, and 00 otherwise
    */
    throw std::runtime_error("Unimplemented opcode (0xDXYN): " + std::to_string(opcode));
}