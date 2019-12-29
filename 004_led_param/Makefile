all:
	arm-linux-gcc -c -o led_param.o 004_led_param.c -nostdlib
	arm-linux-gcc -c -o start.o start.S
	arm-linux-ld -Ttext 0 start.o led_param.o -o led.elf
	arm-linux-objcopy -O binary -S led.elf led.bin
	arm-linux-objdump -D led.elf > led.dis
clean:
	rm *.bin *.o *.elf *.dis
