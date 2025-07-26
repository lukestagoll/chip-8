#include "CPU.h"
#include "Opcode.h"
#include <cstdint>

CPUStatus Opcode::handle0xF(uint16_t opcode, CPU &cpu)
{
    uint8_t x = (opcode >> 8) & 0xF;

    switch (opcode & 0x00FF)
    {
    case 0x0007: return cpu.storeDelay(x);
    case 0x000A: return cpu.waitForKeyPress(x);
    case 0x0015: return cpu.setDelayTimer(x);
    case 0x0018: return cpu.setSoundTimer(x);
    case 0x001E: return cpu.addRegisterToIndex(x);
    case 0x0029: return cpu.setIndexRegisterFromV(x);
    case 0x0033: return cpu.writeBCDToMemory(x);
    case 0x0055: return cpu.saveRegistersToMemory(x);
    case 0x0065: return cpu.loadRegistersFromMemory(x);
    default:     return cpu.unknownOperation(opcode);
    }
}