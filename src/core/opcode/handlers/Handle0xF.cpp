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
        cpu.waitForKeyPress(x);
        break;
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
        cpu.setIndexRegisterFromV(x);
        break;
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