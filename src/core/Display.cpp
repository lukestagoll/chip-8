#include "Display.h"

Display::Display()
{
    clear();
    draw_flag = false;
}

void Display::clear()
{
    for (int i = 0; i < SIZE; ++i)
    {
        buffer[i] = 0;
    }
    draw_flag = true;
}