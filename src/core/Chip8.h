#pragma once
#include "CPU.h"

#include <cstdint>

class Chip8 {
public:
    Chip8();

    int loadROM(const char* filename);
    void tick();

    void setDrawFlag(bool value) { draw_flag = value; }
    bool getDrawFlag() const { return draw_flag; }
    uint8_t *getDisplay() { return display; };

private:
    CPU cpu;
    Memory memory;

    uint8_t keypad[16];    // Keypad state (0-9, A-F)
    uint8_t display[2048]; // Display buffer (64x32 pixels)

    bool draw_flag = false;

    void loadFontSet();
    void initKeypad();
    void clearDisplay();
};
