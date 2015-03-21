#include <math.h>
#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include <unistd.h>

#define PASO 0.01 //Salto entre muestras. Cuanto mas pequeño, mayor resolucion.
#define PI 3.14159265359
#define N_MUESTRAS ceil(2*PI/PASO) //Longitud del fichero.
#define F_OUT "ADC_in.txt" //Fichero de salida. Pensado para que el ejecutable este en la carpeta de pruebas y cree el fichero con el seno en la misma carpeta.

int main(int argc, char const *argv[])
{
	FILE *fich; 
	int i;
	fich = fopen(F_OUT, "w+");
	if (fich == NULL) {
		perror("Error en la apertura\n");
		printf("errno = %d.\n", errno);
	}
	for (i = 0; i<N_MUESTRAS; i++) {
		fprintf(fich, "%f\n", sin(i*(atoi(argv[1]))/100));
	}
	fclose(fich);
	return 0;
}