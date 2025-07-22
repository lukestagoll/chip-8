#include "Chip8.h"
#include "Font.h"
#include <cstdint>
#include <fstream>
#include <iostream>

Chip8::Chip8()
{
    loadFontSet();
    initKeypad();
    clearDisplay();

    memory = Memory();

    cpu = CPU();
    cpu.attachMemory(&memory);
}


int Chip8::loadROM(const char *filename)
{
    // Load the ROM file into memory
    // Read the file and copy its contents to the Chip-8 memory starting at address 0x200
    // Handle errors if the file cannot be opened or read
    // Set the program counter to 0x200 after loading the ROM

    std::ifstream file(filename, std::ios::binary);
    if (!file)
    {
        std::cerr << "Error: Failed to open file.";
        return 1;
    }

    size_t index = PROGRAM_START_ADDRESS;
    while (index < MEMORY_LIMIT)
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
        memory.safeWrite(0x050 + i, system_font[i]);
    }
}

void Chip8::initKeypad()
{
    for (int i = 0; i < 16; ++i)
    {
        keypad[i] = 0;
    }
}

void Chip8::clearDisplay()
{
    for (int i = 0; i < 2048; ++i)
    {
        display[i] = 0;
    }
}