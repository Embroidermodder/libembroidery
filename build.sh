#!/bin/bash

function docs () {

    cd docs
	sudo apt-get update &> deps.log
	sudo apt-get upgrade &>> deps.log
	sudo apt-get install doxygen &>> deps.log
	pip install sphinx sphinx-book-theme breathe &>> deps.log
	git submodule init &>> deps.log
	git submodule update &>> deps.log

	make html || exit 1
	cd ..

}

function build_refman () {

	sudo apt-get update &> deps.log
	sudo apt-get upgrade &>> deps.log
	sudo apt-get install texlive-full &>> deps.log

    cd docs/emrm
	pdflatex refman.tex
	cd ../..

}

function test_fills () {
    echo "$1 test..."

    STUB="${1::-4}_stitches"
    ./build/embroider --fill $1 130 $STUB.csv
    ./build/embroider --fill $1 130 $STUB.svg
    #./build/embroider --render $STUB.csv $STUB.png

    STUB="${1::-4}_crosses"
    ./build/embroider --cross-stitch $1 130 $STUB.csv
    ./build/embroider --cross-stitch $1 130 $STUB.svg
    #./build/embroider --render $STUB.csv $STUB.png
}

function cmake_build () {
    echo "Building..."

    rm -fr build
    mkdir build
    cd build
    cmake ..
    cmake --build .
    cd ..
}

function tidy_src () {
    echo "This script enforces some of our style requirements"
    echo "and warns developers about possible untidy code."
    echo ""
    echo "See the reference manual for the full list of rules."

    for file in src/*.c src/*.h src/geometry/*.c src/formats/*.c
    do
        sed -i 's/\r$//' $file
        sed -i 's/\t/    /' $file
        sed -i 's/ $//' $file
    done

    # Report changes.
    git diff
}

function analyse_src () {
    mkdir analysis

    for file in src/*.c src/*.h src/geometry/*.c src/formats/*.c
    do
        # For analysis
        gcc -fdump-tree-all -o ${file:-2}.o -c $file
        clang $file -S -Xclang -dump-tokens &> ${file:-2}.tokens
        clang $file -S -emit-llvm &> ${file:-2}.llvm
        clang $file -S -ast-dump &> ${file:-2}.ast-dump
        clang $file -S -ast-view &> ${file:-2}.ast
        clang $file -S -mllvm -print-after-all &> ${file:-2}.opt
    done
}

function libembroidery_tests () {
    echo "Built in tests..."

    ./build/embroider --test

    echo "Stitch fill tests..."

    test_fills demos/donut.png
    test_fills demos/logo-spirals.png
    test_fills demos/berries.png
    test_fills demos/snow-squirrel.png
    test_fills demos/great-tit.png
    test_fills demos/owl.png
    test_fills demos/logo.png
}

if [ "$1" = "docs" ]; then
    docs
    exit
fi

if [ "$1" = "tidy" ]; then
    tidy_src
    exit
fi

if [ "$1" = "analysis" ]; then
    analyse_src
    exit
fi

if [ "$1" = "test" ]; then
    libembroidery_tests
    exit
fi

cmake_build

