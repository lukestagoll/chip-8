#include "EventHandler.h"

#include <SDL3/SDL_log.h>

void EventHandler::pollEvents()
{
    while (SDL_PollEvent(&event) > 0)
    {
        switch (event.type)
        {
        case SDL_EVENT_KEY_DOWN: {
            Action key = keymap.getKey(event.key.scancode);
            if (key != Action::NONE)
            {
                chip8->keydown(key);
            }
            break;
        }
        case SDL_EVENT_KEY_UP: {
            Action key = keymap.getKey(event.key.scancode);
            if (key != Action::NONE)
            {
                chip8->keyup(key);
            }
            break;
        }
        default:
            break;
        }
    }
}