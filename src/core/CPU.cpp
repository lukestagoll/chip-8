#include "CPU.h"
#include "Opcode.h"
#include <stdexcept>

void CPU::init()
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
    I = 0;
    delay_timer = 0;
    sound_timer = 0;
    program_counter = PROGRAM_START_ADDRESS;
}

void CPU::initStack()
{
    stack_pointer = 0;

    for (int i = 0; i < 16; ++i)
    {
        stack[i] = 0;
    }
}

void CPU::cycle()
{

    // Emulate one cycle of the Chip-8 CPU

    // Fetch instruction from memory at the current program counter
    if (program_counter >= MEMORY_LIMIT)
    {
        throw std::runtime_error("Error: program counter out of bounds");
    }

    uint16_t opcode = memory->read(program_counter) << 8 | memory->read(program_counter + 1);
    program_counter += 2;

    // Decode & Execute the instruction
    Opcode::execute(opcode, *this, *memory);
}