# CHIP-8 Emulator

A CHIP-8 emulator written in C++17, built as a learning project to understand how CPUs, memory, and displays work at a low level.

> **Status:** Work in progress. ROM and font loading are done; the display and opcodes are next.

## What is CHIP-8?

CHIP-8 is a simple interpreted language from the 1970s, designed to make writing games for early microcomputers easier. With 4 KB of memory, 16 registers, a 64×32 monochrome display, and about 35 instructions, it's a classic first project for emulator development.

## Features

- [x] 4 KB memory, 16 general-purpose registers, index register, program counter, and stack
- [x] ROM loading at `0x200` and built-in font sprites at `0x050`
- [ ] SDL2 display window
- [ ] Fetch-decode-execute loop (starting with the IBM logo opcodes)
- [ ] Unit tests with GoogleTest
- [ ] Full opcode set, with configurable quirks for CHIP-8 variants
- [ ] Timers, keyboard input, and sound
- [ ] Passing the [Timendus CHIP-8 test suite](https://github.com/Timendus/chip8-test-suite)

## Design

The emulator core (the `Chip8` class) is kept completely separate from SDL. This means the core can be unit tested on its own, without opening a window, and the frontend could be swapped out later.

```
src/      emulator core and SDL frontend
tests/    unit tests
roms/     your ROM files (not included, see below)
```

## Building

Requirements:

- A C++17 compiler (AppleClang, GCC, or Clang)
- CMake
- SDL2 (for the display): `brew install sdl2` on macOS

Build:

```
cmake -S . -B build
cmake --build build
```

## Running

```
./build/chip8 roms/<rom-file>.ch8
```

## ROMs

No ROM files are included in this repository. To test the emulator, download the [Timendus CHIP-8 test suite](https://github.com/Timendus/chip8-test-suite) and place the `.ch8` files in the `roms/` folder. A good first ROM is `2-ibm-logo.ch8`, which needs only six opcodes to run.

## References

- [Cowgod's CHIP-8 Technical Reference](http://devernay.free.fr/hacks/chip8/C8TECH10.HTM)
- [Tobias V. Langhoff's guide to making a CHIP-8 emulator](https://tobiasvl.github.io/blog/write-a-chip-8-emulator/)
- [Timendus CHIP-8 test suite](https://github.com/Timendus/chip8-test-suite)

## License

MIT. See [LICENSE](LICENSE).
