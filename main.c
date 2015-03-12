void visualizacion_ociloscopio(void){
	while(1){
		int i;
		for (i = 0; i < NUM_FREC_MUESTREADAS; i++){
			DAC_dato(mod2esc(modFrecTot));
			sleep(T_PANTALLA/NUM_FREC_MUESTREADAS)
		}
	}
}

int main(int argc, char const *argv[])
{
	visualizacion_ociloscopio();
	return 0;
}