#pragma once
#include <array>
#include <cstdint>

#include "Action.h"

class Keypad
{
public:
    void down(Action key) { keys.at(static_cast<int>(key)) = 1; }
    void up(Action key) { keys.at(static_cast<int>(key)) = 0; }
    bool isPressed(uint8_t key) { return keys.at(static_cast<int>(key)) == 1; }

private:
    std::array<uint8_t, 16> keys{}; // Keypad state (0-9, A-F)
};
