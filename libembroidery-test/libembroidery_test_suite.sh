#!/bin/bash
#
# Builds and runs the libembroidery_convert executable (along with the
# static and dynamic versions of the library) and tests the reading
# of CSV input and writing of SVG output, a common use case where
# the user wishes to know what their script created CSV looks right.
#
# Then it outputs machine-compatable stitch files should the dev
# wish to run those tests on a machine.

function test_convert () {
gdb --batch -ex=r \
    --args ./libembroidery_convert ../libembroidery-test/$1 $2 &>> test.log
}

rm -fr build
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Debug .. &> test.log
make &>> test.log

test_convert test01.csv test01.svg
test_convert test02.csv test02.svg
test_convert test01.csv test01.dst
test_convert test02.csv test02.dst
gdb --batch -ex=r --args ./libembroidery_test &>> test.log
