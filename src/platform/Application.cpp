#include "Application.h"
#include "Chip8.h"
#include "Display.h"

#include <SDL3/SDL.h>

int Application::run(const char *romFile)
{
    if (!initSDL() || !window.create() || !renderer.create(window.get()) ||
        !texture.create(renderer.get(), Display::WIDTH, Display::HEIGHT))
    {
        return 1;
    }

    int fail = chip8.loadROM(romFile);
    if (fail)
    {
        return fail;
    }

    for (;;)
    {
        emuClock.update();

        while (emuClock.shouldTick())
        {
            chip8.tick();
            if (chip8.getDrawFlag())
            {
                renderer.clear();

                texture.update(chip8.getDisplayBuffer());

                renderer.renderTexture(texture.get());
                chip8.clearDrawFlag();
            }

            emuClock.consumeTick();
        }

        chip8.updateTimers();
    }

    texture.destroy();
    renderer.destroy();
    window.destroy();
    SDL_Quit();
    return 0;
}

bool Application::initSDL()
{
    if (!SDL_Init(SDL_INIT_VIDEO))
    {
        SDL_Log("Could not initialize SDL: %s", SDL_GetError());
        return false;
    }
    return true;
}