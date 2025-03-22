#!/bin/bash
#
# This file is part of libembroidery.
#
# This needs the "./" part because it used to run the program as well as build it.
BUILD_DIR=./build
TEST_DIR=./test
EMB=$TEST_DIR/embroider
TEST_TIME=10
TOTAL_TESTS=13

function test_build () {
    CC=gcc
    OPTIONS="-g -O2 -fPIC -std=c99 -Wall -Wextra -Werror"
    rm -fr $TEST_DIR
    mkdir $TEST_DIR
    time $CC $OPTIONS src/embroider.c -o $EMB -lm
    cd $TEST_DIR
}

function test_wrap () {
    timeout $TEST_TIME $@ || echo "FAILED" && exit 1
}

function emb_test () {
    echo "Test $1"
    test_wrap $EMB --args --test $1
}

function test_convert () {
    echo "Converting $1 to $2."
    test_wrap $EMB --convert $1 $2
}

function fill_test () {
    echo "Fill SVG test ($1)"
    test_wrap $EMB --fill ../images/$1.png 130 $1.svg
}

function cross_test () {
    echo "Cross fill SVG test ($1)"
    test_wrap $EMB --cross-stitch ../images/$1.png 130 $1.svg
}

function render_fill_test () {
    echo "Render Fill Test ($1)"
    test_wrap $EMB --fill ../images/$1.png 130 $1.csv
    test_wrap $EMB --fill $1.csv $1.png
}

function render_cross_test () {
    echo "Render Cross Test ($1)"
    test_wrap $EMB --cross-stitch ../images/$1.png 130 $1.csv
    test_wrap $EMB --render $1.csv $1_render.png
}


function fast_tests () {
    for i in `seq 0 $TOTAL_TESTS`
    do
        emb_test $i
    done
}

function all_tests () {
    fast_tests

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

if [ "$1" = "--test-full" ]; then

    date &> test_full.log
    test_build &>> test_full.log
    time all_tests &>> test_full.log

elif [ "$1" = "--test" ]; then

    date &> test.log
    test_build &>> test.log
    time fast_tests &>> test.log

elif [ "$1" = "--clean" ]; then

    rm -fr $BUILD_DIR $TEST_DIR

else

    mkdir -f $BUILD_DIR &> build.log
    cd $BUILD_DIR &>> build.log
    cmake .. &>> build.log
    cmake --build . &>> build.log

fi
