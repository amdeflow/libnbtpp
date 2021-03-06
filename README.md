libnbtpp
========

A C++17 NBT Library with compression support

NOTE: The 'real' repository can be found at [GitLab](https://gitlab.com/amdeflow/libnbtpp). 
Please report issues and merge requests there.

### Requirements
* Boost.Iostreams (required for compression support, there is no option to disable this feature)
* zlib (also required for compression support)
* CMake
* A compiler with C++17 support (this library has only been tested on Clang and GCC on Arch Linux)

### Building
#### Compilation
```sh
mkdir build
cd build
cmake ..
make
```

#### Installation
Note: you might need superuser privileges to use this command
```sh
make install
```
You might want to specify the destination directory. On Arch systems, it is recommended to install to `/usr` instead of 
`/usr/local` as that will cause in runtime errors for linked binaries.

#### Testing
To build the testing executable pass the flag `-DLIBNBTPP_BUILD_TESTS=ON` to the `cmake` command in the 
[build](#building) process. To run the tests, execute `./nbtpptest` in the build directory

### Example
```c++
#include <nbtpp/nbtfile.hpp>

int main(int argc, char * argv[]) {
    NBT::File file("bigtest.nbt");
    auto eggCompound = file.getRoot().at("nested compound test").tagCompound()
                                     .at("egg").tagCompound();
    
    std::cout << eggCompound.at("name").tagString()
              << ": "
              << eggCompound.at("value").tagFloat()
              << std::endl;
              
    return EXIT_SUCCESS;
}
```