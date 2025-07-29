#include "CPU.h"
#include "Memory.h"
#include "Opcode.h"
#include <ios>
#include <iostream>

CPU::CPU(Memory &mem, Chip8Display &disp, Timer &delay, Timer &sound, Keypad &keypad_)
    : memory_(mem), display_(disp), delayTimer_(delay), soundTimer_(sound), keypad_(keypad_) {}

// --- Program Control / Flow Execution ---

CPUStatus CPU::cycle()
{
    if (programCounter_ >= Memory::MEMORY_LIMIT)
    {
        std::cerr << "Error: program counter out of bounds - 0x" << std::hex << programCounter_ - 2 << std::endl;
        return CPUStatus::ERROR_PROGRAM_COUNTER_OUT_OF_BOUNDS;
    }

    // Combine two 8-bit values into a single 16-bit opcode
    uint16_t opcode = memory_.read(programCounter_) << 8 | memory_.read(programCounter_ + 1);
    programCounter_ += 2;

    return Opcode::execute(opcode, *this);
}

CPUStatus CPU::callSubroutine(uint16_t address)
{

    if (stackPointer_ >= 16)
    {
        std::cerr << "Error: stack overflow" << std::endl;
        return CPUStatus::ERROR_STACK_OVERFLOW;
    }
    stack_[stackPointer_++] = programCounter_;

    programCounter_ = address;
    return CPUStatus::OK;
}

CPUStatus CPU::exitSubroutine()
{
    if (stackPointer_ == 0)
    {
        std::cerr << "Error: stack empty" << std::endl;
        return CPUStatus::ERROR_STACK_EMPTY;
    }
    programCounter_ = stack_[--stackPointer_];
    return CPUStatus::OK;
}

CPUStatus CPU::drawSprite(uint8_t vx, uint8_t vy, uint8_t n)
{
    // wrap the coordinates - since display width & height are powers of 2, can use bitwise `AND` rather than modulo.
    uint8_t x = V_[vx] & (display_.WIDTH - 1);
    uint8_t y = V_[vy] & (display_.HEIGHT - 1);
    uint16_t spriteAddress = indexRegister_;

    bool collision = false;

    for (uint8_t row = 0; row < n; row++)
    {
        uint8_t spriteByte = memory_.read(spriteAddress + row);
        for (uint8_t col = 0; col < 8; col++)
        {
            if ((spriteByte & (0x80 >> col)) == 0) continue;
#ifdef CLIP_SPRITES
            uint16_t px = x + col;
            uint16_t py = y + row;
            if (px >= display_.WIDTH || py >= display_.HEIGHT) continue;
#else
            uint8_t px = (x + col) & (display_.WIDTH - 1);
            uint8_t py = (y + row) & (display_.HEIGHT - 1);

#endif
            if (display_.flipPixel(px, py))
            {
                collision = true;
            }
        }
    }

    V_[0xF] = collision ? 1 : 0;
    return CPUStatus::OK;
}

// --- Arithmetic and Logic Instructions ---

CPUStatus CPU::addRegisters(uint8_t x, uint8_t y)
{
    uint16_t sum = V_[x] + V_[y];
    uint8_t vf = sum > 0xFF ? 0x01 : 0x00;
    V_[x] = static_cast<uint8_t>(sum);
    V_[VF] = vf;
    return CPUStatus::OK;
}

CPUStatus CPU::subtractRegisters(uint8_t x, uint8_t y)
{
    uint16_t result = V_[x] - V_[y];
    uint8_t vf = V_[x] >= V_[y] ? 0x01 : 0x00;
    V_[x] = static_cast<uint8_t>(result);
    V_[VF] = vf;
    return CPUStatus::OK;
}

CPUStatus CPU::subtractReversed(uint8_t x, uint8_t y)
{
    uint16_t result = V_[y] - V_[x];
    uint8_t vf = V_[y] >= V_[x] ? 0x01 : 0x00;
    V_[x] = static_cast<uint8_t>(result);
    V_[VF] = vf;
    return CPUStatus::OK;
}

CPUStatus CPU::shiftRight(uint8_t index)
{
    uint8_t vf = V_[index] & 0x1;
    V_[index] >>= 1;
    V_[VF] = vf;
    return CPUStatus::OK;
}
CPUStatus CPU::shiftLeft(uint8_t index)
{
    uint8_t vf = (V_[index] & 0x80) >> 7;
    V_[index] <<= 1;
    V_[VF] = vf;
    return CPUStatus::OK;
}

// --- Comparison ---
bool CPU::equalsRegisters(uint8_t x, uint8_t y) const
{
    return V_[x] == V_[y];
}
bool CPU::equalsImmediate(uint8_t index, uint8_t value) const
{
    return V_[index] == value;
}
bool CPU::notEqualsImmediate(uint8_t index, uint8_t value) const
{
    return V_[index] != value;
}

// --- Memory Operations ---
CPUStatus CPU::loadRegistersFromMemory(uint8_t index)
{
    for (uint8_t i = 0; i <= index; i++)
    {
        V_[i] = memory_.read(indexRegister_ + i);
    }
    return CPUStatus::OK;
}

CPUStatus CPU::saveRegistersToMemory(uint8_t index)
{
    for (uint8_t i = 0; i <= index; i++)
    {
        memory_.write(indexRegister_ + i, V_[i]);
    }
    return CPUStatus::OK;
}

CPUStatus CPU::writeBCDToMemory(uint8_t index)
{
    uint8_t value = V_[index];
    memory_.write(indexRegister_, value / 100 % 10);
    memory_.write(indexRegister_ + 1, value / 10 % 10);
    memory_.write(indexRegister_ + 2, value % 10);
    return CPUStatus::OK;
}

CPUStatus CPU::addRegisterToIndex(uint8_t index)
{
    indexRegister_ += V_[index];
    return CPUStatus::OK;
}

CPUStatus CPU::waitForKeyPress(uint8_t index)
{
    waitingForKeyPress_ = true;
    uint8_t key = keypad_.any();
    if (key == 0xFF)
    {
        // need to rerun the operation.
        programCounter_ -= 2;
        return CPUStatus::OK;
    }

    V_[index] = key;
    waitingForKeyPress_ = false;
    waitingForKeyRelease_ = key;
    return CPUStatus::OK;
}

bool CPU::waiting()
{
    if (waitingForKeyRelease_ != 0xFF)
    {
        bool pressed = keypad_.isPressed(waitingForKeyRelease_);
        if (pressed) return true;
        waitingForKeyRelease_ = 0xFF;
    }
    return false;
}


CPUStatus CPU::unknownOperation(uint8_t opcode)
{
    std::cerr << "Error: Unknown opcode 0x" << std::hex << opcode << " at address 0x" << programCounter_ - 2 << std::endl;
    return CPUStatus::ERROR_UNKNOWN_OPCODE;
}
