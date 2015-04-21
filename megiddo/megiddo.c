#include "m5272lib.h"
#include "megiddo.h"
#include <stdio.h>

//-----------------------------------------------------
// void main (void)
//
// Punto de entrada al juego Megiddo
// Lleva a cabo la bifurcacion entre juego con 2 jugadores o con más
//
//-----------------------------------------------------
int main (void)
{
  initTemporizador();
  cli();
  configurarSonidoSistema();
  initLCD ();
  while (1) {
    sacarMenu();
    menuNombre();
    menuMusica();//mejor despues del menu principal

    puts ("Si desea jugar con la variante CLEOPATRA pulse A, si no, pulse otra tecla");
    setCleopatra (teclado() == 'A');

    switch (getNumeroJugadores()) {
    case 3:
    case 2:
      nJugadores ();
      break;
    case 1:
      setNumeroJugadores(2);
      puts("Pulse A si quiere jugar via teclado matricial o B para jugar via SMS");
      char tecla = teclado();
	
      if (tecla=='A') {
	vsMaquina (); //bifurcamos al modo de juego de jugador contra máquina
      }
      if (tecla=='B') {
	vsMaquinaSMS ();
      }
      break;
    default:
      printf ("No implementado %d jugadores\n", getNumeroJugadores());
    }
  }
  return 0;
}

