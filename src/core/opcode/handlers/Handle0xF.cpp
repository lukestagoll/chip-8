#include "CPU.h"
#include "Opcode.h"
#include <cstdint>
#include <stdexcept>

void Opcode::handle0xF(uint16_t opcode, CPU &cpu)
{
    switch (opcode & 0x00FF)
    {
    case 0x0007:
        // TODO: Store the current value of the delay timer in register VX
        throw std::runtime_error("Unimplemented opcode (0xFX07): " + std::to_string(opcode));
    case 0x000A:
        // TODO: Wait for a keypress and store the result in register VX
        throw std::runtime_error("Unimplemented opcode (0xFX0A): " + std::to_string(opcode));
    case 0x0015:
        // TODO: Set the delay timer to the value of register VX
        throw std::runtime_error("Unimplemented opcode (0xFX15): " + std::to_string(opcode));
    case 0x0018:
        // TODO: Set the sound timer to the value of register VX
        throw std::runtime_error("Unimplemented opcode (0xFX18): " + std::to_string(opcode));
    case 0x001E:
        // TODO: Add the value stored in register VX to register I
        throw std::runtime_error("Unimplemented opcode (0xFX1E): " + std::to_string(opcode));
    case 0x0029:
        // TODO: Set I to the memory address of the sprite data corresponding to the hexadecimal digit stored in register VX
        throw std::runtime_error("Unimplemented opcode (0xFX29): " + std::to_string(opcode));
    case 0x0033:
        // TODO: Store the binary-coded decimal equivalent of the value stored in register VX at addresses I, I + 1, and I + 2
        throw std::runtime_error("Unimplemented opcode (0xFX33): " + std::to_string(opcode));
    case 0x0055:
        // TODO: Store the values of registers V0 to VX inclusive in memory starting at address I. I is set to I + X + 1 after operation
        throw std::runtime_error("Unimplemented opcode (0xFX55): " + std::to_string(opcode));
    case 0x0065:
        // TODO: Fill registers V0 to VX inclusive with the values stored in memory starting at address I. I is set to I + X + 1 after operation
        throw std::runtime_error("Unimplemented opcode (0xFX65): " + std::to_string(opcode));
    default:
        throw std::runtime_error("Unknown opcode: " + std::to_string(opcode));
    }
}