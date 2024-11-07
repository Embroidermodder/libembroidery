#
# In order to more efficiently test routines designed for embedded systems,
# there is a linux testing platform called emb_elf64_test.
#

all:
	nasm -felf64 -o emb_elf64_test.o emb_elf64_test.asm
	ld emb_elf64_test.o -o emb_elf64_test
	nasm -fbin -o emb_thumb emb_thumb.asm

