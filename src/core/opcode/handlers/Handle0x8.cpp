#include "CPU.h"
#include "Opcode.h"
#include <cstdint>
#include <stdexcept>

CPUStatus Opcode::handle0x8(uint16_t opcode, CPU &cpu)
{
    uint8_t x = (opcode >> 8) & 0xF;
    uint8_t y = (opcode >> 4) & 0xF;

    switch (opcode & 0xF00F)
    {
    case 0x8000: return cpu.copyRegister(x, y);
    case 0x8001: return cpu.bitwiseOR(x, y);
    case 0x8002: return cpu.bitwiseAND(x, y);
    case 0x8003: return cpu.bitwiseXOR(x, y);
    case 0x8004: return cpu.addRegisters(x, y);
    case 0x8005: return cpu.subtractRegisters(x, y);
    case 0x8006: return cpu.shiftRight(x);
    case 0x8007: return cpu.subtractReversed(x, y);
    case 0x800E: return cpu.shiftLeft(x);
    default:     return cpu.unknownOperation(opcode);
    }
}