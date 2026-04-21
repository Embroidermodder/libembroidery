#!/bin/sh

mkdir build
cd build
cmake ..
cmake --build .

if [ -n "$1" ]; then
    ctest
fi
