#!/bin/bash
#
# Builds and runs the libembroidery_convert executable (along with the
# static and dynamic versions of the library) and runs the in-built
# test suite.
#
# This matches the GitHub Action we have set up.

rm -fr build
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Debug .. &> test.log
make &>> test.log
gdb --batch -ex=r --args ./embroider -test &>> test.log
