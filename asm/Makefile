all: x86 arm avr data

data:
	nasm -fbin libembroidery_data.asm -l libembroidery_data.lst -o ../libembroidery_data.bin

x86:
	gcc -m32 -o embroider libembroidery_x86.s

arm:
	arm-none-eabi-gcc -o embroider_arm libembroidery_arm.s

avr:
	avr-none-eabi-gcc -o embroider_avr libembroidery_arm.s

clean:
	rm -f embroider*
