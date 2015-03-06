//------------------------------------------------------------------------------
// Teclado_GNU.c
//
//   Programa ejemplo para el manejo de un teclado matricial.
//
// Autores: Juan Manuel Montero y Rub�n San Segundo.
// Adaptado a C por: Javier Guill�n �lvarez
//------------------------------------------------------------------------------
#include "m5272lib.c"
#include "m5272gpio.c"

#define NUM_FILAS 4
#define NUM_COLS 4
#define EXCIT 1

//------------------------------------------------------
// char teclado(void)
//
// Descripci�n:
//   Explora el teclado matricial y devuelve la tecla 
//   pulsada
//------------------------------------------------------
char teclado(void)
{
  //char tecla;
  BYTE fila, columna, fila_mask;
  static char teclas[4][4] = {{"123C"},
                              {"456D"},
                              {"789E"},
                              {"A0BF"}};
  // Bucle de exploraci�n del teclado
  while(TRUE){

    // Excitamos una columna
    for(columna = NUM_COLS - 1; columna >= 0; columna--){
      set16_puertoS(EXCIT << columna);		// Se env�a la excitaci�n de columna
      retardo(1150);				// Esperamos respuesta de optoacopladores

      // Exploramos las filas en busca de respuesta
      for(fila = NUM_FILAS - 1; fila >= 0; fila--){
        fila_mask = EXCIT << fila;		// M�scara para leer el bit de la fila actual
        if(lee16_puertoE() & fila_mask){		// Si encuentra tecla pulsada,
          while(lee_puertoE() & fila_mask);	//   Esperamos a que se suelte
          retardo(1150);			//   Retardo antirrebotes
          return teclas[fila][columna];		//   Devolvemos la tecla pulsada
        }
      }
      // Siguiente columna
    }
    // Exploraci�n finalizada sin encontrar una tecla pulsada
  }
  // Reiniciamos exploraci�n
}

//------------------------------------------------------
// void bucleMain(void)
//
// Descripci�n:
//   Funci�n del programa principal
//------------------------------------------------------
void bucleMain(void)
{
  char tecla;
  tecla = teclado();
  outch(tecla);
}

//------------------------------------------------------
// void __init(void)
//
// Descripci�n:
//   Funci�n por defecto de inicializaci�n del sistema
//------------------------------------------------------
void __init(void){}

//---------------------------------------------------------
// Definici�n de rutinas de atenci�n a la interrupci�n
// Es necesario definirlas aunque est�n vac�as
void rutina_int1(void){}
void rutina_int2(void){}
void rutina_int3(void){}
void rutina_int4(void){}
void rutina_tout0(void){}
void rutina_tout1(void){}
void rutina_tout2(void){}
void rutina_tout3(void){}
