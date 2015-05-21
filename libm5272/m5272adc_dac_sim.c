#include <stdlib.h>
#include <stdio.h>
#include <errno.h>


#define PATH_IN "./sim/ADC_in.txt"
#define PATH_OUT "./sim/DAC_out.txt"

#define DEBUG 0

FILE *in;
FILE *out;

//Abre ficheros de datos.
void 
DAC_ADC_init ()
{
	in=fopen(PATH_IN,"r");
	out=fopen(PATH_OUT,"w");
}

//Escribe en el fichero de salida.
void 
DAC_dato (int dato)
{
	if (out==NULL)
	{
		perror("error: intento escribir en un fichero cerrado.");
		return;
	}
	fprintf(out, "%d\n", dato);
	if (DEBUG) 
	{
		printf("Escrito: %d\n", dato);
	}
	fflush(out);
}

//Lee del fichero de entrada
int 
ADC_dato ()
{
	int dato;
	if (in==NULL) 
	{
		perror("error: intento leer en un fichero cerrado.");
		return -1;
	}
	fscanf(in, "%d", &dato);
	return dato;
}
