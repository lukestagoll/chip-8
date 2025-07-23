#include "Application.h"
#include <iostream>

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        std::cerr << "Usage: chip8 <rom_file>" << std::endl;
        return 1;
    }

    const char *romFile = argv[1];

    Application app;
    return app.run(romFile);
}