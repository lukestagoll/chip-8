#include "Chip8.h"
#include "CPU.h"
#include "Font.h"
#include "Memory.h"
#include <cstdint>
#include <fstream>
#include <iostream>

Chip8::Chip8()
    : memory_(), display_(), keypad_(), delayTimer_(), soundTimer_(), cpu_(memory_, display_, delayTimer_, soundTimer_, keypad_)
{
    init();
}

void Chip8::init()
{
    loadFontSet();
    memory_.init();
    display_.clear();
    cpu_.init();
    keypad_.init();
    delayTimer_.reset();
    soundTimer_.reset();
    paused_ = false;
}

int Chip8::loadROM(const char *filename)
{
    std::string filenameString(filename);

    std::ifstream file(filename, std::ios::binary);
    if (!file)
    {
        std::cerr << "Error: Failed to open file." << std::endl;
        return 1;
    }

    size_t index = CPU::PROGRAM_START_ADDRESS;
    while (index < Memory::MEMORY_LIMIT)
    {
        char byte;
        file.read(&byte, 1);
        memory_.write(index, static_cast<uint8_t>(byte));
        index++;
    }

    if (!file.eof() && file.peek() != EOF)
    {
        std::cerr << "Error: file exceeds memory limit." << std::endl;
        return 1;
    }

    currentROM = filenameString;

    paused_ = false;
    return 0;
}

int Chip8::restart()
{
    if (currentROM == "") return 1;
    return loadROM(currentROM.c_str());
}

CPUStatus Chip8::tick()
{
    if (cpu_.waiting()) return CPUStatus::OK;
    return cpu_.cycle();
}

void Chip8::loadFontSet()
{
    for (int i = 0; i < 80; ++i)
    {
        memory_.safeWrite(0x050 + i, systemFont[i]);
    }
}

void Chip8::updateTimers()
{
    delayTimer_.update();
    soundTimer_.update();
}

bool Chip8::playingAudio()
{
    return soundTimer_.get() > 0;
}

void Chip8::keydown(Action key)
{
    keypad_.down(key);
}

void Chip8::keyup(Action key)
{
    keypad_.up(key);
}