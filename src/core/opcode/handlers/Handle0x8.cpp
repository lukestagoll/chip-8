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
        // TODO: Set VX to VX AND VY
        throw std::runtime_error("Unimplemented opcode (0x8XY2): " + std::to_string(opcode));
    case 0x8003:
        // TODO: Set VX to VX XOR VY
        throw std::runtime_error("Unimplemented opcode (0x8XY3): " + std::to_string(opcode));
    case 0x8004:
        /*
            TODO: Add the value of register VY to register VX
                  Set VF to 01 if a carry occurs
                  Set VF to 00 if a carry does not occur
        */
        throw std::runtime_error("Unimplemented opcode (0x8XY4): " + std::to_string(opcode));
    case 0x8005:
        /*
            TODO: Subtract the value of register VY from register VX
                  Set VF to 00 if a borrow occurs
                  Set VF to 01 if a borrow does not occur
        */
        throw std::runtime_error("Unimplemented opcode (0x8XY5): " + std::to_string(opcode));
    case 0x8006:
        /*
            TODO: Store the value of register VY shifted right one bit in register VX¹
                  Set register VF to the least significant bit prior to the shift
                  VY is unchanged
        */
        throw std::runtime_error("Unimplemented opcode (0x8XY6): " + std::to_string(opcode));
    case 0x8007:
        /*
            TODO: Set register VX to the value of VY minus VX
                  Set VF to 00 if a borrow occurs
                  Set VF to 01 if a borrow does not occur
        */
        throw std::runtime_error("Unimplemented opcode (0x8XY7): " + std::to_string(opcode));
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