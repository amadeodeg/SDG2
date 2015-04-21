#include <stdio.h>
#include "megiddo.h"
#include "m5272lib.h"


//Rutina que comprueba los datos introducidos 
// y muestra un mensaje de error si no es correcto


//------------------------------------------------------
//int leerFila(char tecla)
//
//Lee del teclado y si se introduce de A a F
// devuelve un entero de 1 a 6 que es la fila seleccionada
//En caso de pulsar otra tecla lanza mensaje de error 
//
//------------------------------------------------------
int leerFila()
{
  while (1) {
    char tecla;
    printf ("Introduzca el radio\n"
	    " radio (entre A y F): ");
    fflush(stdout);
    tecla = teclado();
    if (tecla < 0)
	return -1;
    if((tecla >= 'A')&&(tecla <= 'F')) {
      printf ("%c\n", tecla);
      return tecla - 'A';
    }
    output("ERROR: Tecla no valida.\r\n");
  }
}

//------------------------------------------------------
//int leerColumna(char tecla)
// 
//Lee del teclado y si se introduce de 1 a 6
//devuelve un entero de 1 a 6 que es la columna seleccionada
//En caso de pulsar otra tecla lanza mensaje de error 
//
//------------------------------------------------------

int leerColumna()
{
  while (1) {
    char tecla;
    printf ("Introduzca la columna\n"
	    " columna (entre 1 y 6): ");
    fflush(stdout);
    tecla = teclado();
    if (tecla < 0)
	return -1;
    if((tecla >= '1')&&(tecla <= '6')) {
      printf ("%c\n", tecla);
      return tecla - '1';
    }
    output("ERROR: Tecla no valida.\r\n");
  }
}
