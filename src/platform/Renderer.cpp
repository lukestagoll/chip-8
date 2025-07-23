#include "SDL3/SDL_video.h"
#include "Renderer.h"

bool Renderer::create(SDL_Window *window)
{
    renderer = SDL_CreateRenderer(window, NULL);

    if (!renderer)
    {
        SDL_Log("Could not create renderer: %s", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return false;
    }

    return true;
}

void Renderer::clear()
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
}

void Renderer::renderTexture(SDL_Texture *texture)
{
    SDL_RenderTexture(renderer, texture, nullptr, nullptr);
    SDL_RenderPresent(renderer);
}
