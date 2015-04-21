#include "megiddo.h"
#include "m5272lcd.h"
#include <stdio.h>
#include <string.h>
#define NDEBUG 1

static char lcd_linea[40];
static volatile char* lcd_ptr;

#ifndef NDEBUG
void LCD_write(UWORD dato, LCD_TIPO tipo)
{
  static int row = 0;
  static int column = 80-13;

  if (tipo == LCD_CHAR) {
    cli();
    printf ("\e7\e[%d;%df\e[1m%c\e8", row, column, dato);
    fflush (stdout);
    sti();
    ++column;
    return;
  }

  switch (dato) {
  case LIN_1LCD:
    row = 0;
    column = 80-13;
    break;
  }
}
#endif

static
void lcd_char (void) 
{
  if (lcd_ptr && *lcd_ptr) {
    LCD_dato(*lcd_ptr++);
    tareaTemporizada (10, lcd_char);
  }
}

void lcd_print (const char* txt)
{
  strncpy (lcd_linea, txt, 40);
  lcd_linea[12] = '\0';
  lcd_ptr = lcd_linea;
  LCD_inst(LIN_1LCD);
  tareaTemporizada (10, lcd_char);
}

void sacarLCD (void)
{
  char msg[40];
  int jug = getJugadorActual();
  struct jugador_t* j = getJugador (jug);
  snprintf (msg, 40, "%c: P=%d T=%d  ", j->rep, j->contPuntos, j->tiempo);
  lcd_print (msg);
  tareaTemporizada (1000, sacarLCD);
}

void initLCD (void)
{
  LCD_reset ();
  LCD_init ();
  lcd_print ("* MEGIDDO *");
}
