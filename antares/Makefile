top_srcdir=..

include $(top_srcdir)/Makeconf.FLAVOUR
include $(top_srcdir)/Makeconf.$(FLAVOUR)

CFLAGS=-g -Wall
LDLIBS=$(ARCH_LDLIBS)

antares_SOURCES = \
	m5272adc_dac.c \
	m5272gpio.c \
	m5272int.c \
	m5272lcd.c \
	teclado.c
	
antares_OBJECTS = $(patsubst %.c, %.o, $(antares_SOURCES))



all: clean antares.a

antares.a: $(antares_OBJECTS)

clean:
	$(RM) *.o antares*.a

%.a:
	$(AR) rcs $@ $^