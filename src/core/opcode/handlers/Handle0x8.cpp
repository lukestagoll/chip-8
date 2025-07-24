#include "CPU.h"
#include "Opcode.h"
#include <cstdint>
#include <stdexcept>

void Opcode::handle0x8(uint16_t opcode, CPU &cpu)
{
    uint8_t x = (opcode >> 8) & 0xF;
    uint8_t y = (opcode >> 4) & 0xF;

    switch (opcode & 0xF00F)
    {
    case 0x8000:
        cpu.assignV(x, y);
        break;
    case 0x8001:
        cpu.bitwiseOR(x, y);
        break;
    case 0x8002:
        cpu.bitwiseAND(x, y);
        break;
    case 0x8003:
        cpu.bitwiseXOR(x, y);
        break;
    case 0x8004:
        cpu.addRegisters(x, y);
        break;
    case 0x8005:
        cpu.subtractRegisters(x, y);
        break;
    case 0x8006:
        cpu.shiftRight(x);
        break;
    case 0x8007:
        cpu.subtractReversed(x, y);
        break;
    case 0x800E:
        cpu.shiftLeft(x);
        break;
    default:
        throw std::runtime_error("Unknown opcode: " + std::to_string(opcode));
    }
}