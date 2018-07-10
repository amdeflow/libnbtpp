#ifndef NBTPP_BINARY_HPP
#define NBTPP_BINARY_HPP

#include <deque>
#include "endianness.hpp"
#include "nbtpp.hpp"

namespace NBT {
    namespace ToBinary {
        std::vector<std::uint8_t> toBinary(Tag& tag, Endianness endianness);

        std::vector<std::uint8_t> writeTagName(std::string name, Endianness endianness);
        std::vector<std::uint8_t> writeTagType(TagType type);

        std::vector<std::uint8_t> tagByte(Tag& tag);
        std::vector<std::uint8_t> tagShort(Tag& tag, Endianness endianness);
        std::vector<std::uint8_t> tagInt(Tag& tag, Endianness endianness);
        std::vector<std::uint8_t> tagLong(Tag& tag, Endianness endianness);
        std::vector<std::uint8_t> tagFloat(Tag& tag, Endianness endianness);
        std::vector<std::uint8_t> tagDouble(Tag& tag, Endianness endianness);
        std::vector<std::uint8_t> tagByteArray(Tag& tag, Endianness endianness);
        std::vector<std::uint8_t> tagString(Tag& tag, Endianness endianness);
        std::vector<std::uint8_t> tagList(Tag& tag, Endianness endianness);
        std::vector<std::uint8_t> tagCompound(Tag& tag, Endianness endianness);
        std::vector<std::uint8_t> tagIntArray(Tag& tag, Endianness endianness);
        std::vector<std::uint8_t> tagLongArray(Tag& tag, Endianness endianness);
    }

    namespace FromBinary {
        Tag readTag(TagType type, std::deque<std::uint8_t> &input, Endianness endianness);

        std::string readTagName(std::deque<std::uint8_t>& input, Endianness endianness);
        TagType readTagType(std::deque<std::uint8_t>& input);

        Tag readTagByte(std::deque<std::uint8_t>& input);
        Tag readTagShort(std::deque<std::uint8_t>& input, Endianness endianness);
        Tag readTagInt(std::deque<std::uint8_t>& input, Endianness endianness);
        Tag readTagLong(std::deque<std::uint8_t>& input, Endianness endianness);
        Tag readTagFloat(std::deque<std::uint8_t>& input, Endianness endianness);
        Tag readTagDouble(std::deque<std::uint8_t>& input, Endianness endianness);
        Tag readTagByteArray(std::deque<std::uint8_t>& input, Endianness endianness);
        Tag readTagString(std::deque<std::uint8_t>& input, Endianness endianness);
        Tag readTagList(std::deque<std::uint8_t>& input, Endianness endianness);
        Tag readTagCompound(std::deque<std::uint8_t>& input, Endianness endianness);
        Tag readTagIntArray(std::deque<std::uint8_t>& input, Endianness endianness);
        Tag readTagLongArray(std::deque<std::uint8_t>& input, Endianness endianness);
    }
}

#endif