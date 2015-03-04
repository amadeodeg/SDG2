//------------------------------------------------------------------------------
// m5272lcd.c
//
//   Funciones de configuración y control de un LCD UC-12202-A SAMSUNG 
//   conectado a la plataforma de desarrollo ENT2004CF
//
// Autor: Javier Guillén Álvarez
//------------------------------------------------------------------------------
#ifndef __M5272LCD_C__
#define __M5272LCD_C__

#include "m5272lib.c"
#include "m5272gpio.c"

//------------------------------------------------------------------
// TIPO:        LCD_TIPO
// DESCRIPCIÓN: sirve para indicar a LCD_write si la se le pasa
//		un carácter para imprimir o una instrucción
//------------------------------------------------------------------
typedef enum {LCD_CHAR = 0x40, LCD_INST = 0x00} LCD_TIPO;

#define CLR_DISP	0x0100		// Clear Display
#define LIN_1LCD	0x8000		// Set DRAM dir=0x00 (Inicio 1ª línea)
#define LIN_2LCD	0xC000		// Set DRAM dir=0x40 (Inicio 2ª línea)
#define FS_8BITS	0x3000		// Function Set para 8 bits
#define FS_CONF8	0x3800		// Function Set: 8bits, 2líneas, 5x7puntos
#define MODE_SET	0x0600		// Mode Set: autoincremento, no shift
#define CD_ON		0x0F00		// Display ON, Cursor ON, Parpadeo ON
#define BIT_ENABLE	0x0080

// MACROS PARA ABREVIAR LAS LLAMADAS A LCD_write
#define LCD_dato(dato) LCD_write(dato, LCD_CHAR)
#define LCD_inst(inst) LCD_write(inst, LCD_INST)

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
void LCD_write(UWORD dato, LCD_TIPO tipo)
{
  UWORD salida;
  if(tipo == LCD_CHAR){
    dato = dato << 8;				// El dato debe estar en los 8 bits más significativos
  }
  set16_puertoS(dato | tipo | BIT_ENABLE);	// Enable + dato: Activamos LCD e indicamos el tipo de dato
  retardo(RET_3MS);
  set16_puertoS(dato | tipo);			// Disable: carga el dato en el LCD
  retardo(RET_3MS);
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
  retardo(RET_15MS);		// Retardo inicial
  for(i = 0; i < 3; i++){	// Se repite 3 veces,
    LCD_inst(FS_8BITS);		//   Instrucción para funcionamiento en 8 bits
    retardo(RET_15MS);		//   Hay que esperar más de 4.1ms
  }
}

#endif