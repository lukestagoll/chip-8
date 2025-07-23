#include "CPU.h"
#include "Opcode.h"
#include <cstdint>
#include <stdexcept>

void Opcode::handle0x0(uint16_t opcode, CPU &cpu)
{
    switch (opcode)
    {
        case 0x00E0:
            cpu.clearDisplay();
            break;
        case 0x00EE:
            cpu.exitSubroutine();
            break;
        default:
            throw std::runtime_error("Unknown opcode: " + std::to_string(opcode));
    }
}
