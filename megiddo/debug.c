#ifndef NDEBUG
#include <stdio.h>
#include "m5272lib.h"

extern char __stack[];

void debug_temporizador(void);
void debug_jugador(void);

void dump_stack(int i, char* stack_ptr)
{
  char* frame = *(char**) stack_ptr;
  char* pc = *(char**) (stack_ptr + 4);
  stack_ptr += 8;

  if (!frame || !pc)
    return;
  printf (" #%d 0x%08p (frame = 8+%d bytes)\n",
	  i, pc, frame - stack_ptr - 8);
  dump_stack (i + 1, frame);
}

void debug (tecla)
{
  static int musica = 0;
  cli();
  switch (tecla) {
  case '1':
    debug_temporizador();
    break;
  case '2':
    debug_jugador();
    break;
  case '3':
    {
      char* stack_ptr;
      asm volatile( "movel %%sp, %0\n\t"
		    : "=d" (stack_ptr)
		    :
		    : "sp");
      printf ("stack size: %ld bytes\n", __stack - stack_ptr);
      dump_stack (0, stack_ptr + 4);
    }
    break;
  case '4':
    musica = !musica;
    printf ("Musica %d\n", musica);
    if (musica) { 
      musica_on(); 
    } 
    else { 
      musica_off(); 
    }
    break;
  }
  sti();
}
  
#endif
