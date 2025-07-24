#include "CPU.h"
#include "Memory.h"
#include "Opcode.h"
#include <stdexcept>

CPU::CPU(Memory &mem, Display &disp) : memory(mem), display(disp) {}

// --- Program Control / Flow Execution ---

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

void CPU::callSubroutine(uint16_t address)
{

    if (stackPointer >= 16)
    {
        throw std::overflow_error("Stack limit reached");
    }
    stack[stackPointer++] = programCounter;

    programCounter = address;
}

void CPU::exitSubroutine()
{
    if (stackPointer == 0)
    {
        throw std::underflow_error("Stack empty");
    }
    programCounter = stack[--stackPointer];
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

// --- Arithmetic and Logic Instructions ---

void CPU::addRegisters(uint8_t x, uint8_t y)
{
    uint16_t sum = V[x] + V[y];
    V[VF] = sum > 0xFF ? 1 : 0;
    V[x] = static_cast<uint8_t>(sum);
}

void CPU::subtractRegisters(uint8_t x, uint8_t y)
{
    uint16_t result = V[x] - V[y];
    V[VF] = V[x] >= V[y] ? 1 : 0;
    V[x] = static_cast<uint8_t>(result);
}

void CPU::subtractReversed(uint8_t x, uint8_t y)
{
    uint16_t result = V[y] - V[x];
    V[VF] = V[y] >= V[x] ? 1 : 0;
    V[x] = static_cast<uint8_t>(result);
}

void CPU::shiftRight(uint8_t index)
{
    V[VF] = V[index] & 0x1;
    V[index] >>= 1;
}
void CPU::shiftLeft(uint8_t index)
{
    V[VF] = (V[index] & 0x80) >> 7;
    V[index] <<= 1;
}

// --- Comparison ---
bool CPU::equalsRegisters(uint8_t x, uint8_t y) const
{
    return V[x] == V[y];
}
bool CPU::equalsImmediate(uint8_t index, uint8_t value) const
{
    return V[index] == value;
}
bool CPU::notEqualsImmediate(uint8_t index, uint8_t value) const
{
    return V[index] != value;
}