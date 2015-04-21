#include "megiddo.h"

//Variables

int num ; 
int j;

//------------------------------------------------------
//int exploraFila (i,jugador)
//
//explora que si hay seis jugadors en una columna
//------------------------------------------------------

int exploraFila(i,jugador) {
	num = 0;
	for (j=0; j<6;j ++){
		if(leerDatos(i,j) == jugador){
			num++;
		}
	}return num;
}

//------------------------------------------------------
//int exploraColumna (i,jugador)
//
//explora que si hay seis jugadors en una columna
//------------------------------------------------------
				
int exploraColumna(i,jugador) {
	num = 0;
	for (j=0; j<6;j ++){
		if(leerDatos(j,i) == jugador){
			num++;
		}
	}return num;
}

//------------------------------------------------------
//int exploraDiagonalPpal(i,jugador)
//
// explora las diagonalas de derecha a izquierda
//------------------------------------------------------

int exploraDiagonalPpal(i, jugador){
	num = 0;
	for (j=0; j<6;j++){
		if(leerDatos(i,j) == jugador){
			num++;
			i++;
			if(i>5)	i= 0;
		}
	}
	return num;
}

//------------------------------------------------------
//int exploraDiagonalSecundaria(i,jugador)
//
// explora las diagonalas de derecha a izquierda
//------------------------------------------------------

int exploraDiagonalSecundaria(i, jugador){
	num = 0;
	
	for(j=5; j>=0;j--){
		if(leerDatos(i,j) == jugador){
			num++;
			i--;
			if(i<0)	i= 5;		
		}
	}
	return num;	
}

//-------------------------------------------------------------------------------------------
// ganador()
//
// Descripción:
//   Método que comprueba si se gana.
//-------------------------------------------------------------------------------------------

BOOL ganador(int jugador)
{
  int i;
  for (i=0; i<6; i++){
    if (exploraFila(i,jugador) == 6) return TRUE;	
    if (exploraColumna(i,jugador) == 6) return TRUE;
    if (exploraDiagonalPpal(i,jugador) == 6) return TRUE;
    if (exploraDiagonalSecundaria(i,jugador) == 6) return TRUE;
  }
  return FALSE;
}


