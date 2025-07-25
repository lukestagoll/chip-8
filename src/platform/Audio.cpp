#include "Audio.h"
#include <SDL3/SDL.h>
#include <array>

bool Audio::create()
{
    spec.channels = 1;
    spec.format = SDL_AUDIO_F32;
    spec.freq = 8000;

    stream = SDL_OpenAudioDeviceStream(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, &spec, NULL, NULL);
    if (!stream)
    {
        SDL_Log("Couldn't create audio stream: %s", SDL_GetError());
        return false;
    }
    SDL_ResumeAudioStreamDevice(stream);
    return true;
}

void Audio::start()
{
    if (SDL_GetAudioStreamQueued(stream) < minimumQueued)
    {
        std::array<float, samples> buffer{};
        for (int i = 0; i < samples; ++i)
        {
            phase = sineSample * freq / 8000.0f;
            buffer[i] = SDL_sinf(phase * 2 * SDL_PI_F);
            sineSample++;
        }
        sineSample %= 8000;
        SDL_PutAudioStreamData(stream, &buffer, sizeof(buffer));
    }
}

void Audio::stop()
{
    SDL_ClearAudioStream(stream);
}