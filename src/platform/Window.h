#pragma once

#include <SDL3/SDL.h>

class Window
{
public:
    static constexpr int SCREEN_WIDTH = 640;
    static constexpr int SCREEN_HEIGHT = 320;
    SDL_Window *get() { return window; };
    bool create();
    void destroy() { SDL_DestroyWindow(window); }

  private:
    SDL_Window *window;
};
