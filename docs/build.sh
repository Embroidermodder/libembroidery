#!/bin/bash

sudo apt-get update &> deps.log
sudo apt-get upgrade &>> deps.log
sudo apt-get install doxygen &>> deps.log
pip install sphinx sphinx-book-theme breathe &>> deps.log
git submodule init &>> deps.log
git submodule update &>> deps.log

for project in embroidermodder embroiderymobile pet libembroidery
do
    cd source/$project
        doxygen || exit 1
    cd ../..
done

make html || exit 1
