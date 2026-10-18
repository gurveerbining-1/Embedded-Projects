default:
	avr-gcc -Os -DF_CPU=16000000UL -mmcu=atmega328p -c -o display.o display.c
	avr-gcc -mmcu=atmega328p -o display.bin display.o
	avr-objcopy -O ihex -R .eeprom display.bin display.hex