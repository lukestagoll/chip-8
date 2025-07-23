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
        cpu.orV(x, y);
        break;
    case 0x8002:
        cpu.andV(x, y);
        break;
    case 0x8003:
        cpu.xorV(x, y);
        break;
    case 0x8004:
        cpu.addVV(x, y);
        break;
    case 0x8005:
        cpu.subVV(x, y);
        break;
    case 0x8006:
        /*
            TODO: Store the value of register VY shifted right one bit in register VX¹
                  Set register VF to the least significant bit prior to the shift
                  VY is unchanged
        */
        throw std::runtime_error("Unimplemented opcode (0x8XY6): " + std::to_string(opcode));
    case 0x8007:
        cpu.subVV(y, x);
        break;
    case 0x800E:
        /*
            TODO: Store the value of register VY shifted left one bit in register VX¹
                  Set register VF to the most significant bit prior to the shift
                  VY is unchanged
        */
        throw std::runtime_error("Unimplemented opcode (0x8XYE): " + std::to_string(opcode));
    default:
        throw std::runtime_error("Unknown opcode: " + std::to_string(opcode));
    }
}