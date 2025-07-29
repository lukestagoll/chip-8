cmake_minimum_required(VERSION 3.16)

project(chip8-qt)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC OFF)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets Multimedia)

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

set(CORE_HEADERS
    src/core/Chip8.h
    src/core/CPU.h
    src/core/CPUStatus.h
    src/core/Chip8Display.h
    src/core/Font.h
    src/core/Keypad.h
    src/core/Memory.h
    src/core/Timer.h
    src/core/opcode/Opcode.h
)

set(CORE_SOURCES
    src/core/Chip8.cpp
    src/core/CPU.cpp
    src/core/Chip8Display.cpp
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
    src/platform/EmulationClock.cpp
    src/platform/Keymap.cpp
    src/platform/MainWindow.cpp
    src/platform/SoundEffect.cpp
    src/platform/Widget.cpp
)


set(PLATFORM_HEADERS
    src/platform/Action.h
    src/platform/AudioOutput.h
    src/platform/EmulationClock.h
    src/platform/Keymap.h
    src/platform/MainWindow.h
    src/platform/SoundEffect.h
    src/platform/Widget.h
)

qt_add_resources(RESOURCES ${CMAKE_SOURCE_DIR}/assets/resources.qrc)

# Add the source files to the executable target
add_executable(chip8-qt
    src/main.cpp
    ${CORE_HEADERS}
    ${CORE_SOURCES}
    ${PLATFORM_HEADERS}
    ${PLATFORM_SOURCES}
    ${RESOURCES}
)

if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(chip8-qt PRIVATE
        $<$<CONFIG:Release>:-O2 -march=native>
    )
endif()


# Add the include directories for the target
target_include_directories(chip8-qt PRIVATE
    src/core
    src/core/opcode
    src/platform
)

target_link_libraries(chip8-qt PRIVATE Qt6::Core Qt6::Gui Qt6::Widgets Qt6::Multimedia)

# Set the output directory for the executable
set_target_properties(chip8-qt PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
    OUTPUT_NAME "chip8-qt"
)

file(COPY ${CMAKE_SOURCE_DIR}/roms DESTINATION ${CMAKE_BINARY_DIR}/bin)

# Enable link time optimization for Release builds
include(CheckIPOSupported)
check_ipo_supported(RESULT ipo_supported OUTPUT ipo_error)
if(ipo_supported)
  set_property(TARGET chip8-qt PROPERTY INTERPROCEDURAL_OPTIMIZATION_RELEASE TRUE)
endif()
