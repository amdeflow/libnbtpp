#include "binary.hpp"

#include <algorithm>
#include <cstring>

std::vector<std::uint8_t> NBT::ToBinary::toBinary(Tag& tag, Endianness endianness) {
    switch (tag.type()) {
        case TagType::TagByte:
            return tagByte(tag);
        case TagType::TagShort:
            return tagShort(tag, endianness);
        case TagType::TagInt:
            return tagInt(tag, endianness);
        case TagType::TagLong:
            return tagLong(tag, endianness);
        case TagType::TagFloat:
            return tagFloat(tag, endianness);
        case TagType::TagDouble:
            return tagDouble(tag, endianness);
        case TagType::TagByteArray:
            return tagByteArray(tag, endianness);
        case TagType::TagString:
            return tagString(tag, endianness);
        case TagType::TagList:
            return tagList(tag, endianness);
        case TagType::TagCompound:
            return tagCompound(tag, endianness);
        case TagType::TagIntArray:
            return tagIntArray(tag, endianness);
        case TagType::TagLongArray:
            return tagLongArray(tag, endianness);
        default:
            throw TypeNotMatchedException();
    }
}

std::vector<std::uint8_t> NBT::ToBinary::writeTagName(std::string name, Endianness endianness) {
    if (name.length() >= UINT16_MAX)
        throw SizeException();

    const auto length = static_cast<std::uint16_t>(name.length());

    std::vector<std::uint8_t> output(sizeof(std::uint16_t));
    std::memcpy(output.data(), &length, sizeof(std::uint16_t));

    swapEndianness(output, endianness);

    std::vector<std::uint8_t> vname(name.begin(), name.end());

    output.insert(output.end(), vname.begin(), vname.end());
    return output;
}

std::vector<std::uint8_t> NBT::ToBinary::writeTagType(TagType type) {
    std::vector<std::uint8_t> output;
    output.push_back(static_cast<std::uint8_t>(type));

    return output;
}

std::vector<std::uint8_t> NBT::ToBinary::tagByte(Tag& tag) {
    std::vector<std::uint8_t> output;
    output.push_back(static_cast<std::uint8_t>(tag.tagByte()));

    return output;
}

std::vector<std::uint8_t> NBT::ToBinary::tagShort(NBT::Tag &tag, NBT::Endianness endianness) {
    std::vector<std::uint8_t> output(sizeof(std::int16_t));
    std::memcpy(output.data(), &tag.tagShort(), sizeof(std::int16_t));

    swapEndianness(output, endianness);

    return output;
}

std::vector<std::uint8_t> NBT::ToBinary::tagInt(NBT::Tag &tag, NBT::Endianness endianness) {
    std::vector<std::uint8_t> output(sizeof(std::int32_t));
    std::memcpy(output.data(), &tag.tagInt(), sizeof(std::int32_t));

    swapEndianness(output, endianness);

    return output;
}

std::vector<std::uint8_t> NBT::ToBinary::tagLong(NBT::Tag &tag, NBT::Endianness endianness) {
    std::vector<std::uint8_t> output(sizeof(std::int64_t));
    std::memcpy(output.data(), &tag.tagLong(), sizeof(std::int64_t));

    swapEndianness(output, endianness);

    return output;
}

std::vector<std::uint8_t> NBT::ToBinary::tagFloat(NBT::Tag &tag, NBT::Endianness endianness) {
    std::vector<std::uint8_t> output(sizeof(float));
    std::memcpy(output.data(), &tag.tagFloat(), sizeof(float));

    swapEndianness(output, endianness);

    return output;
}

std::vector<std::uint8_t> NBT::ToBinary::tagDouble(NBT::Tag &tag, NBT::Endianness endianness) {
    std::vector<std::uint8_t> output(sizeof(double));
    std::memcpy(output.data(), &tag.tagDouble(), sizeof(double));

    swapEndianness(output, endianness);

    return output;
}

std::vector<std::uint8_t> NBT::ToBinary::tagByteArray(NBT::Tag &tag, Endianness endianness) {
    if (tag.tagByteArray().size() >= INT32_MAX)
        throw SizeException();

    std::vector<std::uint8_t> output(sizeof(std::int32_t));

    const auto length = static_cast<std::int32_t>(tag.tagByteArray().size());
    std::memcpy(output.data(), &length, sizeof(std::uint16_t));

    swapEndianness(output, endianness);

    std::vector<std::uint8_t> bytes(tag.tagByteArray().size());
    std::memcpy(bytes.data(), tag.tagByteArray().data(), tag.tagByteArray().size());

    output.insert(output.end(), bytes.begin(), bytes.end());

    return output;
}

