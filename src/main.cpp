#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

#include "Chip8.h"
#include "SDL3/SDL_stdinc.h"

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

    SDL_Texture *texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, 64, 32);

    const char* romFile = "roms/1-chip8-logo.ch8";
    int fail = chip8.loadROM(romFile);

    if (fail) return fail;

    for (;;)
    {
        chip8.tick();

        if (chip8.getDrawFlag())
        {
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            SDL_RenderClear(renderer);

            uint8_t *display = chip8.getDisplay();
            uint32_t pixels[2048];
            for (int i = 0; i < 64 * 32; ++i)
            {
                pixels[i] = display[i] ? 0xFFFFFFFF : 0x000000FF;
            }

            SDL_UpdateTexture(texture, nullptr, pixels, 64 * sizeof(uint32_t));

            SDL_RenderTexture(renderer, texture, nullptr, nullptr);

            SDL_RenderPresent(renderer);

            chip8.setDrawFlag(false);
        }
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}