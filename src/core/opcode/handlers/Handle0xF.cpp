#include "CPU.h"
#include "Opcode.h"
#include <cstdint>
#include <stdexcept>

void Opcode::handle0xF(uint16_t opcode, CPU &cpu)
{
    uint8_t x = (opcode >> 8) & 0xF;

    switch (opcode & 0x00FF)
    {
    case 0x0007:
        cpu.storeDelay(x);
        break;
    case 0x000A:
        // TODO: Wait for a keypress and store the result in register VX
        throw std::runtime_error("Unimplemented opcode (0xFX0A): " + std::to_string(opcode));
    case 0x0015:
        cpu.setDelayTimer(x);
        break;
    case 0x0018:
        cpu.setSoundTimer(x);
        break;
    case 0x001E:
        cpu.addRegisterToIndex(x);
        break;
    case 0x0029:
        // TODO: Set I to the memory address of the sprite data corresponding to the hexadecimal digit stored in register VX
        throw std::runtime_error("Unimplemented opcode (0xFX29): " + std::to_string(opcode));
    case 0x0033:
        cpu.writeBCDToMemory(x);
        break;
    case 0x0055:
        cpu.saveRegistersToMemory(x);
        break;
    case 0x0065:
        cpu.loadRegistersFromMemory(x);
        break;
    default:
        throw std::runtime_error("Unknown opcode: " + std::to_string(opcode));
    }
}