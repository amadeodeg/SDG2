#include "m5272.h"
#include "megiddo.h"

#define V_BASE 0x40				  // Dirección de inicio de los vectores de interrupción
#define DIR_VTMR1 4*(V_BASE+6)			  // Dirección del vector de TMR1

#define FREC_INT 100				  // Frec. de interr. TMR1 = 100 Hz (cada 10ms)
#define CNT_INT1 MCF_CLK/(FREC_INT*0x50*16)	  // Valor de precarga del temporizador de interrupciones TRR1
#define BORRA_REF 0x0002			  // Valor de borrado de interr. pendientes de tout1 para TER1

struct tarea {
  tarea_func_t f;
  ULONG plazo;
};
static volatile struct tarea t[10];
static volatile ULONG tiempo;

ULONG getTiempo (void)
{
  return tiempo;
}

void tareaTemporizada (int ms, tarea_func_t f)
{
  int i;
  for (i = 0; i < 10; ++i) {
    if (! t[i].f) {
      t[i].f = f;
      t[i].plazo = ms;
      return;
    }
  }
}

void eliminarTareaTemporizada (tarea_func_t f)
{
  int i;
  for (i = 0; i < 10; ++i) {
    if (t[i].f == f) {
      t[i].f = 0;
      return;
    }
  }
}


static volatile int done;

static void wait_done (void)
{
  done = 1;
}

void ms_sleep (int ms)
{
  done = 0;
  tareaTemporizada (ms, wait_done);
  while (!done);
}

//------------------------------------------------------
// void rutina_tout0(void)
//
// Descripción:
//   Función de atención a la interrupción para TIMER0
//------------------------------------------------------
void __attribute__((interrupt_handler)) isr_timer1 (void)
{
  int i;
  mbar_writeShort (MCFSIM_TER1, BORRA_REF); 	// Reset del bit de fin de cuenta

  tiempo += 1000 / FREC_INT;
  if (pausado())
    return;
  for (i = 0; i < 10; ++i) {
    if (t[i].f) {
      t[i].plazo -= 1000 / FREC_INT;
      if (t[i].plazo <= 0) {
	tarea_func_t f = t[i].f;
        t[i].f = 0;
        f();
      }
    }
  }
}

//------------------------------------------------------
// void __init(void)
//
// Descripción:
//   Función por defecto de inicialización del sistema
//------------------------------------------------------
void initTemporizador(void)
{
  // Fija comienzo de vectores de interrupción en V_BASE.
  mbar_writeByte(MCFSIM_PIVR, V_BASE);
  // Escribimos la dirección de la función para TMR0
  ACCESO_A_MEMORIA_LONG(DIR_VTMR1)= (ULONG)isr_timer1;
  // TMR0: PS=0x50-1 CE=00 OM=1 ORI=1 FRR=1 CLK=10 RST=1
  mbar_writeShort(MCFSIM_TMR1, 0x4F3D);
  // Ponemos a 0 el contador del TIMER0
  mbar_writeShort(MCFSIM_TCN1, 0x0000);
  // Fijamos la cuenta final del contador
  mbar_writeShort(MCFSIM_TRR1, CNT_INT1);
  // Marca la interrupción del TIMER1 como no pendiente
  mbar_writeLong(MCFSIM_ICR1, 0x88888F88);
  sti();
}

#ifndef NDEBUG
#include <stdio.h>

void
debug_temporizador (void)
{
  int i;

  printf ("tiempo = %lu\n", tiempo);
  for (i = 0; i < 10; ++i) {
    if (t[i].f) {
      printf ("  %d: tarea = 0x%p, plazo = %lu\n", i, t[i].f, t[i].plazo);
    }
  }
}

#endif
