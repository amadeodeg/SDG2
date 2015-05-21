//------------------------------------------------------------------------------
// Teclado_GNU.c
//
//   Programa ejemplo para el manejo de un teclado matricial.
//
// Autores: Juan Manuel Montero y Rubén San Segundo.
// Adaptado a C por: Javier Guillén Álvarez
//------------------------------------------------------------------------------

#include "m5272lib.h"
#include "m5272gpio.h"
#include <unistd.h>

#define NUM_FILAS 4
#define NUM_COLS 4
#define EXCIT 1

//------------------------------------------------------
// char teclado(void)
//
// Descripción:
//   Explora el teclado matricial y devuelve el caracter 
//   de la tecla pulsada
//------------------------------------------------------
int get_tecla(void)
{
  BYTE fila, columna, fila_mask;
  int tecla;
  static char teclas[4][4] = {{"123C"},
			                        {"456D"},
			                        {"789E"},
			                        {"A0BF"}};

  // Bucle de exploración del teclado
  while (1) {
    // Excitamos una columna
    for(columna = NUM_COLS - 1; columna >= 0; columna--){
      cli();
      set_puertoS (EXCIT << columna);		// Se envía la excitación de columna
      usleep (5000);				// Esperamos respuesta de optoacopladores

      // Exploramos las filas en busca de respuesta
      for(fila = NUM_COLS - 1; fila >= 0; fila--){
	fila_mask = EXCIT << fila;		// Máscara para leer el bit de la fila actual
	if(lee_puertoE() & fila_mask){		// Si encuentra tecla pulsada,
	  while(lee_puertoE() & fila_mask);	//   Esperamos a que se suelte
	  sti();
	  usleep (5000);			//   Retardo antirrebotes
	  tecla =  teclas[fila][columna];
	  return tecla;
	}
      }
      // Siguiente columna
      usleep (10000);
    }
    // Exploración finalizada sin encontrar una tecla pulsada
    usleep (10000);
  }

  // Reiniciamos exploración
}

//Devuelve el entero de varias cifras al pulsar varias teclas sucesivas.
//Para señalar el fin del numero, pulsar cualquier letra. No devuelve letras.
int 
get_numero_teclado(void)
{
  int aux;
  int tecla = 0;
  while ( (aux = get_tecla() - '0') < 10){ 
    tecla = tecla*10 + aux;
  }
  return tecla;
}

