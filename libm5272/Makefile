top_srcdir=..

include $(top_srcdir)/Makeconf.FLAVOUR
include $(top_srcdir)/Makeconf.$(FLAVOUR)

CFLAGS=-g -Wall
LDLIBS=$(ARCH_LDLIBS)

libm5272_sim_SOURCES = \
	m5272adc_dac_sim.c \
	m5272gpio_sim.c \
	m5272lcd_sim.c \
	teclado_matricial_sim.c
	
libm5272_sim_OBJECTS = $(patsubst %.c, %.o, $(libm5272_sim_SOURCES))


libm5272_SOURCES = \
	m5272adc_dac.c \
	m5272gpio.c \
	m5272lcd.c \
	teclado_matricial.c
	
libm5272_OBJECTS = $(patsubst %.c, %.o, $(libm5272_SOURCES))



all: clean libm5272$(SIM).a

libm5272.a: $(libm5272_OBJECTS)
libm5272_sim.a: $(libm5272_sim_OBJECTS)

clean:
	$(RM) *.o libm5272*.a

%.a:
	$(AR) rcs $@ $^