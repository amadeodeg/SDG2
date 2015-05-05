top_srcdir=.

include $(top_srcdir)/Makeconf.$(shell uname -s)
include $(top_srcdir)/Makeconf.FLAVOUR
include $(top_srcdir)/Makeconf.$(FLAVOUR)

SOURCES = \
		main.c \
		calculos.c \
		interrupciones$(SIM).c 

OBJECTS = $(patsubst %.c, %.o, $(SOURCES))

SUBDIRS = \
		libm5272


all: clean $(SUBDIRS) main

main: $(OBJECTS)

clean:
	$(RM) *.o main

$(SUBDIRS):
	@echo $@
	$(MAKE) -C $@