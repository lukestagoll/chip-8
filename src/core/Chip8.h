#pragma once
#include "CPU.h"
#include "Display.h"
#include "Memory.h"

#include <array>
#include <cstdint>

class Chip8 {
public:
    Chip8();

    int loadROM(const char *filename);
    void tick();

    void setDrawFlag(bool value) { drawFlag = value; }
    bool getDrawFlag() const { return drawFlag; }
    Display *getDisplay() { return &display; }

private:
    CPU cpu;
    Memory memory;
    Display display;

    std::array<uint8_t, 16> keypad; // Keypad state (0-9, A-F)

    bool drawFlag = false;

    void loadFontSet();
    void initKeypad();
};
