#include "CPU.h"
#include "Memory.h"
#include "Opcode.h"
#include <ios>
#include <iostream>

CPU::CPU(Memory &mem, Display &disp, Timer &delay, Timer &sound, Keypad &keypad)
    : memory(mem), display(disp), delayTimer(delay), soundTimer(sound), keypad(keypad) {}

// --- Program Control / Flow Execution ---

CPUStatus CPU::cycle()
{
    if (programCounter >= Memory::MEMORY_LIMIT)
    {
        std::cerr << "Error: program counter out of bounds - 0x" << std::hex << programCounter - 2 << std::endl;
        return CPUStatus::ERROR_PROGRAM_COUNTER_OUT_OF_BOUNDS;
    }

    // Combine two 8-bit values into a single 16-bit opcode
    uint16_t opcode = memory.read(programCounter) << 8 | memory.read(programCounter + 1);
    programCounter += 2;

    return Opcode::execute(opcode, *this);
}

CPUStatus CPU::callSubroutine(uint16_t address)
{

    if (stackPointer >= 16)
    {
        std::cerr << "Error: stack overflow" << std::endl;
        return CPUStatus::ERROR_STACK_OVERFLOW;
    }
    stack[stackPointer++] = programCounter;

    programCounter = address;
    return CPUStatus::OK;
}

CPUStatus CPU::exitSubroutine()
{
    if (stackPointer == 0)
    {
        std::cerr << "Error: stack empty" << std::endl;
        return CPUStatus::ERROR_STACK_EMPTY;
    }
    programCounter = stack[--stackPointer];
    return CPUStatus::OK;
}

CPUStatus CPU::drawSprite(uint8_t vx, uint8_t vy, uint8_t n)
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
    return CPUStatus::OK;
}

// --- Arithmetic and Logic Instructions ---

CPUStatus CPU::addRegisters(uint8_t x, uint8_t y)
{
    uint16_t sum = V[x] + V[y];
    uint8_t vf = sum > 0xFF ? 0x01 : 0x00;
    V[x] = static_cast<uint8_t>(sum);
    V[VF] = vf;
    return CPUStatus::OK;
}

CPUStatus CPU::subtractRegisters(uint8_t x, uint8_t y)
{
    uint16_t result = V[x] - V[y];
    uint8_t vf = V[x] >= V[y] ? 0x01 : 0x00;
    V[x] = static_cast<uint8_t>(result);
    V[VF] = vf;
    return CPUStatus::OK;
}

CPUStatus CPU::subtractReversed(uint8_t x, uint8_t y)
{
    uint16_t result = V[y] - V[x];
    uint8_t vf = V[y] >= V[x] ? 0x01 : 0x00;
    V[x] = static_cast<uint8_t>(result);
    V[VF] = vf;
    return CPUStatus::OK;
}

CPUStatus CPU::shiftRight(uint8_t index)
{
    uint8_t vf = V[index] & 0x1;
    V[index] >>= 1;
    V[VF] = vf;
    return CPUStatus::OK;
}
CPUStatus CPU::shiftLeft(uint8_t index)
{
    uint8_t vf = (V[index] & 0x80) >> 7;
    V[index] <<= 1;
    V[VF] = vf;
    return CPUStatus::OK;
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
CPUStatus CPU::loadRegistersFromMemory(uint8_t index)
{
    for (uint8_t i = 0; i <= index; i++)
    {
        V[i] = memory.read(indexRegister + i);
    }
    return CPUStatus::OK;
}

CPUStatus CPU::saveRegistersToMemory(uint8_t index)
{
    for (uint8_t i = 0; i <= index; i++)
    {
        memory.write(indexRegister + i, V[i]);
    }
    return CPUStatus::OK;
}

CPUStatus CPU::writeBCDToMemory(uint8_t index)
{
    uint8_t value = V[index];
    memory.write(indexRegister, value / 100 % 10);
    memory.write(indexRegister + 1, value / 10 % 10);
    memory.write(indexRegister + 2, value % 10);
    return CPUStatus::OK;
}

CPUStatus CPU::addRegisterToIndex(uint8_t index)
{
    indexRegister += V[index];
    return CPUStatus::OK;
}

CPUStatus CPU::waitForKeyPress(uint8_t index)
{
    waitingForKeyPress = true;
    uint8_t key = keypad.any();
    if (key == 0xFF)
    {
        // need to rerun the operation.
        programCounter -= 2;
        return CPUStatus::OK;
    }

    V[index] = key;
    waitingForKeyPress = false;
    waitingForKeyRelease = key;
    return CPUStatus::OK;
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


CPUStatus CPU::unknownOperation(uint8_t opcode)
{
    std::cerr << "Error: Unknown opcode 0x" << std::hex << opcode << " at address 0x" << programCounter - 2 << std::endl;
    return CPUStatus::ERROR_UNKNOWN_OPCODE;
}