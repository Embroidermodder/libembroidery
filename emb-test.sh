#!/bin/bash
#
# Builds and runs the libembroidery_convert executable (along with the
# static and dynamic versions of the library) and runs the in-built
# test suite.
#
# This matches the GitHub Action we have set up.

function build_libembroidery () {
rm -fr build
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Debug .. &> test.log
make &>> test.log
gdb --batch -ex=r --args ./embroider -test &>> test.log
cd -
}

function make_doc () {
man -Tpdf ./doc/embroider.1 >./doc/embroider.pdf
}

function embedded_compatibility_report () {
echo "SYMBOL USAGE" > symbols.txt
for s in `nm -j build/embroider`
do
echo $s >> symbols.txt
grep $s *.c *.h | wc >> symbols.txt
done

echo "SPACE USAGE" > space_use.txt
strip build/libembroidery.so
strip build/libembroidery_static.a
strip build/embroider
du -h build/libembroidery.so >> space_use.txt
du -h build/libembroidery_static.a >> space_use.txt
du -h build/embroider >> space_use.txt
}

build_libembroidery
embedded_compatibility_report
