#pragma once
#include "CPU.h"
#include "Display.h"
#include "Memory.h"

#include <cstdint>

class Chip8 {
public:
    Chip8();

    int loadROM(const char *filename);
    void tick();

    void setDrawFlag(bool value) { draw_flag = value; }
    bool getDrawFlag() const { return draw_flag; }
    Display *getDisplay() { return &display; }

private:
    CPU cpu;
    Memory memory;
    Display display;

    uint8_t keypad[16];    // Keypad state (0-9, A-F)

    bool draw_flag = false;

    void loadFontSet();
    void initKeypad();
};
