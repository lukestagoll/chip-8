# CHIP-8 Emulator

A personal project to create a CHIP-8 interpreter in C++, following 
[tobiasvl's guide](https://tobiasvl.github.io/blog/write-a-chip-8-emulator/). This serves as my gateway into emulator development and low-level systems programming.

## Overview

This project aims to replicate the functionality of the original CHIP-8 interpreter.

## Specifications

- 4KB RAM
  - 4096 bytes (0x000 to 0xFFF)
  - 0x000 to 0x1FF is reserved for the interpreter
  - 0x200 to 0xFFF is available for user programs
- 64x32 monochrome display
  - no color or grayscale, just black and white
- Simple sound output
  - single tone, beeps when the sound timer is non-zero
- Program counter
  - 16-bit register that tracks the current instruction (2 bytes per instruction)
  - Starts at 0x200
- Stack for subroutine/function calls
  - 16 levels deep
- A 16-bit index register (I)
  - Points to memory addresses
- 16 8-bit registers (V0 to VF)
  - Used to store values, loop counters, temporary data, etc.
  - VF is used as a flag register
- 8-bit delay and sound timers 
  - Count down at 60Hz
  - Delay timer controls the speed of the game
  - Sound timer beeps when non-zero


## Prerequisites
Create a `roms` directory in the root of the project to store CHIP-8 ROM files.

Head to https://github.com/Timendus/chip8-test-suite/releases and download the `1-chip8-logo.ch8` and place it in the `roms` directory.