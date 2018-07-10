#include "endianness.hpp"

NBT::Endianness NBT::systemEndianness() {
    union {
        std::uint16_t i;
        std::uint8_t c[2];
    } const bytes = {0x0123};

    return bytes.c[0] == 0x01 ? Endianness::BigEndian : Endianness::LittleEndian;
}

void NBT::swapEndianness(std::vector<std::uint8_t> &bytes, NBT::Endianness toEndianness) {
    if (systemEndianness() != toEndianness) {
        std::reverse(bytes.begin(), bytes.end());
    }
}