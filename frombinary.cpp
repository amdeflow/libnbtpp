#include <cstring>
#include "binary.hpp"

NBT::Tag NBT::FromBinary::readTag(NBT::TagType type, std::deque<std::uint8_t> &input, NBT::Endianness endianness) {
    switch (type) {
        case TagType::TagByte:
            return readTagByte(input);
        case TagType::TagShort:
            return readTagShort(input, endianness);
        case TagType::TagInt:
            return readTagInt(input, endianness);
        case TagType::TagLong:
            return readTagLong(input, endianness);
        case TagType::TagFloat:
            return readTagFloat(input, endianness);
        case TagType::TagDouble:
            return readTagDouble(input, endianness);
        case TagType::TagByteArray:
            return readTagByteArray(input, endianness);
        case TagType::TagString:
            return readTagString(input, endianness);
        case TagType::TagList:
            return readTagList(input, endianness);
        case TagType::TagCompound:
            return readTagCompound(input, endianness);
        case TagType::TagIntArray:
            return readTagIntArray(input, endianness);
        case TagType::TagLongArray:
            return readTagLongArray(input, endianness);
        default:
            throw TypeNotMatchedException();
    }
}

std::string NBT::FromBinary::readTagName(std::deque<std::uint8_t> &input, Endianness endianness) {
    std::vector<std::uint8_t> blen(input.begin(), input.begin() + 2);
    swapEndianness(blen, endianness);

    for (int i = 0; i < 2; ++i) {
        input.pop_front();
    }

    union {
        std::uint8_t data[2];
        std::uint16_t len;
    } convert{};

    std::memcpy(convert.data, blen.data(), sizeof(std::uint16_t));

    std::vector<std::uint8_t> chars;
    for (std::uint_fast16_t i = 0; i < convert.len; ++i) {
        chars.push_back(input.front());
        input.pop_front();
    }

    return std::string(chars.begin(), chars.end());
}

NBT::TagType NBT::FromBinary::readTagType(std::deque<std::uint8_t> &input) {
    auto btype = input.front();
    input.pop_front();

    return static_cast<TagType>(btype);
}

NBT::Tag NBT::FromBinary::readTagByte(std::deque<std::uint8_t> &input) {
    std::int8_t byte = input.front();
    input.pop_front();

    return Tag(byte);
}

NBT::Tag NBT::FromBinary::readTagShort(std::deque<std::uint8_t> &input, Endianness endianness) {
    std::vector<std::uint8_t> bnum(input.begin(), input.begin() + 2);
    swapEndianness(bnum, endianness);

    for (std::uint_fast8_t i = 0; i < 2; ++i) {
        input.pop_front();
    }

    union {
        std::uint8_t data[2];
        std::int16_t num;
    } convert{};

    std::memcpy(convert.data, bnum.data(), sizeof(std::int16_t));

    return Tag(convert.num);
}

NBT::Tag NBT::FromBinary::readTagInt(std::deque<std::uint8_t> &input, Endianness endianness) {
    std::vector<std::uint8_t> bnum(input.begin(), input.begin() + 4);
    swapEndianness(bnum, endianness);

    for (std::uint_fast8_t i = 0; i < 4; ++i) {
        input.pop_front();
    }

    union {
        std::uint8_t data[4];
        std::int32_t num;
    } convert{};

    std::memcpy(convert.data, bnum.data(), sizeof(std::int32_t));

    return Tag(convert.num);
}

NBT::Tag NBT::FromBinary::readTagLong(std::deque<std::uint8_t> &input, Endianness endianness) {
    std::vector<std::uint8_t> bnum(input.begin(), input.begin() + 8);
    swapEndianness(bnum, endianness);

    for (std::uint_fast8_t i = 0; i < 8; ++i) {
        input.pop_front();
    }

    union {
        std::uint8_t data[8];
        std::int64_t num;
    } convert{};

    std::memcpy(convert.data, bnum.data(), sizeof(std::int64_t));

    return Tag(convert.num);
}

NBT::Tag NBT::FromBinary::readTagFloat(std::deque<std::uint8_t> &input, Endianness endianness) {
    std::vector<std::uint8_t> bnum(input.begin(), input.begin() + 4);
    swapEndianness(bnum, endianness);

    for (std::uint_fast8_t i = 0; i < 4; ++i) {
        input.pop_front();
    }

    union {
        std::uint8_t data[4];
        float num;
    } convert{};

    std::memcpy(convert.data, bnum.data(), sizeof(float));

    return Tag(convert.num);
}

