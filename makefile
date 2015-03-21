#Opciones de simulacion
CC=gcc
#LDLIBS= -L. -lm5272_sim
#CFLIB_SIM_OBJS=m5272adc_dac_sim.o
COSAS=
#-----------------------
#Opciones de coldfire
#CC=m68k-elf-gcc
#LDLIBS= -L. -lm5272
#CFLIB_OBJS=
#-----------------------
CFLAGS=-g -Wall -Werror -I
#%.a:
# ar rcs $@ $^
#libm5272.a: $(CFLIB_OBJS)
#libm5272_sim.a: $(CFLIB_SIM_OBJS)
#visualizacionOsciloscopio.o interrupciones.o
OBJECTS = main.o ./lib/m5272adc_dac_sim.o ./lib/teclado_matricial_sim.o 
FUENTES = main.c ./lib/m5272adc_dac_sim.c ./lib/teclado_matricial_sim.c 


main: $(OBJECTS)
	$(CC) $(OBJECTS) $(CFLAGS) -o main

depend:
	makedepend $(FUENTES) 
