#include <stdio.h>
#include "m5272lcd.h"

//Escribe un caracter por pantalla.
void LCD_write(UWORD dato, LCD_TIPO tipo)
{
	printf("%c\n", (char)dato);
}

//Para mantener compatibilidad en simulacion.
void LCD_init()
{
}

//Para mantener compatibilidad en simulacion.
void LCD_reset()
{
}

//Escribe un string por pantalla.
void LCD_write_s(char* s)
{
	printf("%s\n", s);
}