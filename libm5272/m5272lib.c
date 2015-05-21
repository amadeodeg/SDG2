#include "m5272.h"

// Desahabilita las interrupciones
//void cli() __asm__ __volatile__ ( "move.w %%sr, %%d0 \n\t ori.l #0x0700,%%d0 \n\t move.w %%d0, %%sr \n\t" : : : "d0", "memory");

// Habilita las interrupciones
//void sti() asm volatile ( "move.w %%sr, %%d0 \n\t andi.l #0xF8FF,%%d0 \n\t move.w %%d0, %%sr \n\t" : : : "d0", "memory");