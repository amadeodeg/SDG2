#include <stdio.h>
#include "m5272lcd.h"

void LCD_write(UWORD dato, LCD_TIPO tipo){
	printf("%c\n", (char)dato);
}
void LCD_init(){

}
void LCD_reset(){

}
void LCD_write_s(char* s){
	printf("%s\n", s);
}