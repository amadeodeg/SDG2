#include <stdio.h>
#include "megiddo.h"

void nJugadores(void)
{
  int i;
  limpiarTablero ();
  resetJugadores();
  for (i = 0; i < getNumeroJugadores(); ++i) {
    nuevo_jugador_persona (i);
  }
  
  jugar ();
}

//-------------------------------------------------------
//
//Metodo principal del modo jugador vs maquina.
//
//comprueba si hay ganador
//pide que situe la ficha en el tablero
//comprueba que esa posicion no este ocupada
//la añade al tablero y come las fichas que sean pertinentes
//imprime el tablero
//cambia el turno
//
//-------------------------------------------------------
void vsMaquina(void)
{
  char tecla;
 
  puts("Pulse 1 para nivel fácil;\n 2-nivel medio;\n 3-nivel difícil");
  do {
    tecla = teclado();
    if (tecla>='1' && tecla<='3'){ 
      asignarNivel(tecla);
      break;
    }
    puts ("pulse correctamente");

  } while (TRUE);

  limpiarTablero ();
  initJugadores();
  nuevo_jugador_persona (0);
  nuevo_jugador_maquina (1);
  
  jugar ();
}


static
void finTurno (void)
{
  megiddo_error = 1;
}

static
int peque_juego (void)
{
  limpiarTablero ();
  resetJugadores ();
  set_pausado (0);
  while (1) {
    int ret;
    struct jugador_t* j = getJugador(getJugadorActual());
    getTablero();
    printf ("Jugador %c (%s)\n", j->rep, j->nombre);
    tareaTemporizada (60000, finTurno);
    j->fichasComidas = 0;
    ret = j->mover(j);
    eliminarTareaTemporizada (finTurno);
    if (megiddo_error) {
      printf ("\nError: %s\n", mensaje_error(megiddo_error));
      megiddo_error = 0;
    }
    else
      j->movimientos++;
    if (ret > 0) {
      set_pausado (1);
      j->pequejuegos++;
      return total_ganado (j->rep);
    }
    cambiarJugador();
  }
}

void jugar (void)
{
  struct jugador_t* j = 0;
  tareaTemporizada (1000, sacarLCD);
  while (! peque_juego ());
  j = getJugador(getJugadorActual());
  printf ("Ha ganado el jugador %c (%s)\n", j->rep, j->nombre);
  eliminarTareaTemporizada (sacarLCD);
  tocarMelodiaGanador ();
}
