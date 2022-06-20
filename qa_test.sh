#!/bin/bash

rm -fr build
mkdir build
cd build
cmake ..
make 2> build_error.log
./embroider --test
cd ..
