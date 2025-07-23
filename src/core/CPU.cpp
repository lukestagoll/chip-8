#include "CPU.h"
#include "Memory.h"
#include "Opcode.h"
#include <stdexcept>

CPU::CPU(Memory &mem, Display &disp) : memory(mem), display(disp)
{
    initRegisters();
    initStack();
}

void CPU::initRegisters()
{
    for (int i = 0; i < 16; ++i)
    {
        V[i] = 0;
    }
    indexRegister = 0;
    delayTimer = 0;
    soundTimer = 0;
    programCounter = PROGRAM_START_ADDRESS;
}

void CPU::initStack()
{
    stackPointer = 0;

    for (int i = 0; i < 16; ++i)
    {
        stack[i] = 0;
    }
}

void CPU::cycle()
{
    // Emulate one cycle of the Chip-8 CPU

    // Fetch instruction from memory at the current program counter
    if (programCounter >= Memory::MEMORY_LIMIT)
    {
        throw std::runtime_error("Error: program counter out of bounds");
    }

    uint16_t opcode = memory.read(programCounter) << 8 | memory.read(programCounter + 1);
    programCounter += 2;

    // Decode & Execute the instruction
    Opcode::execute(opcode, *this);
}