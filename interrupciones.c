#include "calculos.h" //Funciones llamadas en atencion a la interrupcion
//TODO include

#ifndef DATOS

#define V_BASE 0x40   //Direccion inicio (base) de vector interrupciones
#define DIR_VTMR0 4*(V_BASE+5)	//Direccion del vector de timer0
#define FREC_INT 4000	//Frecuencia de interrupcion periodica
#define PREESCALADO 2
#define CNT_INIT1 MCF_CLK/(FREC_INT*PREESCALADO*16) //TRR, valor de carga en el temporizador

#if CNT_INIT1>0xFFFF
#error PRESCALADO demasiado pequeño para la frecuencia pedida(CNT_INIT1>0xFFFF)
#endif

#define BORRA_REF 0x0002	//TODO que es esto?


#endif



void __attribute__ ((interrupt_handler)) isr_timer1(void){
	calculaModuloDFT(ADC_dato());
}


//------------------------------------------------------
// void __init(void)
//
// Descripción:
//   Función por defecto de inicialización del sistema
//------------------------------------------------------
void configModo1(void)
{
  // Fija comienzo de vectores de interrupción en V_BASE.
  mbar_writeByte(MCFSIM_PIVR, V_BASE);
  // Escribimos la dirección de la función para TMR0
  ACCESO_A_MEMORIA_LONG(DIR_VTMR1) = (ULONG)isr_timer1;
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