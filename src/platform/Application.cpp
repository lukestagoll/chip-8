#include "Application.h"
#include "CPU.h"
#include "Chip8.h"
#include "Display.h"

#include <SDL3/SDL.h>
#include <iostream>

int Application::run(const char *romFile)
{
    if (!initSDL() || !window.create() || !renderer.create(window.get()) ||
        !texture.create(renderer.get(), Display::WIDTH, Display::HEIGHT) || !audio.create())
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
        eventHandler.pollEvents();
        emuClock.update();

        if (chip8.playingAudio()) audio.start();
        else audio.stop();

        while (emuClock.shouldTick())
        {
            CPUStatus status = chip8.tick();
            std::cout << static_cast<int>(status) << std::endl;
            if (status != CPUStatus::OK)
            {
                return exit(static_cast<int>(status));
            }

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

    return exit(0);
}

bool Application::initSDL()
{
    if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO))
    {
        SDL_Log("Could not initialize SDL: %s", SDL_GetError());
        return false;
    }
    return true;
}

int Application::exit(int status)
{
    texture.destroy();
    renderer.destroy();
    window.destroy();
    SDL_Quit();
    return status;
}