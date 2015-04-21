top_srcdir = ..
include $(top_srcdir)/Makeconf

all: libm5272.a libmegiddo.a megiddo.hcf megiddo.dep

libmegiddo.a: error.o debug.o \
		sacarMenu.o tablero.o jugador.o ocupada.o \
		GetTablero.o comeFicha.o \
		Temporizador.o pausa.o \
		jugar.o persona.o maquina.o persona_sms.o \
		sonidoGanadorYPerdedor.o sonidoSistema.o \
		mp3.o mueveMaquina.o \
		ganadorXpuntos.o ganador.o \
		sacarLCD.o \
		introNombre.o menuMusica.o \
		conectarGSM.o cleopatra.o \
		vsMaquinaSMS.o\
		estadisticas.o \
		enviarSMS.o \
		comprobarDatos.o \
		menuNombre.o \
		m5272lib.o m5272int.o m5272gpio.o m5272lcd.o teclado.o

clean:
	rm -f *.o *.a *~ *.hcf *.dep megiddo

megiddo.hcf: megiddo
megiddo: libmegiddo.a

teclas.hcf: teclas
teclas: libmegiddo.a
test-teclado: teclas.hcf
	$(top_srcdir)/utils/serial-console -s $(SPEED) -l $<

lcd.hcf: lcd
lcd: libmegiddo.a
test-lcd: lcd.hcf
	$(top_srcdir)/utils/serial-console -s $(SPEED) -l $<

gsm: gsm.o m5272lib.o
gsm.hcf: gsm
test-gsm: gsm.hcf
	$(top_srcdir)/utils/serial-console -s $(SPEED) -l $<

run: megiddo.hcf
	TIMEOUT=0 $(top_srcdir)/utils/serial-console -s $(SPEED) -l $<
