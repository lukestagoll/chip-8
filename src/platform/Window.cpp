#include "Window.h"
#include "SDL3/SDL_video.h"

bool Window::create()
{
    window = SDL_CreateWindow("Chip-8 Interpreter", SCREEN_WIDTH, SCREEN_HEIGHT, 0);

    if (!window)
    {
        SDL_Log("Could not create window: %s", SDL_GetError());
        SDL_Quit();
        return false;
    }

    return true;
}
