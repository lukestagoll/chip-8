cmake_minimum_required(VERSION 3.16)

project(chip8)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)


find_program(CCACHE_PROGRAM ccache)
if(CCACHE_PROGRAM)
  set(CMAKE_CXX_COMPILER_LAUNCHER "${CCACHE_PROGRAM}")
  set(CMAKE_C_COMPILER_LAUNCHER "${CCACHE_PROGRAM}")
endif()

if(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX OR CMAKE_COMPILER_IS_CLANG)
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS}")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
endif()

# Set build parallelism
include(ProcessorCount)
ProcessorCount(N)
if(NOT N EQUAL 0)
  set(CMAKE_BUILD_PARALLEL_LEVEL ${N})
endif()

add_subdirectory(external/SDL)

set(CORE_SOURCES
    src/core/Chip8.cpp
    src/core/CPU.cpp
    src/core/Display.cpp
    src/core/Keypad.cpp
    src/core/Memory.cpp
    src/core/Timer.cpp
    src/core/opcode/Opcode.cpp
    src/core/opcode/handlers/Handle0x0.cpp
    src/core/opcode/handlers/Handle0x1.cpp
    src/core/opcode/handlers/Handle0x2.cpp
    src/core/opcode/handlers/Handle0x3.cpp
    src/core/opcode/handlers/Handle0x4.cpp
    src/core/opcode/handlers/Handle0x5.cpp
    src/core/opcode/handlers/Handle0x6.cpp
    src/core/opcode/handlers/Handle0x7.cpp
    src/core/opcode/handlers/Handle0x8.cpp
    src/core/opcode/handlers/Handle0x9.cpp
    src/core/opcode/handlers/Handle0xA.cpp
    src/core/opcode/handlers/Handle0xB.cpp
    src/core/opcode/handlers/Handle0xC.cpp
    src/core/opcode/handlers/Handle0xD.cpp
    src/core/opcode/handlers/Handle0xE.cpp
    src/core/opcode/handlers/Handle0xF.cpp
)

set(PLATFORM_SOURCES
    src/platform/Application.cpp
    src/platform/Audio.cpp
    src/platform/EmulationClock.cpp
    src/platform/EventHandler.cpp
    src/platform/Keymap.cpp
    src/platform/Renderer.cpp
    src/platform/Texture.cpp
    src/platform/Window.cpp
)

# Add the source files to the executable target
add_executable(chip8
    src/main.cpp
    ${CORE_SOURCES}
    ${PLATFORM_SOURCES}
)

if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(chip8 PRIVATE
        $<$<CONFIG:Release>:-O2 -march=native>
    )
endif()


# Add the include directories for the target
target_include_directories(chip8 PRIVATE
    external/SDL/include
    src/core
    src/core/opcode
    src/platform
)

target_link_libraries(chip8 PRIVATE SDL3)

# Set the output directory for the executable
set_target_properties(chip8 PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
    OUTPUT_NAME "chip8"
)

file(COPY ${CMAKE_SOURCE_DIR}/roms DESTINATION ${CMAKE_BINARY_DIR}/bin )

# Enable link time optimization for Release builds
include(CheckIPOSupported)
check_ipo_supported(RESULT ipo_supported OUTPUT ipo_error)
if(ipo_supported)
  set_property(TARGET chip8 PROPERTY INTERPROCEDURAL_OPTIMIZATION_RELEASE TRUE)
endif()