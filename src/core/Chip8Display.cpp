#include "Chip8Display.h"

Chip8Display::Chip8Display()
{
    clear();
    drawFlag_ = false;
}

void Chip8Display::clear()
{
    for (int i = 0; i < SIZE; ++i)
    {
        buffer_[i] = 0;
    }
    drawFlag_ = true;
}

// returns true if collision
uint8_t Chip8Display::flipPixel(uint8_t x, uint8_t y)
{
    uint16_t idx = x + y * WIDTH;
    bool wasSet = buffer_[idx] == 1;
    buffer_[idx] ^= 1;
    drawFlag_ = true;

    return wasSet && buffer_[idx] == 0;
}
