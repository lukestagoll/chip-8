#pragma once
#include <SDL3/SDL_events.h>

#include "Chip8.h"
#include "Keymap.h"

class EventHandler
{
public:
    void attachChip8(Chip8 *chipPtr) { chip8 = chipPtr; }
    void pollEvents();

private:
    Chip8 *chip8;
    SDL_Event event;
    Keymap keymap;
};
