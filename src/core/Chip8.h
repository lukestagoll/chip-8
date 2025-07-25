#pragma once
#include "Action.h"
#include "CPU.h"
#include "Display.h"
#include "Keypad.h"
#include "Memory.h"
#include "Timer.h"

#include <cstdint>

class Chip8 {
public:
    Chip8();

    int loadROM(const char *filename);
    void tick();

    void clearDrawFlag() { display.clearDrawFlag(); }
    bool getDrawFlag() const { return display.getDrawFlag(); }
    const uint8_t *getDisplayBuffer() const { return display.getBuffer(); }

    void updateTimers();
    bool playingAudio();

    void keydown(Action key);
    void keyup(Action key);

private:
    CPU cpu;
    Memory memory;
    Display display;
    Timer delayTimer;
    Timer soundTimer;
    Keypad keypad;

    void loadFontSet();
};
