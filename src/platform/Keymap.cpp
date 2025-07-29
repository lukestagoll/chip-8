#include "Keymap.h"
#include <stdexcept>

Action Keymap::getKey(int key)
{
    try
    {
        return keybinds_.at(key);
    }
    catch (const std::out_of_range &)
    {
        return Action::NONE;
    }
}
