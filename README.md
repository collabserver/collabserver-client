# CollabServer - Client Interface

[![license](https://img.shields.io/badge/license-LGPLv3.0-blue.svg)](https://github.com/CollabServer/collab-client-interface/blob/master/LICENSE.txt)
[![build-status-master](https://travis-ci.org/CollabServer/collab-client-interface.svg?branch=master)](https://travis-ci.org/CollabServer/collab-client-interface)

| master | dev |
| :-----: | :----: |
| [![build-status-master](https://travis-ci.org/CollabServer/collab-client-interface.svg?branch=master)](https://travis-ci.org/CollabServer/collab-client-interface) | [![build-status-master](https://travis-ci.org/CollabServer/collab-client-interface.svg?branch=dev)](https://travis-ci.org/CollabServer/collab-client-interface) |


# Overview
End-user interface to connect and work with a CollabServer.


# Getting Started
1. Be sure you have all requirements and system-wide dependencies
1. Build collabclient static lib (See build instructions)
1. Link your application with `libcollabclient.a`
1. Include `collabdata` headers
1. Include `collabclient` headers
1. Link also with dependencies `zmq` and `pthread`


# Features
- Server
    - Connect
    - Disconnect
- Data
    - Create data on server
    - Join data
    - Leave data


# Build on Linux (CMake)
**Build static lib**
```bash
# Warning: Install system-wide dependencies
# Be sure you have all requirements

mkdir build
cd build
cmake -DCOLLAB_DEPENDENCIES_DOWNLOAD=ON ..
make
```

**Build tests**
```bash
# Warning: Install system-wide dependencies
# Be sure you have all requirements

mkdir build
cd build
cmake -DCOLLAB_DEPENDENCIES_DOWNLOAD=ON ..
make
make runTests

# Or use build script
./build.sh
```

**CMake options**

| CMake option name | Description |
| --- | --- |
| COLLAB_DEPENDENCIES_DIR | (STRING) Path to a directory where to find all dependencies (By default, uses current cmake build) |
| COLLAB_DEPENDENCIES_DOWNLOAD | (ON/OFF) Set ON to also download dependencies at cmake time. This is useful the first time you setup the project. Dependencies are placed in COLLAB_DEPENDENCIES_DIR. (By default: OFF).|
| COLLAB_TESTS | (ON/OFF) Set ON to build unit tests |
| COLLAB_EXAMPLES | (ON/OFF) Set ON to build examples |
| CMAKE_BUILD_TYPE | Debug, Release, RelWithDebInfo, MinSizeRel |


# Requirements
- C++11
- `pragma once` support
- Tested with gcc 4.8.4
- Tested with clang 5.0.0
- Tested only on Linux. **Not support certified for Mac and Windows**
- CMake (2.8.2 or higher)


# Dependencies
- System-Wide (**Must be installed manually**)
    - [ZeroMQ](http://zeromq.org/) (Release 3.1.1)
        - ArchLinux: `pacman -S zeromq`
        - Ubuntu: `apt-get install libzmq3 libzmq3-dev`
        - There is also a [Windows binary here](http://zeromq.org/distro:microsoft-windows) (Not tested yet)
    - pthread
- Automatically downloaded and built by CMake
    - [GoogleTest](https://github.com/google/googletest) (Release 1.8.1)
    - [collab-common](https://github.com/CollabServer/collab-common.git)
    - [collab-data-crdts](https://github.com/CollabServer/collab-data-crdts.git)

**Option: save dependencies for offline use**
> Dependencies downloaded by CMake are placed in the current CMake build folder
> (in `dependencies` folder).
> This is useful the firs time.
> To speedup the cmake process, you may keep these downloaded and built dependencies
> in a safe place and change the CMake dependencies path (See CMake options).

**Option: use environment variable for dependencies path**
> If `COLLAB_DEPENDENCIES_DIR` environment variable is set, CMake will use
> it as the current dependencies path.


# Generate Documentation
1. Install [Doxygen](https://www.stack.nl/~dimitri/doxygen/)
1. `doxygen Doxyfile`
1. Files are placed in `doc` folder


# Author
Constantin Masson ([constantinmasson.com](http://constantinmasson.com/))


