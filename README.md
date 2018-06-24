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
> script and placed in *bin* folder.
> Others must be installed manually (Generally system-wide install).
- [collab-common](https://github.com/CollabServer/collab-common.git) (CMake)
- [ZeroMQ](http://zeromq.org/) (Must be installed system-wide)


## Build instructions

### Clone project with dependencies
```bash
git clone --recursive https://github.com/CollabServer/collab-client-interface.git
cd collab-client-interface
```

### Build static lib with CMake
- [GoogleTest](https://github.com/google/googletest)
(Automatically downloaded by CMake and placed in project's root folder `bin`

```cmake

# Build manually
mkdir build
cd build
cmake ..
make -j4

# Build from shell script
./build.sh
```


# Author
Constantin Masson ([constantinmasson.com](http://constantinmasson.com/))
