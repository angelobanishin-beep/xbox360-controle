CC = g++
CFLAGS = -O2 -Wall

all: programa_controle

programa_controle: main.cpp
	$(CC) $(CFLAGS) main.cpp -o programa_controle

clean:
	rm -f programa_controle
