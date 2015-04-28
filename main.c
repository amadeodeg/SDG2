#include "m5272adc_dac.h"
#include "m5272gpio.h"
#include "teclado_matricial.h"
#include "interrupciones.h"
#include "calculos.h"
#include "mytime.h"
#include "m5272lcd.h"
#include <stdint.h>

#define DEBUG 1
#define MODO_1 1



void startModo1(void){
	while(1){
		struct timespec t1, t2;
		int i;
		uint16_t pin_rampa;
		struct timespec ts;
		int ms = T_PANTALLA/NUM_FREC_MUESTREADAS*100;
		pin_rampa = 1;
		current_utc_time(&t1);
		for (i = 0; i < NUM_FREC_MUESTREADAS; i++){
			if (DEBUG) printf("Frec: %d Dato: %d\n", i, mod2esc(getPmodFrecTot()+i));
			DAC_dato(mod2esc(getPmodFrecTot()+i));

			ts.tv_sec = ms / 1000;
			ts.tv_nsec = (ms % 1000) * 1000000;
			nanosleep(&ts, NULL);
		}
		current_utc_time(&t2);
		//printf("%f\n", MIL_MILLONES * (t2.tv_sec - t1.tv_sec) + t2.tv_nsec - t1.tv_nsec);
		//reset bit inico rampa
		set16_puertoS(pin_rampa);

	}
}

void configMinima(){
	DAC_ADC_init();
}


int main(int argc, char const *argv[])
{
	int teclaModo;
	configMinima();
	if (DEBUG) printf("ConfigMinima\n");
	LCD_write_s("Introduzca modo de funcionamiento:");
	teclaModo = get_teclado();
	if (DEBUG) printf("tecla: %d\n", teclaModo);

	switch(teclaModo){
		
	case MODO_1:
		configModo1();
		if (DEBUG) printf("Modo1 configurado\n");
		startModo1();
		if (DEBUG) printf("Modo1 empezado \n");

		break;

	default:
		break;
	}



	//visualizacion_ociloscopio();
	return 0;
}
