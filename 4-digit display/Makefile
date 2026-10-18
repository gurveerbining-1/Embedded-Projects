default:
	avr-gcc -Os -DF_CPU=16000000UL -mmcu=atmega328p -c -o countdown.o countdown.c
	avr-gcc -mmcu=atmega328p -o countdown.bin countdown.o
	avr-objcopy -O ihex -R .eeprom countdown.bin countdown.hex