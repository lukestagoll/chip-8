#include "Display.h"

Display::Display()
{
    clear();
    drawFlag = false;
}

void Display::clear()
{
    for (int i = 0; i < SIZE; ++i)
    {
        buffer[i] = 0;
    }
    drawFlag = true;
}

// returns true if collision
uint8_t Display::flipPixel(uint8_t x, uint8_t y)
{
    uint16_t idx = x + y * WIDTH;
    bool wasSet = buffer[idx] == 1;
    buffer[idx] ^= 1;
    drawFlag = true;

    return wasSet && buffer[idx] == 0;
}