#include <stdlib.h>
#include <errno.h>



#define PATH_IN "ADC_in.txt"
#define PATH_OUT "DAC_out.txt"

FILE *in;
FILE *out;

void DAC_ADC_init(){
	in=fopen(PATH_IN,"r");
	out=fopen(PATH_OUT,"r");
}

void DAC_dato(int dato){
	if(out==NULL){
		perror("error: intento escribir en un fichero cerrado.");
		return;
	}
	fprintf(out, "%d\n", dato);
}

int ADC_dato(){
	int dato;
	if(in==NULL){
		perror("error: intento leer en un fichero cerrado.");
		return;
	}
	fscanf(in, "%d", &dato);
	return dato;
}