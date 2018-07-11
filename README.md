libnbtpp
========

A C++17 NBT Library with compression support

NOTE: The 'real' repository can be found at [GitLab](https://gitlab.com/amdeflow/libnbtpp). Please report issues and merge requests there.

### Requirements
* Boost.Iostreams (required for compression support, there is no option to disable this feature)
* CMake
* A compiler (this library has only been tested on Clang and GCC on Arch Linux)

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

#### Testing
To build the testing executable pass the flag `-DLIBNBTPP_BUILD_TESTS=ON` to the `cmake` command in the [build](#building) process. To run the tests, execute `./nbtpptest` in the build directory