#include "./lib/m5272ADC_DAC.h"

void startModo1(void){
	while(1){
		int i;
		for (i = 0; i < NUM_FREC_MUESTREADAS; i++){
			DAC_dato(mod2esc(modFrecTot));
			sleep(T_PANTALLA/NUM_FREC_MUESTREADAS)
		}
	}
}

void configMinima(){

}

int main(int argc, char const *argv[])
{
	configMinima();

	char teclaModo = leeTecladoMatricial();
	switch(teclaModo){
		
		case MODO_1:
		configModo1();
		startModo1();
		break;

		default:
		break;
	}



	visualizacion_ociloscopio();
	return 0;
}