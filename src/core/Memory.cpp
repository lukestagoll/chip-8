#include "Memory.h"
#include <stdexcept>

Memory::Memory()
{
    for (int i = 0; i < 4096; ++i)
    {
        memory[i] = 0;
    }
};

uint8_t Memory::read(uint16_t address) const
{
    return memory[address];
}

void Memory::write(uint16_t address, uint8_t value)
{
    memory[address] = value;
}

uint8_t Memory::safeRead(uint16_t address) const
{
    if (address >= 4096)
    {
        throw std::out_of_range("Invalid memory read");
    }
    return memory[address];
}

void Memory::safeWrite(uint16_t address, uint8_t value)
{
    if (address >= 4096)
    {
        throw std::out_of_range("Invalid memory write");
    }
    memory[address] = value;
}
