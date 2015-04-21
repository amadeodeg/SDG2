#include <string.h>
#include "megiddo.h"

#define MAXJUGADORES 3

static struct jugador_t j[MAXJUGADORES];
static volatile int jugador_actual = 0;
static int njugadores = 0;

static
void inc_tiempo_jugador (void)
{
  if ( ! pausado()) {
    struct jugador_t* j = getJugador(jugador_actual);
    j->tiempo++;
    j->tiempo_total++;
  }
  tareaTemporizada (1000, inc_tiempo_jugador);
}

void initJugadores (void)
{
  jugador_actual = 0;
  memset (j, 0, MAXJUGADORES * sizeof (struct jugador_t));
}

void resetJugadores (void)
{
  int i;

  eliminarTareaTemporizada (inc_tiempo_jugador);
  for (i = 0; i < getNumeroJugadores(); ++i) {
    j[i].pequejuegos = 0;
    j[i].tiempo = 0;
    j[i].tiempo_total = 0;
    j[i].fichasComidas = 0;
    j[i].megiddos = 0;
    j[i].movimientos = 0;
  }
  jugador_actual = 0;
  set_pausado (1);
  tareaTemporizada (1000, inc_tiempo_jugador);
}

struct jugador_t* getJugador (int i)
{
  if (i >= '1')
    i -= '1';
  if (i >= MAXJUGADORES)
    return 0;
  return &j[i];
}

void cambiarJugador(void)
{
  struct jugador_t* j;
  jugador_actual = (jugador_actual + 1) % getNumeroJugadores();
  j = getJugador (jugador_actual);
  j->tiempo = 0;
}

int getJugadorActual(void)
{
  return jugador_actual;
}

//-------------------------------------------------------------------------------------------
// int getNumeroJugadores()
//
// Método que devuelve el número de jugadores. Si no se ha inicializado el juego, dará 0.
//
//-------------------------------------------------------------------------------------------
int getNumeroJugadores()
{
  return njugadores;
}

void setNumeroJugadores(int n)
{
  njugadores = n;
}


#ifndef NDEBUG
#include <stdio.h>

void
debug_jugador (void)
{
  int i;
  int n = getNumeroJugadores();

  printf ("%d jugadores\n", n);
  for (i = 0; i < n; ++i) {
    printf (" %c%c: %s, t=%d, p=%d\n",
	    (getJugadorActual() == i)? '>' : ' ',
	    j[i].rep, j[i].nombre, j[i].tiempo, j[i].contPuntos);
  }
}

#endif
