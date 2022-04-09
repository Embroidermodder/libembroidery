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
cd python
swig -Wall -python embroidery.i

python3 setup.py build
python3 setup.py install --user

python3 << EOF
import libembroidery
help(libembroidery)
EOF
cd ..
}

#c_build
python_build
