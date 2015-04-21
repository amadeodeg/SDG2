#include <stdio.h>
#include "megiddo.h"

static
int
mover_persona (struct jugador_t* j)
{
  int fila;
  int columna;

  while (1) {
    fila = leerFila();
    if (fila < 0)
	return 0;
    columna = leerColumna();
    if (columna < 0)
	return 0;
    if (!ocupada (fila,columna))
      break;
    printf ("Posicion ocupada\n");
  }
    
  insertarDatos (fila, columna, j->rep);
  if (getCleopatra())
    cleopatra(fila, columna, j->rep);
  comeFicha (fila, columna, j->rep);
  busca_megiddos (j->rep);
  if (total_ganado(j->rep) || juego_ganado(j->rep))
    return 1;
  return 0;
}

void nuevo_jugador_persona (int jugador)
{
  struct jugador_t* j = getJugador(jugador);
  j->rep = jugador + '1';
  j->mover = mover_persona;
}

