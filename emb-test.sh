#!/bin/bash
#
# Builds and runs the libembroidery_convert executable (along with the
# static and dynamic versions of the library) and tests the reading
# of CSV input and writing of SVG output, a common use case where
# the user wishes to know what their script created CSV looks right.
#
# Then it outputs machine-compatable stitch files should the dev
# wish to run those tests on a machine.

function gdb_wrap () {
gdb --batch -ex=r --args $@ &>> test.log
}

function build_debug () {
rm -fr build
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Debug .. &> test.log
make &>> test.log
}

function test_suite () {
build_debug
gdb_wrap ./embroider ../embroider/test01.csv test01.svg
gdb_wrap ./embroider ../embroider/test02.csv test02.svg
gdb_wrap ./embroider ../embroider/test01.csv test01.dst
gdb_wrap ./embroider ../embroider/test02.csv test02.dst
gdb_wrap ./embroider -test
}

function valgrind_report () {
MEMORYLEAKS=$(cat "_memleak.txt" | grep "All heap blocks were freed -- no leaks are possible")

echo "=============================="
if [[ -z "$MEMORYLEAKS" ]]; then
    echo $(cat "_memleak.txt" | grep "LEAK SUMMARY:")
    echo $(cat "_memleak.txt" | grep "definitely lost:")
    echo $(cat "_memleak.txt" | grep "indirectly lost:")
    echo $(cat "_memleak.txt" | grep "possibly lost:")
    echo $(cat "_memleak.txt" | grep "still reachable:")
    echo "Review _memleak.txt for more information."
else
    echo "No memory leaks found :D"
fi
echo "=============================="
}

function valgrind_embroider () {
valgrind --leak-check=full --show-reachable=yes \
    --error-limit=no --suppressions=../valgrind-supp/./valgrind-qt.supp \
    --suppressions=../valgrind-supp/./valgrind-misc.supp \
    --gen-suppressions=all --log-file=_memleak.txt -v \
    ./embroider "$@"
cat ./_memleak.txt | ../valgrind-supp/./valgrind-create-suppressions.sh > _memleak.supp
valgrind_report
}

test_suite
