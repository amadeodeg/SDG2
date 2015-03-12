#include "m5272.h"
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



void __attribute__ ((interrupt_handler)) interr_periodica(void){
	calculaModuloDFT(ADC_dato());
}
