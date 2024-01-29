#!/bin/bash

pacman -S gcc cmake git bash mingw-w64-SDL2 \
	mingw-w64-SDL2_image mingw-w64-SDL2_ttf
git clone https://github.com/Embroidermodder/Embroidermodder
cd Embroidermodder
bash build.sh
