data:
	nasm -fbin libembroidery_data.asm -l libembroidery_data.lst -o ../libembroidery_data.bin

x86:
	nasm -felf32 -o libembroidery_x86.o libembroidery_x86.asm
	ld -melf_i386 libembroidery_x86.o -o embroider

clean:
	rm -f libembroidery_x86.o embroider

all: x86 data
