#include "megiddo.h"

static
int
mover_maquina (struct jugador_t* j)
{
  mueveMaquina ();
  return 0;
}

void nuevo_jugador_maquina (int jugador)
{
  struct jugador_t* j = getJugador(jugador);
  j->rep = jugador + '1';
  j->mover = mover_maquina;
}
