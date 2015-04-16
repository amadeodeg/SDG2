include ../Makeconf.$(shell uname -s)

CC=gcc
CFLAGS=-g -Wall  -I.. -I../lib

all: test_dft
	./test_dft

test_dft: test_dft.o calculos.o


vpath %.c ../lib
