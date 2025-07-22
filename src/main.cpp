#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

#include "Chip8.h"

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 320

Chip8 chip8;

int main(int argc, char* argv[]) {
    if (!SDL_Init(SDL_INIT_VIDEO))
    {
        SDL_Log("Could not initialize SDL: %s", SDL_GetError());
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow
    (
        "Chip-8 Interpreter",
        SCREEN_WIDTH,
        SCREEN_HEIGHT,
        0
    );

    if (!window)
    {
        SDL_Log("Could not create window: %s", SDL_GetError());
        SDL_Quit();
        return 1;
    }
    SDL_Renderer* renderer = SDL_CreateRenderer(window, NULL);

    if (!renderer)
    {
        SDL_Log("Could not create renderer: %s", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    const char* romFile = "roms/1-chip8-logo.ch8";
    int fail = chip8.loadROM(romFile);

    if (fail) return fail;

    for (;;)
    {
        chip8.tick();
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}