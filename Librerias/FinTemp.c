//------------------------------------------------------------------------------
// FinTemp_GNU.c
//
//   Ejemplo para aprender el manejo de interrupciones temporizadas
//   y fines de temporización mediante un temporizador con el sistema
//   ENT2004CF.
//
// Autores: Ricardo de Córdoba, Juan Manuel Montero y Rubén San Segundo
// Adaptado a C por: Javier Guillén Álvarez
//------------------------------------------------------------------------------
#include "m5272.h"
#include "m5272lib.c"

#define V_BASE 0x40				  // Dirección de inicio de los vectores de interrupción
#define DIR_VTMR0 4*(V_BASE+5)			  // Dirección del vector de TMR0
#define DIR_VTMR1 4*(V_BASE+6)			  // Dirección del vector de TMR1
#define PERIODO_INTERR 2			  // Periodo de interrupción de TMR1
#define CNT_INT1 MCF_CLK*PERIODO_INTERR/(0x84*16) // Valor de precarga del temporizador de interrupciones TRR1
#define BORRA_CAP 0x0001			  // Valor de borrado de interr. pendientes de tout1 para TER1
#define BORRA_REF 0x0002			  // Valor de borrado de interr. pendientes de tout1 para TER1

volatile BOOL cap_recibida; // Varible declarada volátil porque se utiliza en el programa principal
			    // y es modificada por las funciones de atención a la interrupción.

//------------------------------------------------------
// void rutina_tout0(void)
//
// Descripción:
//   Función de atención a la interrupción para TIMER0
//------------------------------------------------------
void rutina_tout0(void)
{
  mbar_writeShort(MCFSIM_TER0,BORRA_CAP); 	// Reset del bit de captura
  cap_recibida = TRUE;
}

//------------------------------------------------------
// void rutina_tout1(void)
//
// Descripción:
//   Función de atención a la interrupción para TIMER1
//------------------------------------------------------
void rutina_tout1(void)
{
  output("HE DETECTADO UN FLANCO DE SUBIDA\r\n");
  cap_recibida = FALSE;
  mbar_writeShort(MCFSIM_TER1,BORRA_REF); // Reset del bit de fin de cuenta
}

//------------------------------------------------------
// void __init(void)
//
// Descripción:
//   Función por defecto de inicialización del sistema
//------------------------------------------------------
void __init(void)
{
  mbar_writeByte(MCFSIM_PIVR,V_BASE);		// Fija comienzo de vectores de interrupción en V_BASE.
  ACCESO_A_MEMORIA_LONG(DIR_VTMR0)= (ULONG)_prep_TOUT0; // Vector de interrupción para tout0
  ACCESO_A_MEMORIA_LONG(DIR_VTMR1)= (ULONG)_prep_TOUT1; // Vector de interrupción para tout1
  output("COMIENZA EL PROGRAMA\r\n");
  mbar_writeShort(MCFSIM_TMR0, 0x4F45);		// TMR0: PS=0x50-1 CE=01(Flanco Subida) OM=0 ORI=0 FRR=0 CLK=10 RST=1
  mbar_writeShort(MCFSIM_TMR1, 0x8334);		// TMR1: PS=0x84-1 CE=00(No captura)    OM=1 ORI=1 FRR=0 CLK=10 RST=0 (Todavía no cuenta)
  mbar_writeLong(MCFSIM_ICR1, 0x8888AC88);	// Marca la interrupción del TIMER0 y del TIMER1
						// como no pendiente y de prioridades 2 y 4 respectivamente.
  cap_recibida = FALSE;						
  sti();
}

//------------------------------------------------------
// void reInit(void)
//
// Descripción:
//   Reinicializa la interrupción TMR1
//------------------------------------------------------
void reInit(void)
{
  mbar_writeShort(MCFSIM_TCN1, 0x0000);		// TCN1 Pone a cero el contador de TIMER1
  mbar_writeShort(MCFSIM_TRR1, CNT_INT1);	// TRR1 Valor de precarga del temporizador
  mbar_writeShort(MCFSIM_TMR1, 0x8334);		// TMR1 PS=0x84-1 CE=00(No captura) OM=1 ORI=1 FRR=0 CLK=10 RST=0 (Todavía no cuenta)
  bsetl(16, MCF_MBAR + MCFSIM_TMR1);		// Arranca el temporizador TIMER1
}

//------------------------------------------------------
// void bucleMain(void)
//
// Descripción:
//   Función del programa principal
//------------------------------------------------------
void bucleMain(void)
{
  // Espera a que TMR0 detecte un flanco de subida
  while(!cap_recibida);

  // Inicia el temporizador de 2 segundos
  reInit();
  
  // Espera hasta que transcurran los 2 segundos e imprime
  // el mensaje de flanco detectado
  while(cap_recibida);

  // Detiene TMR1
  cli();					// Inhabilita las interrupciones
  bclrl(16,MCF_MBAR + MCFSIM_TMR1); 		// TMR1 Para el TIMER1
  sti();					// Vuelve a habilitar las interrupciones
}

//---------------------------------------------------------
// Definición de rutinas de atención a la interrupción
// Es necesario definirlas aunque estén vacías
void rutina_int1(void){}
void rutina_int2(void){}
void rutina_int3(void){}
void rutina_int4(void){}
void rutina_tout2(void){}
void rutina_tout3(void){}
