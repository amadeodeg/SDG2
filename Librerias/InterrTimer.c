//------------------------------------------------------------------------------
// InterrTimer_GNU.c
//
//   Ejemplo para aprender el manejo de interrupciones temporizadas
//   y fines de temporizaci�n mediante un temporizador con el sistema
//   ENT2004CF.
//
// Autores: Juan Manuel Montero, Rub�n San Segundo y Ricardo de C�rdoba
// Adaptado a C por: Javier Guill�n �lvarez
//------------------------------------------------------------------------------
#include "m5272.h"
#include "m5272lib.c"

#define V_BASE 0x40				  // Direcci�n de inicio de los vectores de interrupci�n
#define DIR_VTMR0 4*(V_BASE+5)			  // Direcci�n del vector de TMR0

#define FREC_INT 1000				  // Frec. de interr. TMR0 = 1000 Hz (cada 1ms)
#define PRESCALADO 2
#define CNT_INT1 MCF_CLK/(FREC_INT*PRESCALADO*16)	  // Valor de precarga del temporizador de interrupciones TRR0
#if CNT_INT1>0xFFFF
#error PRESCALADO demasiado peque�o para esa frecuencia (CNT_INT1>0xFFFF)
#endif
#define BORRA_REF 0x0002			  // Valor de borrado de interr. pendientes de tout1 para TER0

volatile ULONG cont_retardo;

//------------------------------------------------------
// void rutina_tout0(void)
//
// Descripci�n:
//   Funci�n de atenci�n a la interrupci�n para TIMER0
//------------------------------------------------------
void rutina_tout0(void)
{
  mbar_writeShort(MCFSIM_TER0,BORRA_REF); 	// Reset del bit de fin de cuenta
  if(cont_retardo > 0){
    cont_retardo--;				// Decrementa el contador cada 1ms
  }

}

//------------------------------------------------------
// void __init(void)
//
// Descripci�n:
//   Funci�n por defecto de inicializaci�n del sistema
//------------------------------------------------------
void __init(void)
{
  mbar_writeByte(MCFSIM_PIVR,V_BASE);			// Fija comienzo de vectores de interrupci�n en V_BASE.
  ACCESO_A_MEMORIA_LONG(DIR_VTMR0)= (ULONG)_prep_TOUT0; // Escribimos la direcci�n de la funci�n para TMR0
  output("COMIENZA EL PROGRAMA\r\n");
  mbar_writeShort(MCFSIM_TMR0, (PRESCALADO-1)<<8|0x3D);		// TMR0: PS=1-1=0 CE=00 OM=1 ORI=1 FRR=1 CLK=10 RST=1
  mbar_writeShort(MCFSIM_TCN0, 0x0000);		// Ponemos a 0 el contador del TIMER0
  mbar_writeShort(MCFSIM_TRR0, CNT_INT1);	// Fijamos la cuenta final del contador
  mbar_writeLong(MCFSIM_ICR1, 0x8888C888);	// Marca la interrupci�n del TIMER0 como no pendiente
						// y de nivel 4.
  cont_retardo = 0;
  sti();					// Habilitamos interrupciones
}

//------------------------------------------------------
// void sleep(ULONG milisegundos)
//
// Descripci�n:
//   Funci�n que introduce el retardo indicado en 
//   milisegundos.
//------------------------------------------------------
void sleep(ULONG milisegundos)
{
  cont_retardo = milisegundos;	// Inicializa el contador
  while(cont_retardo > 0);	// Espera a que llegua a cero
  return;
}

//------------------------------------------------------
// void bucleMain(void)
//
// Descripci�n:
//   Funci�n del programa principal
//------------------------------------------------------
void bucleMain(void)
{
  char* cad = "CADA SEGUNDO ESCRIBO UNA LETRA\r\n";

  while(*cad){
    sleep(1000);                // Introduce un retardo de 1 segundo
    outch(*cad++);              // Escribe una la siguiente letra de cadena
  }
}



//---------------------------------------------------------
// Definici�n de rutinas de atenci�n a la interrupci�n
// Es necesario definirlas aunque est�n vac�as
void rutina_int1(void){}
void rutina_int2(void){}
void rutina_int3(void){}
void rutina_int4(void){}
void rutina_tout1(void){}
void rutina_tout2(void){}
void rutina_tout3(void){}
