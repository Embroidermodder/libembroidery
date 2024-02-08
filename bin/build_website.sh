#!/bin/bash

cp *.tar docs/_static

cp bin/* docs/_static

pip install sphinx &> deps.log || exit 1

cd docs || exit 1
    python3 -m sphinx -M html . . || exit 1
cd .. || exit 1

bash bin/build_refman.sh
