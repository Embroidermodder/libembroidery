#!/bin/bash

rm -fr build
mkdir build
cd build
cmake ..
make 2> build_error.log
./embroider --test

convert xc:white -geometry 1000x1000 -depth 8 output.ppm
convert output.ppm -fill black -draw "rectangle 100,100 500,500" output.ppm
convert output.ppm -fill white -draw "rectangle 200,200 300,300" output.ppm
./embroider --fill output.ppm 130 output.csv
./embroider --render output.csv result.ppm

convert rose: -resize 1000x1000 -depth 8 rose.ppm
./embroider --fill rose.ppm 130 rose.csv
./embroider --render rose.csv rose_stitches.ppm

./embroider --cross-stitch rose.ppm 130 rose.csv
./embroider --render rose.csv rose_cross.ppm
cd ..
