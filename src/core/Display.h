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
    const uint8_t *getBuffer() const { return buffer; };

private:
    uint8_t buffer[SIZE];
    bool drawFlag = false;
};