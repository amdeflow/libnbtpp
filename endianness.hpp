#ifndef NBTPP_ENDIANNESS_HPP
#define NBTPP_ENDIANNESS_HPP

#include "nbtpp.hpp"

#include <cstdint>
#include <algorithm>

namespace NBT {
    enum class Endianness {
        BigEndian,
        LittleEndian,
    };

    Endianness systemEndianness();

    void swapEndianness(std::vector<std::uint8_t> &bytes, Endianness toEndianness);
};

#endif