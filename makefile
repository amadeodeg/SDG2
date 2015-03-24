
CC=gcc

CFLAGS=-g -Wall -Werror -I.
LDLIBS=-L. -lm5272_sim

FLAVOUR=_sim

SOURCES = main.c
OBJECTS = $(patsubst %.c, %.o, $(SOURCES))

libm5272_SOURCES = 
libm5272_OBJECTS = $(patsubst %.c, %.o, $(libm5272_SOURCES))

libm5272_sim_SOURCES = \
	lib/m5272adc_dac_sim.c \
	lib/teclado_matricial_sim.c

libm5272_sim_OBJECTS = $(patsubst %.c, %.o, $(libm5272_sim_SOURCES))

all: libm5272$(FLAVOUR).a main

main: $(OBJECTS)

clean:
	$(RM) *.o main
	$(RM) lib/*.o libm5272*.a

libm5272.a: $(libm5272_OBJECTS)
libm5272_sim.a: $(libm5272_sim_OBJECTS)

%.a:
	ar rcs $@ $^