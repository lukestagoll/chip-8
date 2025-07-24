#pragma once

#include <SDL3/SDL.h>

class EmulationClock
{
public:
    void update();
    bool shouldTick() const;
    void consumeTick();

    void updateClockRate(int rate);

private:
    const Uint64 frequency = SDL_GetPerformanceFrequency();
    int clockRate = 800;
    double tickInterval = 1.0 / clockRate;

    Uint64 previous = SDL_GetPerformanceCounter();
    double accumulator = 0.0;
    double delta = 0.0;
};
