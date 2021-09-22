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
cmake -DCMAKE_BUILD_TYPE=Debug ..
make
gdb --batch -ex=r --args ./embroider -test
cd -
}

function make_doc () {
man -Tpdf ./doc/embroider.1 >./doc/embroider.pdf
}

function embedded_compatibility_report () {
echo "SYMBOL USAGE" > embedded.txt
for s in `nm -j build/embroider`
do
echo $s >> embedded.txt
grep $s *.c *.h | wc >> embedded.txt
done

echo "SPACE PER SYMBOL" >> embedded.txt
nm -S --size-sort build/libembroidery_static.a >> embedded.txt

echo "TOTAL SPACE USAGE" >> embedded.txt
strip build/libembroidery_static.a
du -h build/libembroidery_static.a >> embedded.txt
}

build_libembroidery
embedded_compatibility_report
