#include "CPU.h"
#include "Memory.h"
#include "Opcode.h"
#include <stdexcept>

CPU::CPU(Memory &mem, Display &disp) : memory(mem), display(disp)
{
    initRegisters();
    initStack();
}

void CPU::initRegisters()
{
    for (int i = 0; i < 16; ++i)
    {
        V[i] = 0;
    }
    indexRegister = 0;
    delayTimer = 0;
    soundTimer = 0;
    programCounter = PROGRAM_START_ADDRESS;
}

void CPU::initStack()
{
    stackPointer = 0;

    for (int i = 0; i < 16; ++i)
    {
        stack[i] = 0;
    }
}

void CPU::cycle()
{
    // Emulate one cycle of the Chip-8 CPU

    // Fetch instruction from memory at the current program counter
    if (programCounter >= Memory::MEMORY_LIMIT)
    {
        throw std::runtime_error("Error: program counter out of bounds");
    }

    uint16_t opcode = memory.read(programCounter) << 8 | memory.read(programCounter + 1);
    programCounter += 2;

    // Decode & Execute the instruction
    Opcode::execute(opcode, *this);
}

/**
    Draws a sprite at position VX, VY with N bytes of sprite data starting at the address stored in I.
    Set VF to 01 if any set pixels are changed to unset, and 00 otherwise
*/
void CPU::drawSprite(uint8_t vx, uint8_t vy, uint8_t n)
{
    // wrap the coordinates - since display width & height are powers of 2, can use bitwise `AND` rather than modulo.
    uint8_t x = V[vx] & (display.WIDTH - 1);
    uint8_t y = V[vy] & (display.HEIGHT - 1);
    uint16_t spriteAddress = indexRegister;

    bool collision = false;

    for (uint8_t row = 0; row < n; row++)
    {
        uint8_t spriteByte = memory.read(spriteAddress + row);
        for (uint8_t col = 0; col < 8; col++)
        {
            if ((spriteByte & (0x80 >> col)) == 0) continue;
#ifdef CLIP_SPRITES
            uint16_t px = x + col;
            uint16_t py = y + row;
            if (px >= display.WIDTH || py >= display.HEIGHT) continue;
#else
            uint8_t px = (x + col) & (display.WIDTH - 1);
            uint8_t py = (y + row) & (display.HEIGHT - 1);
            
#endif
            if (display.flipPixel(px, py))
            {
                collision = true;
            }
        }
    }

    V[0xF] = collision ? 1 : 0;
}