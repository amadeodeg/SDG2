//------------------------------------------------------------------------------
// m5272lcd.c
//
//   Funciones de configuración y control de un LCD UC-12202-A SAMSUNG 
//   conectado a la plataforma de desarrollo ENT2004CF
//
// Autor: Javier Guillén Álvarez
//------------------------------------------------------------------------------
#include "m5272lcd.h"
#include <unistd.h>
#include <time.h>

void set16_puertoS (UWORD valor);

//------------------------------------------------------
// void LCD_write(UWORD dato, LCD_TIPO tipo)
//
// Descripción:
//   Función para escribir en el LCD
//
// Parámetros:
//   char dato
//     instrucción o carácter a escribir en el display
//   LCD_TIPO tipo
//     LCD_CHAR si dato es un carácter a escribir
//     LCD_INST si dato es una instrucción para el LCD
//------------------------------------------------------
void LCD_write(UWORD dato, LCD_TIPO tipo) __attribute__((weak));
void LCD_write(UWORD dato, LCD_TIPO tipo)
{
  cli();
  if(tipo == LCD_CHAR){
    dato = dato << 8;				// El dato debe estar en los 8 bits más significativos
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
// Descripción:
//   Función de inicialización del LCD
//--------------------------------------
void LCD_init()
{
  LCD_inst(FS_CONF8);	// Function Set: 8bits, 2líneas, 5x7puntos
  LCD_inst(CLR_DISP);	// Clear Display 
  LCD_inst(MODE_SET);	// Autoincremento del cursor y sin desplazamiento (shift)
  LCD_inst(CD_ON);	// Activa el display, el cursor y el parpadeo
}

//--------------------------------------
// void LCD_reset()
//
// Descripción:
//   Función de inicialización del LCD
//--------------------------------------
void LCD_reset()
{
  int i;
  for(i = 0; i < 3; i++){	// Se repite 3 veces,
    LCD_inst(FS_8BITS);		//   Instrucción para funcionamiento en 8 bits
    usleep(RET_15MS);		//   Hay que esperar más de 4.1ms
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
