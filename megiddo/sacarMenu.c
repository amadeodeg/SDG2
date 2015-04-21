#include "m5272lib.h"
#include "megiddo.h"

//-------------------------------------------------------------------------------------------
// sacarMenu()
//
// Descripción:
//   Método que saca el menú inicial por pantalla y pide el numero de jugadores.
//-------------------------------------------------------------------------------------------
char sacarMenu() {
  char teclaPulsada;
  output("Bienvenido al juego Megiddo.\r\n");
  output("Introduce:\r\n");
  output("A para jugar contra la máquina.\r\n");
  output("B para dos jugadores.\r\n");
  output("C para tres jugadores.\r\n");

  do{
    teclaPulsada = teclado();
    if ((teclaPulsada!='A')&&(teclaPulsada!='B')&&(teclaPulsada!='C')){
      output("ERROR: Tecla no válida. Introducir 'A', 'B' o 'C'.\r\n");  
    }

  }while((teclaPulsada!='A')&&(teclaPulsada!='B')&&(teclaPulsada!='C'));

  if (teclaPulsada == 'A'){
    setNumeroJugadores(1);
    output("Ha elegido jugar contra la máquina.\r\n");
  }
  else if (teclaPulsada == 'B'){
    setNumeroJugadores(2);
    output("Ha elegido jugar con dos jugadores.\r\n");
  }
  else if (teclaPulsada == 'C'){
    setNumeroJugadores(3);
    output("Ha elegido jugar con tres jugadores.\r\n");
  }
  
  return teclaPulsada;
}




