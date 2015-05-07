#include "m5272adc_dac.h"
#include "m5272gpio.h"
#include "teclado_matricial.h"
#include "interrupciones.h"
#include "calculos.h"
#include "mytime.h"
#include "m5272lcd.h"
#include "m5272lib.h"
#include <time.h>
#include <stdint.h>

#define DEBUG 1
#define MODO_1 1
#define PIN_RAMPA 16 //PIN 4



void startModo1(uint16_t puertoS){
	while(1){
		//struct timespec t1, t2;
		int i;
		
		struct timespec ts;

		struct timespec timePulse= {0, 1000000};;

		int ms = T_PANTALLA/NUM_FREC_MUESTREADAS*100;
		

		//current_utc_time(&t1);
		for (i = 0; i < NUM_FREC_MUESTREADAS; i++){
			if (DEBUG) printf("Frec: %d Dato: %d\n", i, mod2esc(getPmodFrecTot()+i));
			DAC_dato(mod2esc(getPmodFrecTot()+i));

			ts.tv_sec = ms / 1000;
			ts.tv_nsec = (ms % 1000) * 1000000;
			nanosleep(&ts, NULL);
		}
		//current_utc_time(&t2);
		//printf("%f\n", MIL_MILLONES * (t2.tv_sec - t1.tv_sec) + t2.tv_nsec - t1.tv_nsec);
		//reset bit inico rampa
		

		set16_puertoS(puertoS=(puertoS | 0x0010));  //bit 4 a uno el resto como estaba
		nanosleep(&timePulse,NULL);
		set16_puertoS(puertoS=(puertoS & 0xFFDF)); //bit 4 a 0 resto como estaba

	}
}

void configMinima(){
	//DAC_ADC_init();
	if(DEBUG) printf("DAC configurado\n");
	LCD_init();
	if(DEBUG) printf("LCD configurado\n");
	
}


int main(int argc, char const *argv[])
{
	uint16_t puertoS;
	int teclaModo;
	struct timespec t1 = {5, 0};
	if(DEBUG) printf("Empieza el programa\n");
	LCD_init(); //quitrar
	LCD_write_s("Modo"); //quitar
	configMinima();
	puertoS = 32; // LED 5
	set16_puertoS(puertoS);
	nanosleep(&t1,NULL);

	if (DEBUG) printf("ConfigMinima\n");
	LCD_write_s("Modo");
	teclaModo = get_teclado();
	if (DEBUG) printf("tecla: %d\n", teclaModo);

	switch(teclaModo){
		
	case MODO_1:
		//configModo1();
		if (DEBUG) printf("Modo1 configurado\n");
		startModo1(puertoS);
		if (DEBUG) printf("Modo1 empezado \n");

		break;

	default:
		//configModo1();
		if (DEBUG) printf("Modo1 configurado\n");
		startModo1(puertoS);
		if (DEBUG) printf("Modo1 empezado \n");
		break;
	}



	//visualizacion_ociloscopio();
	return 0;
}
