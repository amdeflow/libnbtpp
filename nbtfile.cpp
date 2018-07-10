#include <utility>

#include "nbtfile.hpp"
#include <boost/iostreams/filtering_streambuf.hpp>
#include <boost/iostreams/filtering_stream.hpp>
#include <boost/iostreams/copy.hpp>
#include <boost/iostreams/filter/zlib.hpp>
#include <boost/iostreams/filter/gzip.hpp>

NBT::File::File(std::string path, Endianness endianness) {
    std::ifstream file(path, std::ios_base::in | std::ios_base::binary);

    std::deque<std::uint8_t> contents;

    std::vector<char> headerBuffer(2);
    file.read(&headerBuffer[0], headerBuffer.size());

    file.unget();
    file.unget();

    if (headerBuffer.at(0) == 0x1f && (unsigned char) headerBuffer.at(1) == 0x8b) {
        m_cm = CompressionMethod::Gzip;

        boost::iostreams::filtering_istreambuf in;
        in.push(boost::iostreams::gzip_decompressor());
        in.push(file);

        contents.assign(std::istreambuf_iterator<char>{&in}, {});
    } else if (headerBuffer.at(0) == 0x78) {
        m_cm = CompressionMethod::Zlib;

        boost::iostreams::filtering_istreambuf in;
        in.push(boost::iostreams::zlib_decompressor());
        in.push(file);

        contents.assign(std::istreambuf_iterator<char>{&in}, {});
    } else {
        file.unsetf(std::ios::skipws);

        std::streampos size;

        file.seekg(0, std::ios::end);
        size = file.tellg();
        file.seekg(0, std::ios::beg);

        contents.resize((unsigned long) size);

        contents.insert(contents.begin(),
                        std::istream_iterator<std::uint8_t>(file),
                        std::istream_iterator<std::uint8_t>());
    }

    file.close();

    TagType type = FromBinary::readTagType(contents);
    if (type != TagType::TagCompound)
        throw TypeNotMatchedException();

    m_rootName = FromBinary::readTagName(contents, endianness);
    m_root = std::make_shared<Tag>(FromBinary::readTag(type, contents, endianness));
}

NBT::File::File(NBT::Tag rootTag, std::string rootName): m_rootName(std::move(rootName)) {
    if (rootTag.type() != TagType::TagCompound)
        throw TypeNotMatchedException();

    m_root = std::make_shared<Tag>(rootTag);
}

NBT::TagCompound_t& NBT::File::getRoot() {
    return (*m_root).tagCompound();
}

void NBT::File::write(std::string path, NBT::Endianness endianness, NBT::CompressionMethod cm) {
    m_cm = cm;

    std::vector<std::uint8_t> type = ToBinary::writeTagType(m_root.get()->type());
    std::vector<std::uint8_t> name = ToBinary::writeTagName(m_rootName, endianness);
    std::vector<std::uint8_t> tag = ToBinary::toBinary(*m_root.get(), endianness);

    type.insert(type.end(), name.begin(), name.end());
    type.insert(type.end(), tag.begin(), tag.end());

    std::ofstream file(path, std::ios::out | std::ios::binary);

    if (cm == CompressionMethod::None){
        file.write((const char *) type.data(), type.size());
    } else {
        boost::iostreams::filtering_ostream out;
        switch (m_cm) {
            case CompressionMethod::Gzip:
                out.push(boost::iostreams::gzip_compressor());
                break;
            case CompressionMethod ::Zlib:
                out.push(boost::iostreams::zlib_compressor());
                break;
            default:
                out.push(boost::iostreams::gzip_compressor());
                break;
        }

        out.push(file);
        out.write(reinterpret_cast<char *>(type.data()), type.size());
    }

    file.close();
}

void NBT::File::write(std::string path, NBT::Endianness endianness) {
    write(path, endianness, m_cm);
}
