# Assumes that the host is linux, otherwise skips.
# Requires gcc multilib:
# $ apt install build-essential gcc-multilib

build:
	./bin/arduino-cli compile -b arduino:avr:uno `pwd`


all: install build

install:
	cp ../src/* .
	curl -fsSL https://raw.githubusercontent.com/arduino/arduino-cli/master/install.sh | sh
	./bin/arduino-cli update
	./bin/arduino-cli core install arduino:avr


