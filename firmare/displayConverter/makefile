OUTPUT=firmware
OBJECTS=src/main.o											\
				src/uart.o											\
				src/spi.o


CC=avr-gcc
LD=avr-ld
OBJCOPY=avr-objcopy

CPUSPEED=16000000
MCU=atmega168
CPUTYPE=m168p
CFLAGS=-mmcu=$(MCU) -I. -Os -DF_CPU=$(CPUSPEED) -DBAUD=9600
AVRDUDE=avrdude


all: $(OBJECTS)
	$(CC) -Os -Wl,--gc-sections -mmcu=$(MCU) -o $(OUTPUT).elf $(OBJECTS) -lm
	$(OBJCOPY) -O ihex -R.eeprom $(OUTPUT).elf $(OUTPUT).elf.ihex

flash:
	$(AVRDUDE) -p$(CPUTYPE) -cstk500v2 -P/dev/ttyACM3 -Uflash:w:$(OUTPUT).elf.ihex:i -U lfuse:w:0xfe:m -U hfuse:w:0xdf:m

clean:
	rm $(OBJECTS) $(OUTPUT).elf $(OUTPUT).elf.ihex -f


