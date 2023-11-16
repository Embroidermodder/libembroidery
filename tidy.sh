#!/bin/bash

echo "This script enforces some of our style requirements"
echo "and warns developers about possible untidy code."
echo ""
echo "See the reference manual for the full list of rules."

for file in src/*.c src/*.h src/geometry/*.c src/formats/*.c
do
    sed -i 's/\r$//' $file
    sed -i 's/\t/    /' $file
    sed -i 's/ $//' $file
    gcc -fdump-tree-all -c $file
done

# Report changes.
git diff
