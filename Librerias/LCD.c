//------------------------------------------------------------------------------
// LCD_GNU.c
//
//   Programa ejemplo para el manejo de un LCD.
//
// Autores: Juan Manuel Montero y Rub�n San Segundo.
// Adaptado a C por: Javier Guill�n �lvarez
//------------------------------------------------------------------------------
#include "m5272lib.c"
#include "m5272lcd.c"

//------------------------------------------------------
// void __init(void)
//
// Descripci�n:
//   Funci�n por defecto de inicializaci�n del sistema
//------------------------------------------------------
void __init(void)
{
  LCD_reset();	// Reseteamos el LCD
  LCD_init();	// e inicializamos el display
}

//------------------------------------------------------
// void bucleMain(void)
//
// Descripci�n:
//   Funci�n del programa principal
//------------------------------------------------------
void bucleMain(void)
{
  char* mensaje = "HOLA";

  while(*mensaje){		// Imprime "HOLA" en el display
    LCD_dato(*mensaje++); 	// car�cter a car�cter
    retardo(RET_1S);		// Mantenemos el mensaje 1 segundo
  }

  LCD_inst(CLR_DISP);		// Limpiamos display
  LCD_inst(LIN_1LCD);		// Movemos el cursor a la 1� l�nea
  retardo(RET_1S);		// Esperamos otro segundo
}

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
