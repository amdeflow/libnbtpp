#ifndef NBTPP_NBTFILE_HPP
#define NBTPP_NBTFILE_HPP

#include <fstream>
#include <iterator>

#include "nbtpp.hpp"
#include "binary.hpp"

namespace NBT {
    enum class CompressionMethod {
        None,
        Gzip,
        Zlib,
    };

    class File {
    public:
        File(std::string path, Endianness endianness);
        File(Tag rootTag, std::string rootName);

        TagCompound_t& getRoot();

        void write(std::string path, Endianness endianness, NBT::CompressionMethod cm);
        void write(std::string path, Endianness endianness);

    private:
        std::shared_ptr<Tag> m_root;
        std::string m_rootName;
        CompressionMethod m_cm = CompressionMethod::None;
    };
}

#endif //NBTPP_NBTFILE_HPP
