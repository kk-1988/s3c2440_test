all:
	arm-linux-gcc -c -o leds.o leds.c -nostdlib
	arm-linux-gcc -c -o start.o start.S
	arm-linux-ld -Ttext 0 start.o leds.o -o leds.elf
	arm-linux-objcopy -O binary -S leds.elf key_led.bin
	arm-linux-objdump -D leds.elf > leds.dis
clean:
	rm *.bin *.o *.elf *.dis
