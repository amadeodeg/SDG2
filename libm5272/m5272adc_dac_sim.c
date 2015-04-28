#include <stdlib.h>
#include <stdio.h>
#include <errno.h>


#define PATH_IN "./sim/ADC_in.txt"
#define PATH_OUT "./sim/DAC_out.txt"

#define DEBUG 1

FILE *in;
FILE *out;

void DAC_ADC_init(){
	in=fopen(PATH_IN,"r");
	out=fopen(PATH_OUT,"w");
}

void DAC_dato(int dato){

	if(out==NULL){
		perror("error: intento escribir en un fichero cerrado.");
		return;
	}
	fprintf(out, "%d\n", dato);
	if (DEBUG) printf("Escrito: %d\n", dato);
	fflush(out);
}

int ADC_dato(){
	int dato;
	if(in==NULL){
		perror("error: intento leer en un fichero cerrado.");
		return -1;
	}
	fscanf(in, "%d", &dato);
	return dato;
}
