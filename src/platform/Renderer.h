#pragma once

#include <SDL3/SDL.h>

class Renderer
{
public:
    SDL_Renderer *get() { return renderer; };
    bool create(SDL_Window *window);
    void clear();
    void renderTexture(SDL_Texture *texture);
    void destroy() { SDL_DestroyRenderer(renderer); }

private:
    SDL_Renderer *renderer;
};
