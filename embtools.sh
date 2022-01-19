#!/bin/bash

function usage {
echo 'Usage message'
}

function embphoto () {
echo "Photo filtering function."
}

function docs () {
pandoc README.md -o README.pdf
}

function debug () {
rm -fr debug
mkdir debug
cd debug
cmake -DCMAKE_BUILD_TYPE=DEBUG ..
cmake --build . --config=DEBUG

valgrind ./embroider --full-test-suite
cd ..
}

function main_tests () {
rm -fr build
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=RELEASE ..
cmake --build .

./embroider --test
cd ..
}

#display hilbert_level_3.ppm
#
#avconv -i %%06d.ppm -vcodec huffyuv output.avi

function full_test_suite () {
main_tests
cd build

valgrind ./embroider --full-test-suite

tail test_matrix.txt
}

while true
do
    case $1 in
    -a|asm)
      echo "Building assemblies."
      build_asm
      shift
      break
      ;;
    avr)
      build_avr
      shift
      break
      ;;
    arm)
      build_arm
      shift
      break
      ;;
    x86)
      build_x86
      shift
      break
      ;;
    -e)
      find_errors
      shift
      break
      ;;
    -h|help)
      usage
      shift
      break
      ;;
    -t|test|build)
      main_tests
      shift
      break
      ;;
    full)
      full_test_suite
      shift
      ;;
    docs)
      docs
      shift
      ;;
    debug)
      debug
      shift
      ;;
    *)
      shift
      break
      ;;
    esac
done


