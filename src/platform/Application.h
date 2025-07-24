#pragma once

#include "Chip8.h"
#include "EmulationClock.h"
#include "Renderer.h"
#include "Texture.h"
#include "Window.h"

class Application
{
public:
    int run(const char *romFile);
    bool initSDL();

private:
    Window window;
    Renderer renderer;
    Texture texture;
    Chip8 chip8;
    EmulationClock emuClock;
};
