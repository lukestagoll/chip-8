#pragma once

#include "Display.h"
#include <SDL3/SDL.h>
#include <array>

class Texture
{
  public:
    SDL_Texture *get()
    {
        return texture;
    };
    bool create(SDL_Renderer *renderer, int width, int height);
    void update(const uint8_t *displayBuffer);
    void destroy()
    {
        SDL_DestroyTexture(texture);
    }

  private:
    SDL_Texture *texture;
    std::array<uint32_t, Display::SIZE> pixels;
};