NBT::Tag NBT::FromBinary::readTagDouble(std::deque<std::uint8_t> &input, Endianness endianness) {
    std::vector<std::uint8_t> bnum(input.begin(), input.begin() + 8);
    swapEndianness(bnum, endianness);

    for (std::uint_fast8_t i = 0; i < 8; ++i) {
        input.pop_front();
    }

    union {
        std::uint8_t data[8];
        double num;
    } convert{};

    std::memcpy(convert.data, bnum.data(), sizeof(double));

    return Tag(convert.num);
}

NBT::Tag NBT::FromBinary::readTagByteArray(std::deque<std::uint8_t> &input, NBT::Endianness endianness) {
    std::vector<std::uint8_t> blen(input.begin(), input.begin() + 4);
    swapEndianness(blen, endianness);

    for (int i = 0; i < 4; ++i) {
        input.pop_front();
    }

    union {
        std::uint8_t data[4];
        std::int32_t size;
    } convert{};

    std::memcpy(convert.data, blen.data(), sizeof(std::int32_t));

    std::vector<std::int8_t> bytes;
    for (std::int_fast32_t i = 0; i < convert.size; ++i) {
        bytes.push_back(input.front());
        input.pop_front();
    }

    return Tag(bytes);
}

NBT::Tag NBT::FromBinary::readTagString(std::deque<std::uint8_t> &input, Endianness endianness) {
    return Tag(readTagName(input, endianness));
}

NBT::Tag NBT::FromBinary::readTagList(std::deque<std::uint8_t> &input, NBT::Endianness endianness) {
    auto type = readTagType(input);

    std::vector<std::uint8_t> blen(input.begin(), input.begin() + 4);
    swapEndianness(blen, endianness);

    for (int i = 0; i < 4; ++i) {
        input.pop_front();
    }

    union {
        std::uint8_t data[4];
        std::int32_t size;
    } convert{};

    std::memcpy(convert.data, blen.data(), sizeof(std::int32_t));

    std::vector<Tag> tags;
    for (std::uint_fast32_t i = 0; i < convert.size; ++i) {
        tags.push_back(readTag(type, input, endianness));
    }

    return Tag(tags);
}

NBT::Tag NBT::FromBinary::readTagCompound(std::deque<std::uint8_t> &input, NBT::Endianness endianness) {
    std::map<std::string, Tag> tags;
    TagType type;
    std::string name;

    while (input.front() != static_cast<std::uint8_t>(TagType::TagEnd)) {
        type = readTagType(input);
        name = readTagName(input, endianness);

        tags.insert({ name, readTag(type, input, endianness) });
    }

    input.pop_front();

    return Tag(tags);
}

NBT::Tag NBT::FromBinary::readTagIntArray(std::deque<std::uint8_t> &input, Endianness endianness) {
    std::vector<std::uint8_t> blen(input.begin(), input.begin() + 4);
    swapEndianness(blen, endianness);

    for (int i = 0; i < 4; ++i) {
        input.pop_front();
    }

    union {
        std::uint8_t data[4];
        std::int32_t size;
    } convert{};

    std::memcpy(convert.data, blen.data(), sizeof(std::int32_t));

    std::vector<std::int32_t> ints;
    for (std::int_fast32_t i = 0; i < convert.size; ++i) {
        union {
            std::uint8_t data[4];
            std::int32_t num;
        } nconvert{};

        for (auto &j : nconvert.data) {
            j = input.front();
            input.pop_front();
        }

        ints.push_back(nconvert.num);
    }

    return Tag(ints);
}

NBT::Tag NBT::FromBinary::readTagLongArray(std::deque<std::uint8_t> &input, Endianness endianness) {
    std::vector<std::uint8_t> blen(input.begin(), input.begin() + 4);
    swapEndianness(blen, endianness);

    for (int i = 0; i < 4; ++i) {
        input.pop_front();
    }

    union {
        std::uint8_t data[4];
        std::int32_t size;
    } convert{};

    std::memcpy(convert.data, blen.data(), sizeof(std::int32_t));

    std::vector<std::int64_t> longs;
    for (std::int_fast32_t i = 0; i < convert.size; ++i) {
        union {
            std::uint8_t data[4];
            std::int64_t num;
        } nconvert{};

        for (auto &j : nconvert.data) {
            j = input.front();
            input.pop_front();
        }

        longs.push_back(nconvert.num);
    }

    return Tag(longs);
}