#pragma once

#include "Audio.h"
#include "Chip8.h"
#include "EmulationClock.h"
#include "EventHandler.h"
#include "Renderer.h"
#include "Texture.h"
#include "Window.h"

class Application
{
public:
    Application() { eventHandler.attachChip8(&chip8); }
    int run(const char *romFile);
    bool initSDL();
    int exit(int status);

private:
    Window window;
    Renderer renderer;
    Texture texture;
    Chip8 chip8;
    EmulationClock emuClock;
    EventHandler eventHandler;
    Audio audio;
};
