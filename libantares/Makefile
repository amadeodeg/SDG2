top_srcdir = .
include $(top_srcdir)/Makeconf

LIBGLOSS_OBJS = close.o fstat.o getpid.o isatty.o kill.o lseek.o \
		open.o print.o putnum.o read.o sbrk.o stat.o unlink.o \
		write.o reset.o exit.o nanosleep.o usleep.o


all: libantares.a

libantares.a: $(LIBGLOSS_OBJS) inbyte.o outbyte.o

clean:
	rm -f *.o *.a *~
	rm -f test-antares *.hcf

install: libantares.a antares-ram-dbug.ld
	install -m 644 $^ ../trunk/newlib/m68k-elf/lib

test-antares.hcf: test-antares
test: test-antares.hcf
	../trunk/utils/serial-console -l test-antares.hcf -s 19200
