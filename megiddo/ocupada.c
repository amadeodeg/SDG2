#include "megiddo.h"

//-------------------------------------------------------------------------------------------
// ocupada() 
// 
// Descripción: 
//   Método que comprueba si el lugar dónde se quiere poner ficha está ocupado o vacío
//-------------------------------------------------------------------------------------------


BOOL ocupada(int fila, int columna){
	if (leerDatos(fila,columna) != LIBRE) return TRUE;
	return FALSE;
}
