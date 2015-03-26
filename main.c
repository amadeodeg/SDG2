#include "./lib/m5272adc_dac.h"
#include "./lib/teclado_matricial.h"
#include "./lib/interrupciones.h"
#include "./lib/calculos.h"
#include <time.h>

#define MODO_1 1
void startModo1(void){
	while(1){
		int i;
		struct timespec ts;
		int ms = T_PANTALLA/NUM_FREC_MUESTREADAS;
		for (i = 0; i < NUM_FREC_MUESTREADAS; i++){
			DAC_dato(mod2esc(&modFrecTot[i]));
			ts.tv_sec = ms / 1000;
			ts.tv_nsec = (ms % 1000) * 1000000;
			nanosleep(&ts, NULL);
		}
	}
}

void configMinima(){
	DAC_ADC_init();
}


int main(int argc, char const *argv[])
{
	int teclaModo;
	
	configMinima();

	teclaModo = get_teclado();
	switch(teclaModo){
		
		case MODO_1:
		configModo1();
		startModo1();

		break;

		default:
		break;
	}



	//visualizacion_ociloscopio();
	return 0;
}