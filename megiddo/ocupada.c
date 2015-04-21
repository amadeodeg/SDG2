#include "megiddo.h"

//-------------------------------------------------------------------------------------------
// ocupada() 
// 
// Descripci�n: 
//   M�todo que comprueba si el lugar d�nde se quiere poner ficha est� ocupado o vac�o
//-------------------------------------------------------------------------------------------


BOOL ocupada(int fila, int columna){
	if (leerDatos(fila,columna) != LIBRE) return TRUE;
	return FALSE;
}
