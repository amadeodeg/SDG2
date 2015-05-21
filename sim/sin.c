#include <math.h>
#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include <unistd.h>

#define F_OUT "ADC_in.txt"

#define PERIODO 0.00025
#define TIEMPO 1
#define N_MUESTRAS ceil(TIEMPO/PERIODO)
#define PI 3.14159265359
#define PREESCALADO 819

// Calcula la suma de los senos de las frecuencias que se le pasan como argumento
// y escribe los resultados en el fichero de salida F_OUT. Se escala para que la salida
// sea como el ADC de antares y si hay varios senos se divide entre el numero de senos
// para evitar sumas en fase que superen 819.

int main(int argc, char const *argv[])
{
	FILE *fich;
	int i;
	fich = fopen(F_OUT,"w+");
	for (i = 0; i < N_MUESTRAS; i++){
		 int j;
		 float valor=0;
		for (j = 1; j < argc; j++){
		 	valor+=sin(2*PI*atoi(argv[j])*i*PERIODO);
		 }
		 valor/=(argc-1);
		 if (fich == NULL) {
		 	perror("Error en la apertura\n");
		 	printf("errno = %d.\n", errno);
		 	return -1;
		 } 
		 fprintf(fich, "%d\n", (int)(valor*PREESCALADO));
	}
	fclose(fich);
	return 0;
}

