#pragma once

#include <array>
#include <cstdint>

class Memory
{
public:
    static constexpr int MEMORY_LIMIT = 4096;

    uint8_t read(uint16_t address) const;
    void write(uint16_t address, uint8_t value);

    uint8_t safeRead(uint16_t address) const;
    void safeWrite(uint16_t address, uint8_t value);
    void init();

  private:
    /*
        Memory layout:
        0x000-0x1FF: Reserved for interpreter
        0x050-0x0A0: Built in 4x5 pixel font set (0-F). Currently unimplemented.
        0x200-0xFFF: Program ROM and RAM
    */
  std::array<uint8_t, MEMORY_LIMIT> memory_{}; // 4KB of memory
};
