#include "calculos.h" //Funciones llamadas en atencion a la interrupcion
#include "m5272adc_dac.h"
#include "m5272.h"
#include "m5272lib.h"
#include <stdint.h>
#include "m5272gpio.h"
//TODO include

#ifndef DATOS

#define DIR_VTMR1 4*(V_BASE+6)
//#define CNT_INT1 MCF_CLK/(FREC_INT*0x50*16)

#define V_BASE 0x40   //Direccion inicio (base) de vector interrupciones
#define DIR_VTMR0 4*(V_BASE+5)	//Direccion del vector de timer0
#define FREC_INT 4000	//Frecuencia de interrupcion periodica
#define PRESCALADO 2
#define CNT_INT1 MCF_CLK/(FREC_INT*PRESCALADO*16) //TRR, valor de carga en el temporizador

#if CNT_INIT1>0xFFFF
#error PRESCALADO demasiado pequeño para la frecuencia pedida(CNT_INIT1>0xFFFF)
#endif

#define BORRA_REF 0x0002	//TODO que es esto?


#endif

static int bit = 0;
void __attribute__ ((interrupt_handler)) isr_timer1(void){
  mbar_writeShort(MCFSIM_TER0,BORRA_REF);
  //set_gpio(4, 0);
	calculaModuloDFT2(ADC_dato());
  set16_puertoS((get16_puertoS() & ~(1 << 5)) | (bit << 5));
  bit = !bit;
}


//------------------------------------------------------
// void __init(void)
//
// Descripción:
//   Función por defecto de inicialización del sistema
//------------------------------------------------------
void configInt4k(void)
{
  // Fija comienzo de vectores de interrupción en V_BASE.
  mbar_writeByte(MCFSIM_PIVR, V_BASE);
  // Escribimos la dirección de la función para TMR0
  ACCESO_A_MEMORIA_LONG(DIR_VTMR0) = (ULONG)isr_timer1;
  // TMR0: PS=0x50-1 CE=00 OM=1 ORI=1 FRR=1 CLK=10 RST=1
  mbar_writeShort(MCFSIM_TMR0, (PRESCALADO-1)<<8|0x3D); //0x4F3D);
  // Ponemos a 0 el contador del TIMER0
  mbar_writeShort(MCFSIM_TCN0, 0x0000);
  // Fijamos la cuenta final del contador
  mbar_writeShort(MCFSIM_TRR0, CNT_INT1);
  // Marca la interrupción del TIMER1 como no pendiente
  mbar_writeLong(MCFSIM_ICR1, 0x8888C888);
  sti();
}