#include <cstdio>
#include <exception>
#include <iostream>

#include "chip8.h"

// Print `count` bytes of memory starting at `start`, 16 per line.
static void dumpMemory(const Chip8& chip8, std::uint16_t start, std::size_t count) {
    for (std::size_t offset = 0; offset < count; ++offset) {
        auto address = static_cast<std::uint16_t>(start + offset);
        if (offset % 16 == 0) {
            std::printf("%s%04X:", offset == 0 ? "" : "\n", static_cast<unsigned>(address));
        }
        std::printf(" %02X", static_cast<unsigned>(chip8.memory(address)));
    }
    std::printf("\n");
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <rom-file>\n";
        return 1;
    }

    Chip8 chip8;  // lives on the stack; no `new` needed
    try {
        chip8.loadRomFile(argv[1]);
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
        return 1;
    }

    std::cout << "Font sprites at 0x050:\n";
    dumpMemory(chip8, Chip8::kFontStart, 80);
    std::cout << "\nFirst 64 bytes of the program at 0x200:\n";
    dumpMemory(chip8, Chip8::kProgramStart, 64);
    std::printf("\nPC = 0x%03X\n", static_cast<unsigned>(chip8.pc()));
    return 0;
}
