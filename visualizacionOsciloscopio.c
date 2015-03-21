void visualizacion_ociloscopio(int[] *puntero){
	int i;
	for (i = 0; i < NUM_FREC_MUESTREADAS; i++){
		DAC_dato(*(puntero+i));
		sleep(T_REFRESCO/NUM_FREC_MUESTREADAS);
	}
}