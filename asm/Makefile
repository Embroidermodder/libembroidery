data:
	nasm -fbin libembroidery_data.asm -l libembroidery_data.lst -o ../libembroidery_data.bin

x86:
	nasm -o libembroidery_x86.o libembroidery_x86.asm -felf32
	ld -melf_i386 libembroidery_x86.o -o embroider_x86

arm:
	m4 libembroidery_arm.asm > libembroidery_arm.s
	as -o libembroidery_arm.o libembroidery_arm.s
	ld libembroidery_arm.o -o embroider_arm

avr:
	m4 libembroidery_avr.asm > libembroidery_avr.s
	as -o libembroidery_avr.o libembroidery_avr.s
	ld libembroidery_avr.o -o embroider

clean:
	rm -f libembroidery_*.o libembroidery_*.s embroider

all: x86 data
