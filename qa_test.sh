#!/bin/bash

function png2ppm() {
convert $1.png -resize 1000x1000 -depth 8 $1.ppm
}

function straight_stitch() {
./build/embroider --fill $1.ppm 130 $1_stitches.dst
./build/embroider --fill $1.ppm 130 $1_stitches.csv
./build/embroider --render $1_stitches.csv $1_stitches.ppm
convert $1_stitches.ppm $1_stitches.png
}

function cross_stitch() {
./build/embroider --cross_stitch $1.ppm 130 $1_crosses.dst
./build/embroider --cross_stitch $1.ppm 130 $1_crosses.csv
./build/embroider --render $1_crosses.csv $1_crosses.ppm
convert $1_crosses.ppm $1_crosses.png
}

function cmake_build() {
rm -fr build
mkdir build
cd build
cmake ..
make 2> build_error.log
cd ..
}

function donut_test() {
convert xc:white -geometry 1000x1000 -depth 8 donut.ppm
convert output.ppm -fill black -draw "rectangle 100,100 500,500" donut.ppm
convert output.ppm -fill white -draw "rectangle 200,200 300,300" donut.ppm
straight_stitch demos/donut
cross_stitch demos/donut
}

function rose_test() {
convert rose: -resize 1000x1000 -depth 8 demos/rose.ppm
straight_stitch demos/rose
cross_stitch demos/rose
}

function wizard_test() {
convert logo: -resize 1000x1000 -depth 8 demos/wizard.ppm
straight_stitch demos/wizard
cross_stitch demos/wizard
}

function logo_test() {
png2ppm demos/logo-spirals_1000
straight_stitch demos/logo-spirals_1000
cross_stitch demos/logo-spirals_1000
}

function all_tests() {
cd build
./embroider --test
donut_test
rose_test
wizard_test
logo_test
}
