#pragma once
#include "CPU.h"

#include <cstdint>

class Chip8 {
public:
    Chip8();

    int loadROM(const char* filename);
    void tick();

private:
    CPU cpu;
    Memory memory;

    uint8_t keypad[16];    // Keypad state (0-9, A-F)
    uint8_t display[2048]; // Display buffer (64x32 pixels)

    void loadFontSet();
    void initKeypad();
    void clearDisplay();
};
