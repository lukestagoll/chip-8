# CHIP-8 Emulator

A personal project to create a CHIP-8 interpreter in C++ & SDL3, following multiple guides and resources. This serves as my gateway into emulator development and low-level systems programming.

## Overview

This project aims to replicate the functionality of the original CHIP-8 interpreter. Currently in active development with basic display functionality working.

## Current Implementation Status
### Implemented Opcodes
- `00E0` - Clear display
- `00EE` - Return from subroutine
- `1NNN` - jump to address NNN
- `2NNN` - execute subroutine starting at address NNN
- `3XNN` - if VX == NN, skip next instruction (i.e. if VX != NN then)
- `4XNN` - if VX != NN, skip next instruction (i.e. if VX == NN then)
- `5XY0` - if VX == VY, skip next instruction (i.e. if VX != VY then)
- `6XNN` - Set register VX to NN
- `7XNN` - Add NN to VX (VX += NN)
- `9XNN` - if VX != VY, skip next instruction (i.e. if VX == VY then)
- `ANNN` - Set index register I to NNN
- `DXYN` - Draw a sprite at position VX, VY with N bytes data starting at index register I

### Current Limitations
- Only basic opcodes implemented (4 out of 35 total)
- Program execution stops when unimplemented opcodes are encountered
- No input handling yet
- No sound system implemented

### Tested ROMs

The following ROM images have been tested and run successfully:
- [CHIP-8 Test Suite: CHIP-8 splash screen (1-chip8-logo.ch8)](https://github.com/Timendus/chip8-test-suite#chip-8-splash-screen)
- [CHIP-8 Test Suite: IBM logo (2-ibm-logo.ch8)](https://github.com/Timendus/chip8-test-suite#ibm-logo)

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


## Getting Started
### Prerequisites
- **Clang Compiler**
- **CMake**

### Clone the Repo
This project uses git submodules for dependencies. Clone with:
```bash
git clone --recurse-submodules https://github.com/yourusername/chip-8.git
cd chip-8
```

If you've already cloned without submodules, initialize them:
```bash
git submodule update --init --recursive
```

### Setup ROMs Directory
Create a `roms` directory in the root of the project to store CHIP-8 ROM files:

```bash
mkdir roms
```

Download the test ROM:
- Head to https://github.com/Timendus/chip8-test-suite/releases
- Download `1-chip8-logo.ch8` and place it in the `roms` directory

### Build and Run
```bash
# Create & Enter build directory
mkdir build && cd build

# Configure with CMake
cmake ..

# Build the project
make

# Run
./bin/chip8 /roms/1-chip8-logo.ch8
```

# Resources Used
- [Awesome CHIP-8](https://github.com/tobiasvl/awesome-chip-8) - Curated resources
- [Tobias V. Langhoff's CHIP-8 Guide](https://tobiasvl.github.io/blog/write-a-chip-8-emulator/) - Primary tutorial
- [Laurence Muller's CHIP-8 Guide](https://multigesture.net/articles/how-to-write-an-emulator-chip-8-interpreter/) - Implementation guidance
- [Matt Mikolay's CHIP-8 Technical Reference](https://github.com/mattmikolay/chip-8/wiki/CHIP%E2%80%908-Technical-Reference) - Detailed specifications
- [CHIP-8 Instruction Set](https://johnearnest.github.io/Octo/docs/chip8ref.pdf) - Comprehensive instruction set
- [Timendus' CHIP-8 Test Suite](https://github.com/Timendus/chip8-test-suite) - Testing and validation
- [CHIP-8 Wikipedia Page](https://en.wikipedia.org/wiki/CHIP-8) - Further information
