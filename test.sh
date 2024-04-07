#!/bin/bash
#
# This file is part of libembroidery.
#
# This needs the "./" part because it used to run the program
# as well as build it.
WORKDIR=./build
TESTDIR=./test_data
EMB=$WORKDIR/embroider
TEST_TIME=10

function build () {
    rm -fr $WORKDIR $TESTDIR
    mkdir $WORKDIR
    mkdir $TESTDIR
    cd $WORKDIR
    cmake ..
    cmake --build .
    cd ..
}

function emb_test () {
    echo "Sanity test $1"
    timeout $TEST_TIME $EMB --test $1 || echo "FAILED"
}

function fill_test () {
    echo "Fill SVG test ($1)"
    timeout $TEST_TIME $EMB --fill images/$1.png 130 $TESTDIR/$1.svg || echo "FAILED"
}

function cross_test () {
    echo "Cross fill SVG test ($1)"
    timeout $TEST_TIME $EMB --cross-stitch images/$1.png 130 $TESTDIR/$1.svg || echo "FAILED"
}

function render_fill_test () {
    echo "Render Fill Test ($1)"
    timeout $TEST_TIME $EMB --fill images/$1.png 130 $TESTDIR/$1.csv && \
        $EMB --fill $TESTDIR/$1.csv $TESTDIR/$1.png || echo "FAILED"
}

function render_cross_test () {
    echo "Render Cross Test ($1)"
    timeout $TEST_TIME $EMB --cross-stitch images/$1.png 130 $TESTDIR/$1.csv && \
        $EMB --render $TESTDIR/$1.csv $TESTDIR/$1_render.png || echo "FAILED"
}

function test_convert () {
    echo "Converting $1 to $2."
    timeout $TEST_TIME $EMB --convert $TESTDIR/$1 $TESTDIR/$2 || echo "FAILED"
}

function all_tests () {
    for i in `seq 0 13`
    do
        emb_test $i
    done

    fill_test donut 130
    fill_test logo-spirals 130
    fill_test berries 130
    fill_test snow-squirrel 130
    fill_test great-tit 130
    fill_test owl 130
    fill_test logo 130

    cross_test logo
    render_fill_test logo
    render_cross_test logo
}

date

if [ ! -e build/embroider ]
then
    time build
fi

time all_tests
