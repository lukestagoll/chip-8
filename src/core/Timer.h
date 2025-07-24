#pragma once
#include <SDL3/SDL.h>

class Timer
{
public:
    void update();
    void set(uint8_t v);
    uint8_t get() const { return value; };

private:
    const Uint64 frequency = SDL_GetPerformanceFrequency();
    int rate = 60;
    double tickInterval = 1.0 / rate;

    uint8_t value = 0;

    Uint64 previous = SDL_GetPerformanceCounter();
    double accumulator = 0.0;
    double delta = 0.0;
};
