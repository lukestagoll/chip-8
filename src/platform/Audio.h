#pragma once
#include <SDL3/SDL.h>

class Audio
{
  public:
    SDL_AudioStream *get() { return stream; }
    bool create();
    void start();
    void stop();

  private:
    SDL_AudioStream *stream;
    SDL_AudioSpec spec;
    static constexpr int samples = 512;
    const float freq = 440.0f;
    const int minimumQueued = 200 * sizeof(float); // 200 samples per second. increase if audio is choppy
    float phase = 0.0f;
    int sineSample = 0;
};