#include "Chip8Display.h"

Chip8Display::Chip8Display()
{
    clear();
    drawFlag = false;
}

void Chip8Display::clear()
{
    for (int i = 0; i < SIZE; ++i)
    {
        buffer[i] = 0;
    }
    drawFlag = true;
}

// returns true if collision
uint8_t Chip8Display::flipPixel(uint8_t x, uint8_t y)
{
    uint16_t idx = x + y * WIDTH;
    bool wasSet = buffer[idx] == 1;
    buffer[idx] ^= 1;
    drawFlag = true;

    return wasSet && buffer[idx] == 0;
}
