#include <string.h>
#include "megiddo.h"

#define FILAS 6
#define COLUMNAS 6

//Definimos el tablero como un array 6x6
//de tipo int, pudiendo tomar los valores:
//0 si está vacía la casilla
//un número positivo que se corresponde 
//con el del jugador que tiene ficha en esa casilla

static int tablero[FILAS][COLUMNAS];

//Inserta fichas en la posición especificada
//según las normas establecidas

void insertarDatos(int fila, int columna, int jugador){
	tablero[fila][columna]=jugador;
}

//devuelve el entero de la posición especificada
//indicándonos si está vacía o en caso contrario
//el jugador que tiene metida la ficha

int leerDatos(int fila, int columna){
	
	return tablero[fila][columna];
		
}

void limpiarTablero (void) {
  memset (tablero, LIBRE, sizeof(tablero));
}
