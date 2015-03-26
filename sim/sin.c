#include <math.h>
#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include <unistd.h>

#define PASO 0.01 //Salto entre muestras. Cuanto mas pequeño, mayor resolucion.
#define PI 3.14159265359
#define N_MUESTRAS ceil(2*PI/PASO) //Longitud del fichero.
#define F_OUT "ADC_in.txt" //Fichero de salida. Pensado para que el ejecutable este en la carpeta de pruebas y cree el fichero con el seno en la misma carpeta.
#define PREESCALADO 819

int main(int argc, char const *argv[])
{
	FILE *fich; 
	int i;
	fich = fopen(F_OUT, "w+");
	for (i = 0; i<N_MUESTRAS; i++) {
		if (fich == NULL) {
			perror("Error en la apertura\n");
			printf("errno = %d.\n", errno);
		}
		fprintf(fich, "%f\n",PREESCALADO*sin(i*(atoi(argv[1]))*PASO));
	}
	fclose(fich);
	return 0;
}

