#ifndef MEGIDDO_H
#define MEGIDDO_H

#include "m5272lib.h"

#define TECLA_PAUSA '0'
#define LIBRE '\0'

#define MAQUINA '2'

extern volatile int megiddo_error;
const char* mensaje_error (int err);

#define MAXNOMBRE 20
struct jugador_t {
  char nombre[MAXNOMBRE];
  char rep;
  int contPuntos;
  int fichasComidas;
  int megiddos;
  int pequejuegos;
  int movimientos;
  volatile int tiempo; // tiempo que lleva jugando
  volatile int tiempo_total;

  // hace un movimiento en el tablero actual
  // retorna 1 si el juego actual ha terminado
  int (*mover) (struct jugador_t*);
};

void nuevo_jugador_persona (int jugador);
void nuevo_jugador_persona_sms (int jugador);
void nuevo_jugador_maquina (int jugador);
void jugar (void);

void asignarNivel(char a);

void initJugadores (void);
void resetJugadores (void);
struct jugador_t* getJugador (int i);
void cambiarJugador (void);
int getJugadorActual(void);

typedef char (*teclado_func_t) (void);
teclado_func_t registrar_func_teclado (teclado_func_t f);
int teclado(void);

void setCleopatra (int selec);
int getCleopatra (void);
void cleopatra (int fila, int columna, int jugador);


char sacarMenu(void);
int getNumeroJugadores(void);
void setNumeroJugadores(int n);
void menuNombre(void);
char* getNombreJugador (int n);

int contadorFichasComidas(int jugador);

void insertarDatos(int fila, int columna, int jugador);
int leerDatos(int fila, int columna);
void limpiarTablero (void);

void getTablero(void);
BOOL ocupada(int fila, int columna);
BOOL juego_ganado (int jugador);
BOOL total_ganado (int jugador);
void busca_megiddos (int jugador);

int leerFila(void);
int leerColumna(void);

void comeFicha(int fila, int columna, int jugador);

void configurarSonidoSistema(void);
int efectoActivo(void);
void tocarMelodiaGanador(void);
void tocarMelodiaPerdedor(void);

void activarMP3(void);
void desactivarMP3(void);
void inicializarMP3(void);
//retardoMP3(int tiempoRetardo);

void inicializarGSM(void);
void enviaSerie(char* mensaje);
void recibeSerie(void);
void end(void);
void introducirPIN(char* pin);
void CLR_zona_datos(void);

BYTE recibeSerie2();
BYTE getRadio();
BYTE getCirculo();


void enviarSMS(char* numTelefono,char* textoEnviar);
void enviarEstadisticaSMSDosJugadores(char* numTelefono);
void enviarEstadisticaSMSTresJugadores(char* numTelefono);

char menuMusica(void);
int getTipoMusica(void);

void nJugadores(void);
void initTemporizador(void);
typedef void (*tarea_func_t) (void);
void tareaTemporizada (int ms, tarea_func_t f);
void eliminarTareaTemporizada (tarea_func_t f);
ULONG getTiempo (void);
void ms_sleep (int ms);

int pausado ();
void set_pausado (int i);
void pausa ();

void mueveMaquina(void);

char* introNombre(void);

void vsMaquina(void);

void resetEstadisticas(void);
void fichaComida(int jugador);
void estTiempo(void);
void sumaPuntos(int jugador, int pun);
void mov(int jugador);
void sumpartida(void);
int getFichasComidas(int jug);
ULONG getFichasComidasXPartida(int jug);
int getPuntos(int jug);
int getMovimientos(int jug);
int getTiempoXPartida(struct jugador_t* j);
int getNumPartidas();

void vsMaquinaSMS();
void leeInsertaSMS();
void eliminaMensaje(char* pos);

void initLCD (void);
void sacarLCD(void);

#ifndef NDEBUG
void debug (int tecla);
#endif

#endif

