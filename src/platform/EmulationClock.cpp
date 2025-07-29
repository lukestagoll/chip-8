#include "EmulationClock.h"

void EmulationClock::update()
{
    qint64 current = clock_.nsecsElapsed();
    deltaTime_ = (current - lastTimeNs_) / nanoToSec_;
    lastTimeNs_ = current;

    accumulatedTime_ += deltaTime_;
}

bool EmulationClock::shouldTick() const
{
    return accumulatedTime_ >= tickInterval_;
}

void EmulationClock::consumeTick()
{
    accumulatedTime_ -= tickInterval_;
}

void EmulationClock::updateTickRate(int ticksPerSecond)
{
    if (ticksPerSecond <= 0) return;
    ticksPerSecond_ = ticksPerSecond;
    tickInterval_ = 1.0 / ticksPerSecond_;
}
