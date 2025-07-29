#pragma once

#include <cstdint>

class Chip8Display
{
public:
    static constexpr int WIDTH = 64;
    static constexpr int HEIGHT = 32;
    static constexpr int SIZE = WIDTH * HEIGHT;

    Chip8Display();

    void clear();
    uint8_t flipPixel(uint8_t x, uint8_t y);
    const uint8_t *getBuffer() const { return buffer_; };
    bool getDrawFlag() const { return drawFlag_; }
    void clearDrawFlag() { drawFlag_ = false; }

  private:
    uint8_t buffer_[SIZE];
    bool drawFlag_ = false;
};
