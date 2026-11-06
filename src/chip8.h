#pragma once

#include <array>
#include <cstddef>
#include <cstdint>
#include <string>
#include <vector>

// The CHIP-8 virtual machine: memory, registers, timers, and display.
// This class knows nothing about SDL, windows, or keyboards. A front end
// drives it and reads its state; tests can do the same without a window.
class Chip8 {
public:
    // --- Machine constants ---------------------------------------------------
    static constexpr std::size_t kMemorySize    = 4096;  // 4 KB of RAM
    static constexpr std::size_t kNumRegisters  = 16;    // V0..VF
    static constexpr std::size_t kStackSize     = 16;    // 16 levels of nested calls
    static constexpr std::size_t kDisplayWidth  = 64;
    static constexpr std::size_t kDisplayHeight = 32;

    static constexpr std::uint16_t kFontStart    = 0x050; // where font sprites live
    static constexpr std::uint16_t kProgramStart = 0x200; // where ROMs are loaded

    using Display = std::array<bool, kDisplayWidth * kDisplayHeight>;

    Chip8();

    // Put the machine back in its power-on state: clear everything,
    // reload the font, and point the program counter at 0x200.
    void reset();

    // Copy program bytes into memory at 0x200.
    // Throws std::length_error if the program doesn't fit.
    void loadProgram(const std::vector<std::uint8_t>& program);

    // Read a ROM file from disk and load it with loadProgram().
    // Throws std::runtime_error if the file can't be read.
    void loadRomFile(const std::string& path);

    // --- Read-only access to machine state -----------------------------------
    // Used by the front end (to draw) and by tests (to check results).
    std::uint8_t  memory(std::uint16_t address) const { return memory_.at(address); }
    std::uint8_t  v(std::size_t index) const          { return v_.at(index); }
    std::uint16_t indexRegister() const               { return i_; }
    std::uint16_t pc() const                          { return pc_; }
    std::uint8_t  sp() const                          { return sp_; }
    std::uint8_t  delayTimer() const                  { return delayTimer_; }
    std::uint8_t  soundTimer() const                  { return soundTimer_; }
    const Display& display() const                    { return display_; }

private:
    std::array<std::uint8_t, kMemorySize>   memory_{};
    std::array<std::uint8_t, kNumRegisters> v_{};      // general registers V0..VF
    std::uint16_t i_  = 0;                             // index register "I"
    std::uint16_t pc_ = kProgramStart;                 // program counter
    std::array<std::uint16_t, kStackSize>   stack_{};  // return addresses
    std::uint8_t  sp_ = 0;                             // next free stack slot
    std::uint8_t  delayTimer_ = 0;
    std::uint8_t  soundTimer_ = 0;
    Display display_{};                                // true = pixel on
};
