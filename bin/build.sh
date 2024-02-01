#!/bin/bash

echo "Building..."

rm -fr build
mkdir build
cd build
cmake ..
cmake --build .
cd ..
