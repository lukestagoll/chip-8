#pragma once

#include <cstdint>

class Display
{
public:
    static constexpr int WIDTH = 64;
    static constexpr int HEIGHT = 32;
    static constexpr int SIZE = WIDTH * HEIGHT;

    Display();

    void clear();
    uint8_t flipPixel(uint8_t x, uint8_t y);
    const uint8_t *getBuffer() const { return buffer; };
    bool getDrawFlag() const { return drawFlag; }
    void clearDrawFlag() { drawFlag = false; }

private:
    uint8_t buffer[SIZE];
    bool drawFlag = false;
};