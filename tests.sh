#!/bin/sh

rm -fr build
mkdir build
cd build
cmake ..
cmake --build .

valgrind ./embroider --full-test-suite

tail test_matrix.txt
