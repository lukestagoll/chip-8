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