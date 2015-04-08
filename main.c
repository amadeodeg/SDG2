#include "./lib/m5272adc_dac.h"
#include "./lib/teclado_matricial.h"
#include "./lib/interrupciones.h"
#include "./lib/calculos.h"
#include <time.h>
#include <stdio.h>

#define DEBUG 1
#define MODO_1 1
void startModo1(void){
	while(1){
		int i;
		int pin_rampa;
		struct timespec ts;
		time_t last_execution_time;
		int ms = T_PANTALLA/NUM_FREC_MUESTREADAS;
		pin_rampa = 1;
		for (i = 0; i < NUM_FREC_MUESTREADAS; i++){

			if (DEBUG) {
				time_t current_execution_time;
				time_t resta;
				printf("frecuencia %2d: %4d\n", i, mod2esc(&modFrecTot[i]));
    			current_execution_time = time(NULL);
    			resta = current_execution_time - last_execution_time;
    			printf(ctime(&resta));
    			last_execution_time = current_execution_time;
			}

			DAC_dato(mod2esc(&modFrecTot[i]));

			ts.tv_sec = ms / 1000;
			ts.tv_nsec = (ms % 1000) * 1000000;
			nanosleep(&ts, NULL);
		}
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
	if (DEBUG) printf("teclaModo\n");

	configMinima();
	if (DEBUG) printf("ConfigMinima\n");

	teclaModo = get_teclado();
	if (DEBUG) printf("tecla: %d\n", teclaModo);

	switch(teclaModo){
		
		case MODO_1:
		if (DEBUG) printf("Modo1\n");
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