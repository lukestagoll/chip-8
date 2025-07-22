#pragma once

class Chip8 {
public:
    Chip8();
    ~Chip8();
    void init();
    void loadROM(const char* filename);
    void cycle();
};
