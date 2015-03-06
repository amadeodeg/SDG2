//------------------------------------------------------------------------------
// LCD_GNU.c
//
//   Programa ejemplo para el manejo de un LCD.
//
// Autores: Juan Manuel Montero y Rubén San Segundo.
// Adaptado a C por: Javier Guillén Álvarez
//------------------------------------------------------------------------------
#include "m5272lib.c"
#include "m5272lcd.c"

//------------------------------------------------------
// void __init(void)
//
// Descripción:
//   Función por defecto de inicialización del sistema
//------------------------------------------------------
void __init(void)
{
  LCD_reset();	// Reseteamos el LCD
  LCD_init();	// e inicializamos el display
}

//------------------------------------------------------
// void bucleMain(void)
//
// Descripción:
//   Función del programa principal
//------------------------------------------------------
void bucleMain(void)
{
  char* mensaje = "HOLA";

  while(*mensaje){		// Imprime "HOLA" en el display
    LCD_dato(*mensaje++); 	// carácter a carácter
    retardo(RET_1S);		// Mantenemos el mensaje 1 segundo
  }

  LCD_inst(CLR_DISP);		// Limpiamos display
  LCD_inst(LIN_1LCD);		// Movemos el cursor a la 1ª línea
  retardo(RET_1S);		// Esperamos otro segundo
}

//---------------------------------------------------------
// Definición de rutinas de atención a la interrupción
// Es necesario definirlas aunque estén vacías
void rutina_int1(void){}
void rutina_int2(void){}
void rutina_int3(void){}
void rutina_int4(void){}
void rutina_tout0(void){}
void rutina_tout1(void){}
void rutina_tout2(void){}
void rutina_tout3(void){}
