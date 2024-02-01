#!/bin/bash

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
