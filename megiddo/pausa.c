#include <stdio.h>
#include "megiddo.h"

static volatile int en_pausa = 0;

int pausado ()
{
  return en_pausa;
}

void set_pausado (int i)
{
  en_pausa = i;
}

void pausa ()
{
  puts("\nJuego pausado");
  en_pausa = 1;
  while (1) {
    int tecla = teclado();
    if (tecla == TECLA_PAUSA) {
      en_pausa = 0;
      puts("Fin de pausa");
      return;
    }
#ifndef NDEBUG
    debug (tecla);
#endif
  }
}
