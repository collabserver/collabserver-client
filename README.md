# Collab Client Interface

[![release-version](https://img.shields.io/badge/release-alpha--version-red.svg)]()
[![build-status-master](https://travis-ci.org/CollabServer/collab-client-interface.svg?branch=master)](https://travis-ci.org/CollabServer/collab-client-interface)
[![license](https://img.shields.io/badge/license-LGPLv3.0-blue.svg)](https://github.com/CollabServer/collab-client-interface/blob/master/LICENSE.txt)

| master | dev |
| :-----: | :----: |
| [![build-status-master](https://travis-ci.org/CollabServer/collab-client-interface.svg?branch=master)](https://travis-ci.org/CollabServer/collab-client-interface) | [![build-status-master](https://travis-ci.org/CollabServer/collab-client-interface.svg?branch=dev)](https://travis-ci.org/CollabServer/collab-client-interface) |


## Overview
> Work in progress.


## Requirements
- C++11
- `pragma once` support
- Tested with gcc 4.8.4
- Tested with clang 5.0.0
- Tested only on Linux. Not support certified for Mac and Windows


## Dependencies
> Dependencies marked with *(CMake)* are automatically downloaded by CMake
> script and placed in *dependencies* folder.
> Others must be installed manually (Generally system-wide install).
- [ZeroMQ](http://zeromq.org/) (**Must be installed system-wide**)
- [collab-common](https://github.com/CollabServer/collab-common.git) (CMake)
- [collab-data-crdts](https://github.com/CollabServer/collab-data-crdts.git) (CMake)
- [GoogleTest](https://github.com/google/googletest) (CMake. Only for tests)


## Build instructions
Client interface is built as a static library.
You must link the library `collabclient` and its dependencies
`collabcommon` and `zmq`.

### Build types
- CMake build types (ex: `-DCMAKE_BUILD_TYPE=Debug`):
    - Debug
    - Release
    - RelWithDebInfo
    - MinSizeRel

### Clone project with submodules
```bash
git clone --recursive https://github.com/CollabServer/collab-client-interface.git
cd collab-client-interface

# To pull changes from gitmodules
git pull --recurse-submodules=on-demand
# To update submodules
git submodule update
```

### Build static lib with CMake
```bash
# Build manually
mkdir build
cd build
cmake ..
make -j4
```

### Build tests with CMake
```bash
# Build manually
mkdir build
cd build
cmake ..
make -j4
make runTests

# Build from shell script
./build.sh
```


## Generate documentation
- [Doxygen](https://www.stack.nl/~dimitri/doxygen/)

Generate documentation with `doxygen Doxyfile`.
Generated files are places in `doc` folder.


# Author
Constantin Masson ([constantinmasson.com](http://constantinmasson.com/))


