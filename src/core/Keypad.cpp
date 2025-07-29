#include "Keypad.h"

uint8_t Keypad::any()
{
    for (int i = 0; i < 16; i++)
    {
        if (keys_.at(i) == 1)
        {
            return i;
        }
    }
    return 0xFF;
}

void Keypad::init()
{
    for (int i = 0; i < 16; i++)
    {
        keys_[i] = 0;
    }
}