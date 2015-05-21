//------------------------------------------------------------------------------
// m5272lcd.c
//
//   Funciones de configuraci�n y control de un LCD UC-12202-A SAMSUNG 
//   conectado a la plataforma de desarrollo ENT2004CF
//
// Autor: Javier Guill�n �lvarez
//------------------------------------------------------------------------------
#include "m5272lcd.h"
#include <unistd.h>
#include <time.h>

void set16_puertoS (UWORD valor);

//------------------------------------------------------
// void LCD_write(UWORD dato, LCD_TIPO tipo)
//
// Descripci�n:
//   Funci�n para escribir en el LCD
//
// Par�metros:
//   char dato
//     instrucci�n o car�cter a escribir en el display
//   LCD_TIPO tipo
//     LCD_CHAR si dato es un car�cter a escribir
//     LCD_INST si dato es una instrucci�n para el LCD
//------------------------------------------------------
void LCD_write(UWORD dato, LCD_TIPO tipo) __attribute__((weak));
void LCD_write(UWORD dato, LCD_TIPO tipo)
{
  cli();
  if(tipo == LCD_CHAR){
    dato = dato << 8;				// El dato debe estar en los 8 bits m�s significativos
  }
  set16_puertoS(dato | tipo | BIT_ENABLE);	// Enable + dato: Activamos LCD e indicamos el tipo de dato
  usleep(RET_3MS);
  set16_puertoS(dato | tipo);			// Disable: carga el dato en el LCD
  usleep(RET_3MS);
  sti();
}

//--------------------------------------
// void LCD_init()
//
// Descripci�n:
//   Funci�n de inicializaci�n del LCD
//--------------------------------------
void LCD_init()
{
  LCD_inst(FS_CONF8);	// Function Set: 8bits, 2l�neas, 5x7puntos
  LCD_inst(CLR_DISP);	// Clear Display 
  LCD_inst(MODE_SET);	// Autoincremento del cursor y sin desplazamiento (shift)
  LCD_inst(CD_ON);	// Activa el display, el cursor y el parpadeo
}

//--------------------------------------
// void LCD_reset()
//
// Descripci�n:
//   Funci�n de inicializaci�n del LCD
//--------------------------------------
void LCD_reset()
{
  int i;
  for(i = 0; i < 3; i++){	// Se repite 3 veces,
    LCD_inst(FS_8BITS);		//   Instrucci�n para funcionamiento en 8 bits
    usleep(RET_15MS);		//   Hay que esperar m�s de 4.1ms
  }
  usleep(RET_15MS);
}




//Escribe un array en el LCD.

void 
LCD_write_s(char* s)
{
  while(*s){
    LCD_dato((UWORD)*s++);
    usleep(RET_15MS);
  }
}
