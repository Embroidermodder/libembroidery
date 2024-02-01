#!/bin/bash

pip install sphinx sphinx-book-theme &> deps.log

cd docs
python3 -m sphinx -M html . . || exit 1
cd ..
