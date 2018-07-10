#ifndef NBTPP_NBTPP_HPP
#define NBTPP_NBTPP_HPP

#include <cstddef>
#include <cstdint>
#include <map>
#include <memory>
#include <string>
#include <utility>
#include <variant>
#include <vector>

namespace NBT {
    class Tag;

    typedef std::int8_t TagByte_t;
    typedef std::int16_t TagShort_t;
    typedef std::int32_t TagInt_t;
    typedef std::int64_t TagLong_t;
    typedef float TagFloat_t;
    typedef double TagDouble_t;
    typedef std::vector<std::int8_t> TagByteArray_t;
    typedef std::string TagString_t;
    typedef std::vector<Tag> TagList_t;
    typedef std::map<std::string, Tag> TagCompound_t;
    typedef std::vector<std::int32_t> TagIntArray_t;
    typedef std::vector<std::int64_t> TagLongArray_t;

    typedef std::variant<std::int8_t,            \
                     std::int16_t,               \
                     std::int32_t,               \
                     std::int64_t,               \
                     float,                      \
                     double,                     \
                     std::vector<std::int8_t>,   \
                     std::string,                \
                     std::vector<Tag>,           \
                     std::map<std::string, Tag>, \
                     std::vector<std::int32_t>,  \
                     std::vector<std::int64_t>> TagValue_t;

    enum class TagType : std::uint8_t {
        TagEnd       = 0x0,
        TagByte      = 0x1,
        TagShort     = 0x2,
        TagInt       = 0x3,
        TagLong      = 0x4,
        TagFloat     = 0x5,
        TagDouble    = 0x6,
        TagByteArray = 0x7,
        TagString    = 0x8,
        TagList      = 0x9,
        TagCompound  = 0xA,
        TagIntArray  = 0xB,
        TagLongArray = 0xC,
    };

    class TypeNotMatchedException : public std::exception {
    public:
        const char * what() const noexcept override {
            return "NBT Tag type not matched";
        }
    };

    class SizeException : public std::exception {
    public:
        const char * what() const noexcept override {
            return "The size of the array was too big for the containing integer type";
        }
    };

    class Tag {
    public:
        explicit Tag(TagByte_t value);
        explicit Tag(TagShort_t value);
        explicit Tag(TagInt_t value);
        explicit Tag(TagLong_t value);
        explicit Tag(TagFloat_t value);
        explicit Tag(TagDouble_t value);
        explicit Tag(TagByteArray_t value);
        explicit Tag(TagString_t value);
        explicit Tag(TagList_t value);
        explicit Tag(TagCompound_t value);
        explicit Tag(TagIntArray_t value);
        explicit Tag(TagLongArray_t value);

        TagByte_t &tagByte();
        TagShort_t &tagShort();
        TagInt_t &tagInt();
        TagLong_t &tagLong();
        TagFloat_t &tagFloat();
        TagDouble_t &tagDouble();
        TagByteArray_t &tagByteArray();
        TagString_t &tagString();
        TagList_t &tagList();
        TagCompound_t &tagCompound();
        TagIntArray_t &tagIntArray();
        TagLongArray_t &tagLongArray();

        TagType type();

    private:
        std::shared_ptr<TagValue_t> m_value;
    };
}

#endif