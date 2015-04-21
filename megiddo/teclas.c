#include <stdio.h>
#include "megiddo.h"

int main ()
{
  puts ("Pulsa teclas en el teclado matricial");
  while (1) {
    char c = teclado();
    putchar (c); fflush (0);
  }
}
