all:
	arm-linux-gcc -c -o led.o led.c -nostdlib 
	arm-linux-gcc -c -o uart.o uart.c -nostdlib 
	arm-linux-gcc -c -o init.o init.c -nostdlib 
	arm-linux-gcc -c -o main.o main.c -nostdlib 
	arm-linux-gcc -c -o start.o start.S
	arm-linux-ld -Ttext 0 start.o led.o uart.o init.o main.o -o sdram.elf
	arm-linux-objcopy -O binary -S sdram.elf sdram.bin
	arm-linux-objdump -D sdram.elf > sdram.dis
clean:
	rm *.bin *.o *.elf *.dis
	
