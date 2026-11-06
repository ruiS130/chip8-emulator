#include "chip8.h"

#include <algorithm>
#include <fstream>
#include <iterator>
#include <stdexcept>

namespace {

// Built-in hex digit sprites 0..F. Each digit is 5 bytes tall and 4 pixels
// wide; the high 4 bits of each byte are the pixels. For example "0":
//   0xF0 = 1111....
//   0x90 = 1..1....
//   0x90 = 1..1....
//   0x90 = 1..1....
//   0xF0 = 1111....
constexpr std::array<std::uint8_t, 80> kFontSprites = {
    0xF0, 0x90, 0x90, 0x90, 0xF0,  // 0
    0x20, 0x60, 0x20, 0x20, 0x70,  // 1
    0xF0, 0x10, 0xF0, 0x80, 0xF0,  // 2
    0xF0, 0x10, 0xF0, 0x10, 0xF0,  // 3
    0x90, 0x90, 0xF0, 0x10, 0x10,  // 4
    0xF0, 0x80, 0xF0, 0x10, 0xF0,  // 5
    0xF0, 0x80, 0xF0, 0x90, 0xF0,  // 6
    0xF0, 0x10, 0x20, 0x40, 0x40,  // 7
    0xF0, 0x90, 0xF0, 0x90, 0xF0,  // 8
    0xF0, 0x90, 0xF0, 0x10, 0xF0,  // 9
    0xF0, 0x90, 0xF0, 0x90, 0x90,  // A
    0xE0, 0x90, 0xE0, 0x90, 0xE0,  // B
    0xF0, 0x80, 0x80, 0x80, 0xF0,  // C
    0xE0, 0x90, 0x90, 0x90, 0xE0,  // D
    0xF0, 0x80, 0xF0, 0x80, 0xF0,  // E
    0xF0, 0x80, 0xF0, 0x80, 0x80,  // F
};

}  // namespace

Chip8::Chip8() {
    reset();
}

void Chip8::reset() {
    memory_.fill(0);
    v_.fill(0);
    stack_.fill(0);
    display_.fill(false);
    i_ = 0;
    pc_ = kProgramStart;
    sp_ = 0;
    delayTimer_ = 0;
    soundTimer_ = 0;

    std::copy(kFontSprites.begin(), kFontSprites.end(),
              memory_.begin() + kFontStart);
}

void Chip8::loadProgram(const std::vector<std::uint8_t>& program) {
    constexpr std::size_t maxSize = kMemorySize - kProgramStart;  // 3584 bytes
    if (program.size() > maxSize) {
        throw std::length_error("ROM is " + std::to_string(program.size()) +
                                " bytes; the maximum is " + std::to_string(maxSize));
    }
    std::copy(program.begin(), program.end(), memory_.begin() + kProgramStart);
}

void Chip8::loadRomFile(const std::string& path) {
    std::ifstream file(path, std::ios::binary);
    if (!file) {
        throw std::runtime_error("Could not open ROM file: " + path);
    }

    // Read the whole file into a vector of bytes.
    std::vector<std::uint8_t> bytes(
        (std::istreambuf_iterator<char>(file)),
        std::istreambuf_iterator<char>());

    loadProgram(bytes);
}  // `file` is closed automatically here, even if loadProgram threw (RAII).
