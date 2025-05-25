#
# In order to more efficiently test routines designed for embedded systems,
# there is a linux testing platform called embroider_elf64.
#

all: elf64

elf64:
	gcc embroider_elf64.S -o embroider_elf64

thumb:
	as -fbin -o embroider_thumb embroider_thumb.asm
	ld embroider_thumb.o -o embroider_thumb
