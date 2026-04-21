#!/bin/bash

for file in `find src`
do
	indent -linux -i8 -nut $file
done
