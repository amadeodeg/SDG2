#ifndef M5272LCD_H
#define M5272LCD_H

#include "m5272lib.h"

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

void LCD_write(UWORD dato, LCD_TIPO tipo);
void LCD_init();
void LCD_reset();

void LCD_write_s(char* s);

#endif
