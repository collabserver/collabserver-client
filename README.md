# Collab Client Interface

[![release-version](https://img.shields.io/badge/release-alpha--version-red.svg)]()
[![build-status-master](https://travis-ci.org/CollabServer/collab-client-interface.svg?branch=master)](https://travis-ci.org/CollabServer/collab-client-interface)
[![license](https://img.shields.io/badge/license-LGPLv3.0-blue.svg)](https://github.com/CollabServer/collab-client-interface/blob/master/LICENSE.txt)

| master | dev |
| :-----: | :----: |
| [![build-status-master](https://travis-ci.org/CollabServer/collab-client-interface.svg?branch=master)](https://travis-ci.org/CollabServer/collab-client-interface) | [![build-status-master](https://travis-ci.org/CollabServer/collab-client-interface.svg?branch=dev)](https://travis-ci.org/CollabServer/collab-client-interface) |


## Overview
End-user interface to connect and work with a CollabServer.


## Features
- Server
    - Connect
    - Disconnect
- Data
    - Create data on server
    - Join data
    - Leave data


## Build instructions (CMake)
Client interface is built as a static library.
If built the static lib manually, you must also include `collab-data-crdts/include`
and `collab-common/include` headers and, add collab-common/src files to the lib.

### Requirements
- C++11
- `pragma once` support
- Tested with gcc 4.8.4
- Tested with clang 5.0.0
- Tested only on Linux. Not support certified for Mac and Windows

### Dependencies
All dependencies are automatically downloaded by CMake and placed in a folder
named `dependencies`.
You may move this folder in another place later and request CMake not to
download dependencies anymore (**See CMake options**).

If you are using a custom permanent location for your dependencies, a convenient
solution is to set the environment variable `COLLAB_DEPENDENCIES_DIR` with this path.
CMake will use this one as the default location (Except if a custom path is
given as CMake parameter).

- [GoogleTest](https://github.com/google/googletest)

### Manual dependencies (System Wide)
These dependencies **must be installed system-wide** and are not downloaded by CMake.
Check the instruction specific to your operating system for further information.
(Ex: `pacman -S zeromq` on ArchLinux)

- [ZeroMQ](http://zeromq.org/)

### Git submodules
These are used internally by collab-server and are compiled along with collab-server.
You may work on the submodules from this project.

- [collab-common](https://github.com/CollabServer/collab-common.git)
- [collab-data-crdts](https://github.com/CollabServer/collab-data-crdts.git)

```bash
# To clone project with submodules
git clone --recursive https://github.com/CollabServer/collab-client-interface.git

# To pull also submodules
git pull --recurse-submodules=on

# To update submodules
git submodule update
```

### CMake options
| Name | Description |
| --- | --- |
| COLLAB_DEPENDENCIES_DIR | (STRING) Path to a directory where to find all dependencies (By default, uses current cmake build) |
| COLLAB_DEPENDENCIES_DOWNLOAD | (ON/OFF) Set ON to also download dependencies at cmake time. This is useful the first time you setup the project. Dependencies are placed in COLLAB_DEPENDENCIES_DIR. (By default: OFF).|
| COLLAB_TESTS | (ON/OFF) Set ON to build unit tests |
| COLLAB_EXAMPLES | (ON/OFF) Set ON to build examples |
| CMAKE_BUILD_TYPE | Debug, Release, RelWithDebInfo, MinSizeRel |

### Build static lib with CMake
```bash
mkdir build
cd build
cmake -DCOLLAB_DEPENDENCIES_DOWNLOAD=ON ..
make -j2
```

### Build tests with CMake
```bash
# Build manually
mkdir build
cd build
cmake -DCOLLAB_DEPENDENCIES_DOWNLOAD=ON ..
make -j2
make runTests

# Build from shell script
./build.sh
```


## Getting Started
collab-client is built as a static lib.
In order to use it in your project, you must also link its dependencies
`zmq` and, `pthread` in your executable.
If you are using the custom component of collab-data-crdts, you must also
link `collabdata`.


## Generate documentation
- [Doxygen](https://www.stack.nl/~dimitri/doxygen/)

Generate documentation with `doxygen Doxyfile`.
Generated files are places in `doc` folder.


# Author
Constantin Masson ([constantinmasson.com](http://constantinmasson.com/))


