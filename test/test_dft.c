#include "calculos.h"
#include <stdio.h>
#define PATH_IN "../sim/ADC_in.txt"
#define PATH_OUT "../sim/DAC_out.txt"


int main(int argc, char const *argv[])
{
	int veces;
	FILE *in;
	FILE *out;
	in=fopen(PATH_IN,"r");
	out=fopen(PATH_OUT,"w");

	for(veces=0; veces<1; veces++){
		int i, j;
		int* modFrecTot;
		for(i=0; i<80; i++){
			int datoLeido;
			fscanf(in, "%d", &datoLeido);
			calculaModuloDFT(datoLeido);
		}
		modFrecTot = getPmodFrecTot();
		for(j=0; j<20; j++){
			fprintf(out, "%d\n", mod2esc((modFrecTot+j)));
		}
		fprintf(out, "---\n");

	}

	return 0;
}