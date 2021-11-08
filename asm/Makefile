all: x86 arm avr data

data:
	nasm -fbin libembroidery_data.asm -l libembroidery_data.lst -o ../libembroidery_data.bin

x86:
	gcc -no-pie -m32 -o embroider_x86 libembroidery_x86.S

arm:
	gcc -E libembroidery_arm.S -o libembroidery_arm.s
	arm-none-eabi-as -o embroider_arm.o libembroidery_arm.s
	arm-none-eabi-ld -o embroider_arm embroider_arm.o

avr:
	avr-none-eabi-gcc -no-pie -o embroider_avr libembroidery_avr.S

clean:
	rm -f embroider*
