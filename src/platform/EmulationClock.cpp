#include "EmulationClock.h"

void EmulationClock::update()
{
    Uint64 current = SDL_GetPerformanceCounter();
    delta = (current - previous) / static_cast<double>(frequency);
    previous = current;

    accumulator += delta;
}

bool EmulationClock::shouldTick() const
{
    return accumulator >= tickInterval;
}

void EmulationClock::consumeTick()
{
    accumulator -= tickInterval;
}

void EmulationClock::updateClockRate(int rate)
{
    if (rate <= 0)
        return;
    clockRate = rate;
    tickInterval = 1.0 / clockRate;
}