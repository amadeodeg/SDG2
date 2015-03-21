#include "./lib/m5272adc_dac_sim.h"
#include "./lib/teclado_matricial_sim.h"
#define MODO_1 1
// void startModo1(void){
// 	while(1){
// 		int i;
// 		for (i = 0; i < NUM_FREC_MUESTREADAS; i++){
// 			DAC_dato(mod2esc(modFrecTot));
// 			nanosleep(T_PANTALLA/NUM_FREC_MUESTREADAS)
// 		}
// 	}
// }

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
		//configModo1();
		//startModo1();

		break;

		default:
		break;
	}



	//visualizacion_ociloscopio();
	return 0;
}