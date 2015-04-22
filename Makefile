include Makeconf.$(shell uname -s)

SIM=0

ifeq ($(SIM),1)

CC=gcc

CFLAGS=-g -Wall  -I. -Ilib
LDLIBS=-L. -lm5272_sim $(ARCH_LDLIBS)

FLAVOUR=_sim

else

newlibdir=newlib/m68k-elf
SPEED = `stty -F /dev/ttyS0 -a | head -1 | cut -d' ' -f2`
TIMEOUT = 10000

CC = m68k-elf-gcc
AS = m68k-elf-as
AR = m68k-elf-ar
OBJCOPY = m68k-elf-objcopy
OBJDUMP = m68k-elf-objdump

ARCH_FLAGS = -m5200

CPPFLAGS = -DXPLSED $(DEFS)
CFLAGS = $(ARCH_FLAGS) -I$(top_srcdir)/src -I$(newlibdir)/include -g -Wall -O2
LDFLAGS = -L$(top_srcdir)/src -L$(newlibdir)/lib -Tantares-ram-dbug.ld
ASFLAGS = $(ARCH_FLAGS)
LDLIBS = -lm5272_sim

FLAVOUR=


endif


SOURCES = main.c lib/calculos.c
OBJECTS = $(patsubst %.c, %.o, $(SOURCES))


libm5272_SOURCES = \
	lib/m5272adc_dac.c \
	lib/teclado_matricial.c \
	lib/interrupciones.c \
	lib/m5272gpio.c \

libm5272_OBJECTS = $(patsubst %.c, %.o, $(libm5272_SOURCES))

libm5272_sim_SOURCES = \
	lib/m5272adc_dac_sim.c \
	lib/teclado_matricial_sim.c \
	lib/tasks.c \
	lib/interrupciones_sim.c \
	lib/m5272gpio_sim.c \
	lib/mytime.c


libm5272_sim_OBJECTS = $(patsubst %.c, %.o, $(libm5272_sim_SOURCES))

all: clean libm5272$(FLAVOUR).a main

main: $(OBJECTS)

clean:
	$(RM) *.o main
	$(RM) lib/*.o libm5272*.a
	$(RM) test/*.o

libm5272.a: $(libm5272_OBJECTS)
libm5272_sim.a: $(libm5272_sim_OBJECTS)


%.a:
	$(AR) rcs $@ $^
