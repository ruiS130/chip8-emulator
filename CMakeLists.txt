cmake_minimum_required(VERSION 3.20)
project(chip8 LANGUAGES CXX)

# Use exactly C++17, and fail rather than silently falling back to an older
# standard. EXTENSIONS OFF means -std=c++17 instead of -std=gnu++17, so we
# don't accidentally rely on compiler-specific extensions.
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Lets CLion (and tools like clangd) see the exact compiler flags per file.
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Turn on useful warnings for all of our own targets.
if(MSVC)
    add_compile_options(/W4)
else()
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# --- Emulator core -----------------------------------------------------------
# A static library with NO SDL dependency. The SDL front end (phase 2) and the
# unit tests (phase 4) both link against this, which keeps the core testable
# on its own. If someone #includes SDL in here, it won't link — by design.
add_library(chip8_core
    src/chip8.cpp
)
target_include_directories(chip8_core PUBLIC src)

# --- Executable ---------------------------------------------------------------
add_executable(chip8
    src/main.cpp
)
target_link_libraries(chip8 PRIVATE chip8_core)
