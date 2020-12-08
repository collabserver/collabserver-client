#!/bin/bash

set -e
set -x
set -v

mkdir build || true
cd build

cmake -DCMAKE_BUILD_TYPE=${BUILD_TYPE} \
      -DCOLLABSERVER_CLIENT_TESTS=ON \
      -DCOLLABSERVER_CLIENT_EXAMPLES=ON \
      ..
make
make runTests


