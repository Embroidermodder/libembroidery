#!/bin/bash

function make_test_files () {
convert xc:white -resize '1000x1000!' -depth 8 donut.png
convert donut.png -fill black -draw "rectangle 100,100 500,500" donut.png
convert donut.png -fill white -draw "rectangle 200,200 300,300" donut.png
mv donut.png demos
convert rose: -resize '1000x1000!' -depth 8 demos/rose.png
convert logo: -resize '1000x1000!' -depth 8 demos/wizard.png
convert demos/logo-spirals.png -resize '1000x1000!' -depth 8 demos/logo.png
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

make_test_files

echo "Building..."

rm -fr build
mkdir build
cd build
cmake ..
cmake --build .
cd ..

echo "Built in tests..."

./build/embroider --test

echo "Stitch fill tests..."

test_fills demos/donut.png
test_fills demos/rose.png
test_fills demos/wizard.png
test_fills demos/logo.png
