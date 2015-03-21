#include "m5272gpio.h"

int get_teclado(void){
  BYTE fila, columna, fila_mask;
  static char teclas[4][4] = {{"123C"},
                              {"456D"},
                              {"789E"},
                              {"A0BF"}};
  while(TRUE){
    for(columna = NUM_COLS - 1; columna >= 0; columna--){
      set16_puertoS(EXCIT << columna);
      nanosleep(1150);		//TODOOOOOOO   MIRA AQUI		

      for(fila = NUM_FILAS - 1; fila >= 0; fila--){
        fila_mask = EXCIT << fila;		
        if(lee16_puertoE() & fila_mask){
          while(lee_puertoE() & fila_mask);
          retardo(1150);
          return (int)teclas[fila][columna];
        }
      }
    }
  }