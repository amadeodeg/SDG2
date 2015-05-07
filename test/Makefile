top_srcdir=..

include ../Makeconf.$(shell uname -s)
include $(top_srcdir)/Makeconf.FLAVOUR
include $(top_srcdir)/Makeconf.$(FLAVOUR)

top_srcdir=..

SOURCES = main.c ../interrupciones.c 
OBJECTS = $(patsubst %.c, %.o, $(SOURCES))


all: test_dft
	./test_dft

test_dft: test_dft.o calculos.o

main: $(OBJECTS)

vpath %.c ../lib
