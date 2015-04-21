#include <stdio.h>
#include "megiddo.h"

static
int
mover_persona_sms (struct jugador_t* j)
{
  puts ("\n(20 segs)Esperando SMS, debe tener el formato fila seguido de columna(sin espacios)");

  ms_sleep (20000);//damos un tiempo para que se envie el sms	
	
  leeInsertaSMS();

  /*
    if (ganarXpuntos (jugador)) {
    return 1;
    }
    if (ganar(jugador)) {
    return 1;
    }
  */
  return 0;
}

void nuevo_jugador_persona_sms (int jugador)
{
  struct jugador_t* j = getJugador(jugador);
  j->rep = jugador + '1';
  j->mover = mover_persona_sms;
}
