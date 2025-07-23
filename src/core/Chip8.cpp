#include "Chip8.h"
#include "Font.h"
#include "Memory.h"
#include <cstdint>
#include <fstream>
#include <iostream>

Chip8::Chip8() : memory(), display(), cpu(memory, display)
{
    loadFontSet();
    initKeypad();
}

int Chip8::loadROM(const char *filename)
{
    std::ifstream file(filename, std::ios::binary);
    if (!file)
    {
        std::cerr << "Error: Failed to open file.";
        return 1;
    }

    size_t index = CPU::PROGRAM_START_ADDRESS;
    while (index < Memory::MEMORY_LIMIT)
    {
        char byte;
        file.read(&byte, 1);
        memory.write(index, static_cast<uint8_t>(byte));
        index++;
    }

    if (!file.eof() && file.peek() != EOF)
    {
        std::cerr << "Error: file exceeds memory limit.";
        return 1;
    }

    return 0;
}

void Chip8::tick()
{
    cpu.cycle();
}

void Chip8::loadFontSet()
{
    for (int i = 0; i < 80; ++i)
    {
        memory.safeWrite(0x050 + i, systemFont[i]);
    }
}

void Chip8::initKeypad()
{
    for (int i = 0; i < 16; ++i)
    {
        keypad[i] = 0;
    }
}
