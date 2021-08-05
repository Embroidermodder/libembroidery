#!/bin/bash
#
# Builds and runs the libembroidery_convert executable (along with the
# static and dynamic versions of the library) and tests the reading
# of CSV input and writing of SVG output, a common use case where
# the user wishes to know what their script created CSV looks right.
#
# Then it outputs machine-compatable stitch files should the dev
# wish to run those tests on a machine.
mkdir build
cd build
cmake ..
make
./libembroidery_convert ../libembroidery-test/test01.csv test01.svg
./libembroidery_convert ../libembroidery-test/test02.csv test02.svg
./libembroidery_convert ../libembroidery-test/test01.csv test01.dst
./libembroidery_convert ../libembroidery-test/test02.csv test02.dst
./libembroidery_test
