CC = powerpc-linux-gnu-g++
OBJCOPY = powerpc-linux-gnu-objcopy
CFLAGS = -O2 -Wall

all: controle.xex

controle.elf: main.cpp
	$(CC) $(CFLAGS) main.cpp -o controle.elf

controle.xex: controle.elf
	$(OBJCOPY) -O binary controle.elf controle.xex

clean:
	rm -f *.elf *.xex
