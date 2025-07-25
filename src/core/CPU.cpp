#include "CPU.h"
#include "Memory.h"
#include "Opcode.h"
#include <stdexcept>

CPU::CPU(Memory &mem, Display &disp, Timer &delay, Timer &sound, Keypad &keypad)
    : memory(mem), display(disp), delayTimer(delay), soundTimer(sound), keypad(keypad) {}

// --- Program Control / Flow Execution ---

void CPU::cycle()
{
    if (programCounter >= Memory::MEMORY_LIMIT)
    {
        throw std::runtime_error("Error: program counter out of bounds");
    }

    // Combine two 8-bit values into a single 16-bit opcode
    uint16_t opcode = memory.read(programCounter) << 8 | memory.read(programCounter + 1);
    programCounter += 2;

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
    uint8_t vf = sum > 0xFF ? 0x01 : 0x00;
    V[x] = static_cast<uint8_t>(sum);
    V[VF] = vf;
}

void CPU::subtractRegisters(uint8_t x, uint8_t y)
{
    uint16_t result = V[x] - V[y];
    uint8_t vf = V[x] >= V[y] ? 0x01 : 0x00;
    V[x] = static_cast<uint8_t>(result);
    V[VF] = vf;
}

void CPU::subtractReversed(uint8_t x, uint8_t y)
{
    uint16_t result = V[y] - V[x];
    uint8_t vf = V[y] >= V[x] ? 0x01 : 0x00;
    V[x] = static_cast<uint8_t>(result);
    V[VF] = vf;
}

void CPU::shiftRight(uint8_t index)
{
    uint8_t vf = V[index] & 0x1;
    V[index] >>= 1;
    V[VF] = vf;
}
void CPU::shiftLeft(uint8_t index)
{
    uint8_t vf = (V[index] & 0x80) >> 7;
    V[index] <<= 1;
    V[VF] = vf;
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

// --- Memory Operations ---
void CPU::loadRegistersFromMemory(uint8_t index)
{
    for (uint8_t i = 0; i <= index; i++)
    {
        V[i] = memory.read(indexRegister + i);
    }
}

void CPU::saveRegistersToMemory(uint8_t index)
{
    for (uint8_t i = 0; i <= index; i++)
    {
        memory.write(indexRegister + i, V[i]);
    }
}

void CPU::writeBCDToMemory(uint8_t index)
{
    uint8_t value = V[index];
    memory.write(indexRegister, value / 100 % 10);
    memory.write(indexRegister + 1, value / 10 % 10);
    memory.write(indexRegister + 2, value % 10);
}

void CPU::addRegisterToIndex(uint8_t index)
{
    indexRegister += V[index];
}

void CPU::waitForKeyPress(uint8_t index)
{
    waitingForKeyPress = true;
    uint8_t key = keypad.any();
    if (key == 0xFF)
    {
        // need to rerun the operation.
        programCounter -= 2;
        return;
    }

    V[index] = key;
    waitingForKeyPress = false;
    waitingForKeyRelease = key;
}

bool CPU::waiting()
{
    if (waitingForKeyRelease != 0xFF)
    {
        bool pressed = keypad.isPressed(waitingForKeyRelease);
        if (pressed) return true;
        waitingForKeyRelease = 0xFF;
    }
    return false;
}
