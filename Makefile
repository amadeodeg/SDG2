top_srcdir=.
SPEED=19200

include $(top_srcdir)/Makeconf.$(shell uname -s)
include $(top_srcdir)/Makeconf.FLAVOUR
include $(top_srcdir)/Makeconf.$(FLAVOUR)

SOURCES +=	main.c \
			calculos.c \
			interrupciones$(SIM).c 

OBJECTS = $(patsubst %.c, %.o, $(SOURCES))

SUBDIRS = \
		libm5272


all: clean main

main: $(OBJECTS)

libs: 
	$(MAKE) -C $(top_srcdir)/libm5272

clean:
	$(RM) *.o main *.dep *.hcf

load: 
	$(top_srcdir)/utils/serial-console -s 19200 -l main.hcf