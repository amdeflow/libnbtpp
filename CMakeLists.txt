cmake_minimum_required(VERSION 2.8)
project(nbtpp)

set(CMAKE_CXX_STANDARD 17)

option(LIBNBTPP_BUILD_TESTS "Build libnbtpp tests" OFF)

set(Boost_USE_STATIC_LIBS ON)
find_package(Boost REQUIRED COMPONENTS iostreams)
find_package(ZLIB REQUIRED)

add_library(nbtpp SHARED nbtpp.cpp nbtpp.hpp binary.hpp tobinary.cpp endianness.hpp endianness.cpp frombinary.cpp nbtfile.cpp nbtfile.hpp)
target_link_libraries(nbtpp ${Boost_LIBRARIES})
target_link_libraries(nbtpp ${ZLIB_LIBRARIES})
target_include_directories(nbtpp PRIVATE ${Boost_INCLUDE_DIRS})

install(TARGETS nbtpp
        LIBRARY DESTINATION lib)
install(FILES binary.hpp endianness.hpp nbtfile.hpp nbtpp.hpp
        DESTINATION include/nbtpp)

set(DEST_DIR "${CMAKE_INSTALL_PREFIX}")
set(PRIVATE_LIBS "-llibnbtpp")

configure_file("libnbtpp.pc.in" "libnbtpp.pc" @ONLY)
install(FILES ${CMAKE_BINARY_DIR}/libnbtpp.pc DESTINATION share/pkgconfig)

if (LIBNBTPP_BUILD_TESTS)
    add_executable(nbtpptest catch.hpp tests.cpp)
    target_link_libraries(nbtpptest nbtpp)
endif(LIBNBTPP_BUILD_TESTS)