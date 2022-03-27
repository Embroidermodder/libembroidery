#!/bin/bash

function c_build () {
rm -fr build
mkdir build
cd build
cmake ..
make
cd ..
}

python3 setup.py install --user

python3 << EOF
import libembroidery
help(libembroidery)
EOF
