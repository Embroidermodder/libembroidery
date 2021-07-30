#!/bin/bash

function usage {
echo 'Usage message'
}

function embphoto () {
echo "Photo filtering function."
}

function build_datafile () {
gcc -c -Wa,-adhln -g libembroidery_data.S > libembroidery_data.lst
gcc -c libembroidery_data.S -o libembroidery_data.bin
}

function build_x86 () {
gcc -nostdlib -no-pie -m32 -o embroider_x86 libembroidery_x86.S
}

function build_arm () {
gcc -E libembroidery_arm.S -o embroidery_arm.s
arm-none-eabi-as -o embroider_arm.o embroidery_arm.s
arm-none-eabi-ld -o embroider_arm embroider_arm.o
}

function build_avr () {
gcc -E libembroidery_avr.S -o embroidery_avr.s
avr-as -o embroider_avr.o embroidery_avr.s
avr-ld -o embroider_avr embroider_avr.o
}

function asm_clean () {
rm -f embroider*.o
rm -f libembroidery_data.lst
}

function build_asm () {
# Assumes that the host is linux, otherwise skips.
# Requires gcc multilib:
# $ apt install build-essential gcc-multilib

if [[ "$OSTYPE" == "linux-gnu" ]]; then

build_datafile
build_x86
build_arm
build_avr

asm_clean

./embroider_x86 --test

else

cat <<EOF
Building libembroidery embedded version is only supported
on Linux. This is due to using Linux syscalls on x86, gcc-multilib
for cross-compiling to avr and arm and emulation software that
may not be cross-platform.
EOF

fi
}

function main_tests () {
rm -fr build
mkdir build
cd build
cmake ..
cmake --build . 2> error.txt

./embroider --test
cd ..
}

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
    *)
      shift
      break
      ;;
    esac
done


