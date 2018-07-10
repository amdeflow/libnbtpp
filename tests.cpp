#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "nbtpp.hpp"
#include "binary.hpp"

bool checkContainer() {
    try {
        NBT::Tag test(NBT::TagCompound_t {
                { "Eggbert", NBT::Tag("bananrama") },
        });

        std::string expected = "bananrama";

        return test.tagCompound().at("Eggbert").tagString() == expected;
    } catch (std::exception& e) {
        std::cout << e.what() << std::endl;
    }
    return false;
}

bool checkBasicWrite() {
    try {
        NBT::Tag test(NBT::TagCompound_t {
                { "Test", NBT::Tag("apple") },
        });
        std::vector<std::uint8_t> expected = {
                0x08, 0x00, 0x04, 0x54, 0x65, 0x73, 0x74, 0x00, 0x05, 0x61, 0x70, 0x70, 0x6c, 0x65, 0x00
        };

        auto res = NBT::ToBinary::toBinary(test, NBT::Endianness::BigEndian);

        return res == expected;
    } catch (std::exception& e) {
        std::cout << "ERROR: " << e.what() << std::endl;
    }
    return false;
}

bool fpread() {
    std::vector<std::uint8_t> bnum = { 0x40, 0x48, 0xf5, 0xc3 };
    swapEndianness(bnum, NBT::Endianness::BigEndian);

    union {
        std::uint8_t data[4];
        float num;
    } convert{};

    std::memcpy(convert.data, bnum.data(), sizeof(float));

    return convert.num == 3.14f;
}

bool utosconv() {
    std::uint8_t input = 130;

    std::int8_t expected = -126;
    std::int8_t res = input;

    return res == expected;
}

bool bread() {
    std::deque<std::uint8_t> input = {
            0x08, 0x00, 0x04, 0x54, 0x65, 0x73, 0x74, 0x00, 0x05, 0x61, 0x70, 0x70, 0x6c, 0x65, 0x00
    };

    auto result = NBT::FromBinary::readTagCompound(input, NBT::Endianness::BigEndian);

    return result.tagCompound().at("Test").tagString() == "apple";
}

TEST_CASE( "Basic Compound", "[container]" ) {
    REQUIRE(checkContainer() );
}

TEST_CASE( "Basic Write", "[write]" ) {
    REQUIRE( checkBasicWrite() );
}

TEST_CASE( "Floating point read", "[fpread]" ) {
    REQUIRE( fpread() );
}

TEST_CASE( "Signed to unsigned conversion", "[utosconv]" ) {
    REQUIRE( utosconv() );
}

TEST_CASE( "Basic read", "[bread]" ) {
    REQUIRE( bread() );
}