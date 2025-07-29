#pragma once
#include "Action.h"
#include <Qt>

class Keymap
{
public:
    Action getKey(int key);

private:
    std::unordered_map<int, Action> keybinds_ = {
        {Qt::Key_1, Action::KEYPAD_1},
        {Qt::Key_2, Action::KEYPAD_2},
        {Qt::Key_3, Action::KEYPAD_3},
        {Qt::Key_4, Action::KEYPAD_C},

        {Qt::Key_Q, Action::KEYPAD_4},
        {Qt::Key_W, Action::KEYPAD_5},
        {Qt::Key_E, Action::KEYPAD_6},
        {Qt::Key_R, Action::KEYPAD_D},

        {Qt::Key_A, Action::KEYPAD_7},
        {Qt::Key_S, Action::KEYPAD_8},
        {Qt::Key_D, Action::KEYPAD_9},
        {Qt::Key_F, Action::KEYPAD_E},

        {Qt::Key_Z, Action::KEYPAD_A},
        {Qt::Key_X, Action::KEYPAD_0},
        {Qt::Key_C, Action::KEYPAD_B},
        {Qt::Key_V, Action::KEYPAD_F},
    };
};
