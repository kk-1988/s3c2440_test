all:
	arm-linux-gcc -c -o led.o led.c	-nostdlib
	arm-linux-gcc -c -o uart.o uart.c -nostdlib
	arm-linux-gcc -c -o lib1funcs.o lib1funcs.S -nostdlib
	arm-linux-gcc -c -o my_printf.o my_printf.c -nostdlib
	arm-linux-gcc -c -o main.o main.c -nostdlib
	arm-linux-gcc -c -o start.o start.S -nostdlib
	arm-linux-ld -Ttext 0 start.o led.o uart.o lib1funcs.o my_printf.o main.o -o uart.elf
	arm-linux-objcopy -O binary -S uart.elf uart.bin
	arm-linux-objdump -D uart.elf > uart.dis
clean:
	rm *.bin *.o *.elf *.dis
	
