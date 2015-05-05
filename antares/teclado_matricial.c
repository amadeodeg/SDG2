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
#include "../megiddo/megiddo.h"


#define NUM_FILAS 4
#define NUM_COLS 4
#define EXCIT 1

static teclado_func_t manejador_teclado = 0;

teclado_func_t registrar_func_teclado (teclado_func_t f)
{
  teclado_func_t old = manejador_teclado;
  manejador_teclado = f;
  return old;
}

//------------------------------------------------------
// char teclado(void)
//
// Descripción:
//   Explora el teclado matricial y devuelve la tecla
//   pulsada
//------------------------------------------------------
int get_teclado(void)
{
  BYTE fila, columna, fila_mask;
  int tecla;
  static char teclas[4][4] = {{"123C"},
			      {"456D"},
			      {"789E"},
			      {"A0BF"}};

  if (manejador_teclado)
    return manejador_teclado();
  // Bucle de exploración del teclado
  while (1) {
    if (megiddo_error) {
      return -1;
    }
    // Excitamos una columna
    for(columna = NUM_COLS - 1; columna >= 0; columna--){
      cli();
      set_puertoS (EXCIT << columna);		// Se envía la excitación de columna
      retardo (5000);				// Esperamos respuesta de optoacopladores

      // Exploramos las filas en busca de respuesta
      for(fila = NUM_COLS - 1; fila >= 0; fila--){
	fila_mask = EXCIT << fila;		// Máscara para leer el bit de la fila actual
	if(lee_puertoE() & fila_mask){		// Si encuentra tecla pulsada,
	  while(lee_puertoE() & fila_mask);	//   Esperamos a que se suelte
	  sti();
	  retardo (5000);			//   Retardo antirrebotes
	  tecla =  teclas[fila][columna];
	  if (!pausado() && (tecla == TECLA_PAUSA)) {
	    pausa ();
	    return teclado();
	  }
	  return tecla;
	}
      }
      // Siguiente columna
      retardo (10000);
    }
    // Exploración finalizada sin encontrar una tecla pulsada
    retardo (10000);
  }

  // Reiniciamos exploración
}

