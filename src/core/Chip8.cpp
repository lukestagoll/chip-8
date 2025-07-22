#include "Chip8.h"
#include "Font.h"

void Chip8::init()
{
    initMemory();
    loadFontSet();
    initRegisters();
    initStack();
    initKeypad();
    clearDisplay();
}

void Chip8::loadROM(const char* filename)
{
    // Load the ROM file into memory
    // Read the file and copy its contents to the Chip-8 memory starting at address 0x200
    // Handle errors if the file cannot be opened or read
    // Set the program counter to 0x200 after loading the ROM
    
}

void Chip8::cycle()
{

    // Emulate one cycle of the Chip-8 CPU
    // Fetch instruction from memory at the current program counter
    // Decode the instruction
    // Execute the instruction
}

void Chip8::initMemory()
{
    for (int i = 0; i < 4096; ++i)
    {
        memory[i] = 0;
    }
}

void Chip8::loadFontSet()
{
    for (int i = 0; i < 80; ++i)
    {
        memory[0x050 + i] = system_font[i];
    }
}

void Chip8::initRegisters()
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

void Chip8::initStack()
{
    stack_pointer = 0;

    for (int i = 0; i < 16; ++i)
    {
        stack[i] = 0;
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