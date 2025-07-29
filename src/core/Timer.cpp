#include "Timer.h"

void Timer::update()
{
    if (ticksRemaining_ == 0) return;
    qint64 current = clock_.nsecsElapsed();
    deltaTime_ = (current - lastTimeNs_) / nanoToSec_;
    lastTimeNs_ = current;

    accumulatedTime_ += deltaTime_;

    while (accumulatedTime_ >= tickInterval_ && ticksRemaining_ > 0)
    {
        ticksRemaining_--;
        accumulatedTime_ -= tickInterval_;
    }
}

void Timer::set(uint8_t tickCount)
{
    if (tickCount > 0 && ticksRemaining_ == 0) reset();
    ticksRemaining_ = tickCount;
};

void Timer::reset()
{
    accumulatedTime_ = 0;
    lastTimeNs_ = clock_.nsecsElapsed();
};
