#pragma once
#include "Action.h"
#include <SDL3/SDL_scancode.h>
#include <unordered_map>

class Keymap
{
public:
    Action getKey(SDL_Scancode scancode);

private:
    std::unordered_map<SDL_Scancode, Action> keybinds = {
        {SDL_SCANCODE_1, Action::KEYPAD_1},
        {SDL_SCANCODE_2, Action::KEYPAD_2},
        {SDL_SCANCODE_3, Action::KEYPAD_3},
        {SDL_SCANCODE_4, Action::KEYPAD_C},

        {SDL_SCANCODE_Q, Action::KEYPAD_4},
        {SDL_SCANCODE_W, Action::KEYPAD_5},
        {SDL_SCANCODE_E, Action::KEYPAD_6},
        {SDL_SCANCODE_R, Action::KEYPAD_D},

        {SDL_SCANCODE_A, Action::KEYPAD_7},
        {SDL_SCANCODE_S, Action::KEYPAD_8},
        {SDL_SCANCODE_D, Action::KEYPAD_9},
        {SDL_SCANCODE_F, Action::KEYPAD_E},

        {SDL_SCANCODE_Z, Action::KEYPAD_A},
        {SDL_SCANCODE_X, Action::KEYPAD_0},
        {SDL_SCANCODE_C, Action::KEYPAD_B},
        {SDL_SCANCODE_V, Action::KEYPAD_F},
    };
};
