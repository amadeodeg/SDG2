#CC=m68k-elf-gcc
CC=gcc
CFLAGS=-g -Wall -Werror
main: main.o calculos.o interrupciones.o visualizacionOsciloscopio.o 
