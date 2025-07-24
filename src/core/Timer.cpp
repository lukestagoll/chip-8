#include "Timer.h"

void Timer::update()
{
    if (value == 0) return;

    Uint64 current = SDL_GetPerformanceCounter();
    delta = (current - previous) / static_cast<double>(frequency);
    previous = current;

    accumulator += delta;

    while (accumulator >= tickInterval && value > 0)
    {
        value--;

        accumulator -= tickInterval;
    }
}

void Timer::set(uint8_t v)
{
    if (v > 0 && value == 0) {
        accumulator = 0;
        previous = SDL_GetPerformanceCounter();
    }
    value = v;
};