#include "nbtpp.hpp"

NBT::Tag::Tag(NBT::TagByte_t value): m_value(std::make_shared<TagValue_t>(value)) {}
NBT::Tag::Tag(NBT::TagShort_t value): m_value(std::make_shared<TagValue_t>(value)) {}
NBT::Tag::Tag(NBT::TagInt_t value): m_value(std::make_shared<TagValue_t>(value)) {}
NBT::Tag::Tag(NBT::TagLong_t value): m_value(std::make_shared<TagValue_t>(value)) {}
NBT::Tag::Tag(NBT::TagFloat_t value): m_value(std::make_shared<TagValue_t>(value)) {}
NBT::Tag::Tag(NBT::TagDouble_t value): m_value(std::make_shared<TagValue_t>(value)) {}
NBT::Tag::Tag(NBT::TagByteArray_t value): m_value(std::make_shared<TagValue_t>(value)) {}
NBT::Tag::Tag(NBT::TagString_t value): m_value(std::make_shared<TagValue_t>(value)) {}
NBT::Tag::Tag(NBT::TagList_t value): m_value(std::make_shared<TagValue_t>(value)) {}
NBT::Tag::Tag(NBT::TagCompound_t value): m_value(std::make_shared<TagValue_t>(value)) {}
NBT::Tag::Tag(NBT::TagIntArray_t value): m_value(std::make_shared<TagValue_t>(value)) {}
NBT::Tag::Tag(NBT::TagLongArray_t value): m_value(std::make_shared<TagValue_t>(value)) {}

NBT::TagByte_t &NBT::Tag::tagByte() {
    if (type() == TagType::TagByte)
        return std::get<TagByte_t>(*m_value);
    else
        throw TypeNotMatchedException();
}

NBT::TagShort_t &NBT::Tag::tagShort() {
    if (type() == TagType::TagShort)
        return std::get<TagShort_t>(*m_value);
    else
        throw TypeNotMatchedException();
}

NBT::TagInt_t &NBT::Tag::tagInt() {
    if (type() == TagType::TagInt)
        return std::get<TagInt_t>(*m_value);
    else
        throw TypeNotMatchedException();
}

NBT::TagLong_t &NBT::Tag::tagLong() {
    if (type() == TagType::TagLong)
        return std::get<TagLong_t>(*m_value);
    else
        throw TypeNotMatchedException();
}

NBT::TagFloat_t &NBT::Tag::tagFloat() {
    if (type() == TagType::TagFloat)
        return std::get<TagFloat_t>(*m_value);
    else
        throw TypeNotMatchedException();
}

NBT::TagDouble_t &NBT::Tag::tagDouble() {
    if (type() == TagType::TagDouble)
        return std::get<TagDouble_t>(*m_value);
    else
        throw TypeNotMatchedException();
}

NBT::TagByteArray_t &NBT::Tag::tagByteArray() {
    if (type() == TagType::TagByteArray)
        return std::get<TagByteArray_t>(*m_value);
    else
        throw TypeNotMatchedException();
}

NBT::TagString_t &NBT::Tag::tagString() {
    if (type() == TagType::TagString)
        return std::get<TagString_t>(*m_value);
    else
        throw TypeNotMatchedException();
}

NBT::TagList_t &NBT::Tag::tagList() {
    if (type() == TagType::TagList)
        return std::get<TagList_t>(*m_value);
    else
        throw TypeNotMatchedException();
}

NBT::TagCompound_t &NBT::Tag::tagCompound() {
    if (type() == TagType::TagCompound)
        return std::get<TagCompound_t>(*m_value);
    else
        throw TypeNotMatchedException();
}

NBT::TagIntArray_t &NBT::Tag::tagIntArray() {
    if (type() == TagType::TagIntArray)
        return std::get<TagIntArray_t>(*m_value);
    else
        throw TypeNotMatchedException();
}

NBT::TagLongArray_t &NBT::Tag::tagLongArray() {
    if (type() == TagType::TagLongArray)
        return std::get<TagLongArray_t>(*m_value);
    else
        throw TypeNotMatchedException();
}

NBT::TagType NBT::Tag::type() {
    if (std::holds_alternative<TagByte_t>(*m_value)) {
        return TagType::TagByte;
    } else if (std::holds_alternative<TagShort_t>(*m_value)) {
        return TagType::TagShort;
    } else if (std::holds_alternative<TagInt_t>(*m_value)) {
        return TagType::TagInt;
    } else if (std::holds_alternative<TagLong_t>(*m_value)) {
        return TagType::TagLong;
    } else if (std::holds_alternative<TagFloat_t>(*m_value)) {
        return TagType::TagFloat;
    } else if (std::holds_alternative<TagDouble_t>(*m_value)) {
        return TagType::TagDouble;
    } else if (std::holds_alternative<TagByteArray_t>(*m_value)) {
        return TagType::TagByteArray;
    } else if (std::holds_alternative<TagString_t>(*m_value)) {
        return TagType::TagString;
    } else if (std::holds_alternative<TagList_t>(*m_value)) {
        return TagType::TagList;
    } else if (std::holds_alternative<TagCompound_t>(*m_value)) {
        return TagType::TagCompound;
    } else if (std::holds_alternative<TagIntArray_t>(*m_value)) {
        return TagType::TagIntArray;
    } else if (std::holds_alternative<TagLongArray_t>(*m_value)) {
        return TagType::TagLongArray;
    }

    throw TypeNotMatchedException();
}