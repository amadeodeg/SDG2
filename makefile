#CC=m68k-elf-gcc
CC=gcc
CFLAGS=-g -Wall -Werror
LDLIBS= -L. -lm5272_sim
#LDLIBS= -L. -lm5272
main: main.o calculos.o interrupciones.o visualizacionOsciloscopio.o 
