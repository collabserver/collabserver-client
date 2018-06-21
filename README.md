# Collab Client Interface
[![release-version](https://img.shields.io/badge/release-alpha--version-red.svg)]()
[![build-status-master](https://travis-ci.org/CollabServer/collab-client-interface.svg?branch=master)](https://travis-ci.org/CollabServer/collab-client-interface)
[![license](https://img.shields.io/badge/license-LGPLv3.0-blue.svg)](https://github.com/CollabServer/collab-client-interface/blob/master/LICENSE.txt)

| master | dev |
| :-----: | :----: |
| [![build-status-master](https://travis-ci.org/CollabServer/collab-client-interface.svg?branch=master)](https://travis-ci.org/CollabServer/collab-client-interface) | [![build-status-master](https://travis-ci.org/CollabServer/collab-client-interface.svg?branch=dev)](https://travis-ci.org/CollabServer/collab-client-interface) |


# Overview
> Work in progress.


# Install with CMake on GNU/Linux
- [CMake](https://cmake.org/)
> Be sure to check the dependency requirements first.

```cmake
git clone --recursive https://github.com/CollabServer/collab-client-interface.git
cd collab-client-interface
mkdir build
cd build
cmake ..
make -j4

# This creates the client_interface static lib
# Place the .a lib file and the include dir in your project's dependencies
```


# Dependencies and requirements
> Dependencies marked with (CMake) are automatically downloaded by CMake script.
> Others must be installed manually (Generally system-wide install).

- Build with C++11 (tested with gcc 4.8.4 and higher and clang 5.0.0)
- Requires pragma support (pragma once)
- [collab-messaging-protocol](https://github.com/CollabServer/collab-messaging-protocol.git) (CMake)
- [ZeroMQ](http://zeromq.org/) (Must be installed system-wide)


# Author
Constantin Masson ([constantinmasson.com](http://constantinmasson.com/))
