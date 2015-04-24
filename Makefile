top_srcdir=.

include $(top_srcdir)/Makeconf.$(shell uname -s)
include $(top_srcdir)/Makeconf.FLAVOUR
include $(top_srcdir)/Makeconf.$(FLAVOUR)

SOURCES = \
		main.c \
		calculos.c \
		interrupciones$(SIM).c \
		mytime.c \
		tasks.c 


OBJECTS = $(patsubst %.c, %.o, $(SOURCES))



all: clean  main

main: $(OBJECTS)

clean:
	$(RM) *.o main

