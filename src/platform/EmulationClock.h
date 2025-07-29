#pragma once
#include <QElapsedTimer>

class EmulationClock
{
  public:
    EmulationClock() { clock_.start(); }
    void update();
    bool shouldTick() const;
    void consumeTick();

    void updateTickRate(int ticksPerSecond);

  private:
    QElapsedTimer clock_;
    qint64 lastTimeNs_ = 0;

    int ticksPerSecond_ = 800;
    double tickInterval_ = 1.0 / ticksPerSecond_;
    double accumulatedTime_ = 0.0;
    double deltaTime_ = 0.0;
    static constexpr double nanoToSec_ = 1e9;
};
