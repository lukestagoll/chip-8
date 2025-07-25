#include "Keymap.h"
#include <stdexcept>

Action Keymap::getKey(SDL_Scancode scancode)
{
    try {
        return keybinds.at(scancode);
    }
    catch (const std::out_of_range&)
    {
        return Action::NONE;
    }
}
