#include "Memory.h"
#include <stdexcept>

uint8_t Memory::read(uint16_t address) const
{
    return memory_[address];
}

void Memory::write(uint16_t address, uint8_t value)
{
    memory_[address] = value;
}

uint8_t Memory::safeRead(uint16_t address) const
{
    if (address >= 4096)
    {
        throw std::out_of_range("Invalid memory read");
    }
    return memory_[address];
}

void Memory::safeWrite(uint16_t address, uint8_t value)
{
    if (address >= 4096)
    {
        throw std::out_of_range("Invalid memory write");
    }
    memory_[address] = value;
}

void Memory::init()
{
    for (int i = 0; i < 4096; ++i)
    {
        memory_[i] = 0;
    }
}