#include "m5272lib.h"
#include "megiddo.h"

int getTiempoXPartida (struct jugador_t* j) 
{
  return j->tiempo_total / j->pequejuegos;
}

