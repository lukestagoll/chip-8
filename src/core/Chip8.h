#pragma once

#include <cstdint>

#define PROGRAM_START_ADDRESS 0x200

class Chip8 {
public:
    void init();
    void loadROM(const char* filename);
    void cycle();

private:
    /*
        Memory layout:
        0x000-0x1FF: Reserved for interpreter
        0x050-0x0A0: Built in 4x5 pixel font set (0-F). Currently unimplemented.
        0x200-0xFFF: Program ROM and RAM
    */
    uint8_t memory[4096];     // 4KB of memory
    uint8_t V[16];            // 16 8-bit registers

    uint16_t I;               // 16-bit index register
    uint16_t program_counter; // Program counter

    uint8_t delay_timer;      // Delay timer
    uint8_t sound_timer;      // Sound timer

    uint16_t stack[16];       // Stack for subroutine calls
    uint8_t stack_pointer;    // Stack pointer

    uint8_t keypad[16];       // Keypad state (0-9, A-F)
    uint8_t display[2048];    // Display buffer (64x32 pixels)

    void initMemory();
    void loadFontSet();
    void initRegisters();
    void initStack();
    void initKeypad();
    void clearDisplay();
};
