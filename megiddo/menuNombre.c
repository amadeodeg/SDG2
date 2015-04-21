#include "megiddo.h"
#include <stdio.h>
#include <string.h>

//se llama al principio del programa principal para preguntar los nombres.
void menuNombre(){
  int i;
  for (i = 0; i < getNumeroJugadores(); ++i) {
    struct jugador_t* j = getJugador(i);
    printf ("\nJugador %d:\n", i + 1);
    strncpy (j->nombre, introNombre(), MAXNOMBRE);
  }
}




		