std::vector<std::uint8_t> NBT::ToBinary::tagString(NBT::Tag &tag, NBT::Endianness endianness) {
    if (tag.tagString().size() >= UINT16_MAX)
        throw SizeException();

    std::vector<std::uint8_t> output(sizeof(std::uint16_t));

    const auto length = static_cast<std::uint16_t>(tag.tagString().size());
    std::memcpy(output.data(), &length, sizeof(std::uint16_t));

    swapEndianness(output, endianness);

    std::vector<std::uint8_t> string(tag.tagString().begin(), tag.tagString().end());
    output.insert(output.end(), string.begin(), string.end());

    return output;
}

std::vector<std::uint8_t> NBT::ToBinary::tagList(NBT::Tag &tag, NBT::Endianness endianness) {
    if (tag.tagList().size() >= INT32_MAX)
        throw SizeException();

    auto type = TagType::TagEnd;

    if (!tag.tagList().empty()) {
        type = tag.tagList()[0].type();

        for (auto &i : tag.tagList()) {
            if (type != i.type()) {
                throw TypeNotMatchedException();
            }
        }
    }

    std::vector<std::uint8_t> output(sizeof(std::int32_t));

    auto btype = writeTagType(type);
    output.insert(output.end(), btype.begin(), btype.end());

    const auto length = static_cast<std::int32_t>(tag.tagList().size());
    std::memcpy(output.data(), &length, sizeof(std::int32_t));

    swapEndianness(output, endianness);

    for (auto &i : tag.tagList()) {
        auto temp = toBinary(i, endianness);
        output.insert(output.end(), temp.begin(), temp.end());
    }

    return output;
}

std::vector<std::uint8_t> NBT::ToBinary::tagCompound(NBT::Tag &tag, NBT::Endianness endianness) {
    std::vector<std::uint8_t> output;

    for (auto &i : tag.tagCompound()) {
        auto type = writeTagType(i.second.type());
        auto name = writeTagName(i.first, endianness);

        output.insert(output.end(), type.begin(), type.end());
        output.insert(output.end(), name.begin(), name.end());

        auto temp = toBinary(i.second, endianness);
        output.insert(output.end(), temp.begin(), temp.end());
    }

    output.push_back(static_cast<std::uint8_t>(TagType::TagEnd));

    return output;
}

std::vector<std::uint8_t> NBT::ToBinary::tagIntArray(NBT::Tag &tag, Endianness endianness) {
    if (tag.tagIntArray().size() >= INT32_MAX)
        throw SizeException();

    std::vector<std::uint8_t> output(sizeof(std::int32_t));

    const auto length = static_cast<std::int32_t>(tag.tagIntArray().size());
    std::memcpy(output.data(), &length, sizeof(std::int32_t));

    swapEndianness(output, endianness);

    std::vector<std::uint8_t> currentNum(sizeof(std::int32_t));
    for (auto &n : tag.tagIntArray()) {
        currentNum.clear();

        std::memcpy(currentNum.data(), &n, sizeof(std::int32_t));
        swapEndianness(currentNum, endianness);
        output.insert(output.end(), currentNum.begin(), currentNum.end());
    }

    return output;
}

std::vector<std::uint8_t> NBT::ToBinary::tagLongArray(NBT::Tag &tag, Endianness endianness) {
    if (tag.tagLongArray().size() >= INT32_MAX)
        throw SizeException();

    std::vector<std::uint8_t> output(sizeof(std::int32_t));

    const auto length = static_cast<std::int32_t>(tag.tagLongArray().size());
    std::memcpy(output.data(), &length, sizeof(std::uint16_t));

    swapEndianness(output, endianness);

    std::vector<std::uint8_t> currentNum(sizeof(std::int64_t));
    for (auto &n : tag.tagLongArray()) {
        currentNum.clear();

        std::memcpy(currentNum.data(), &n, sizeof(std::int64_t));
        swapEndianness(currentNum, endianness);
        output.insert(output.end(), currentNum.begin(), currentNum.end());
    }

    return output;
}
