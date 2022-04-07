#!/bin/bash

function c_build () {
rm -fr build
mkdir build
cd build
cmake ..
make 2> build_error.log
./embroider --test
cd ..
}

function python_build () {
python3 setup.py install --user

python3 << EOF
import libembroidery
help(libembroidery)
EOF
}

c_build
python_build
