#pragma once
#include <QElapsedTimer>

class Timer
{
public:
    void update();
    void set(uint8_t tickCount_);
    uint8_t get() const { return ticksRemaining_; };
    void reset();

private:
    QElapsedTimer clock_;
    uint8_t ticksRemaining_ = 0;
    qint64 lastTimeNs_ = 0;
    int ticksPerSecond_ = 60;
    double tickInterval_ = 1.0 / ticksPerSecond_;
    double accumulatedTime_ = 0.0;
    double deltaTime_ = 0.0;
    static constexpr double nanoToSec_ = 1e9;
};
