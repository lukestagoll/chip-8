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

    void clearDrawFlag() { display.clearDrawFlag(); }
    bool getDrawFlag() const { return display.getDrawFlag(); }
    Display *getDisplay() { return &display; }

private:
    CPU cpu;
    Memory memory;
    Display display;

    std::array<uint8_t, 16> keypad; // Keypad state (0-9, A-F)

    void loadFontSet();
    void initKeypad();
};
