#pragma once
#include "Action.h"
#include "CPU.h"
#include "Chip8Display.h"
#include "Keypad.h"
#include "Memory.h"
#include "Timer.h"

#include <cstdint>

class Chip8 {
public:
    Chip8();

    int loadROM(const char *filename);
    CPUStatus tick();

    void clearDrawFlag() { display_.clearDrawFlag(); }
    bool getDrawFlag() const { return display_.getDrawFlag(); }
    const uint8_t *getDisplayBuffer() const { return display_.getBuffer(); }

    void updateTimers();
    bool playingAudio();

    void keydown(Action key);
    void keyup(Action key);

private:
    CPU cpu_;
    Memory memory_;
    Chip8Display display_;
    Timer delayTimer_;
    Timer soundTimer_;
    Keypad keypad_;

    void loadFontSet();
};
