
CC=gcc

CFLAGS=-g -Wall -Werror


all: clean sin sin2 boot

sin: 
	gcc -o sin sin.c

sin2:
	gcc -o sin2 sin2.c

clean:
	$(RM) *.o sin sin2

boot:
	./sin2 43
