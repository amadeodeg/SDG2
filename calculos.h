#ifndef CALCULOS_H
#define CALCULOS_H

#define NUM_MUESTRAS_PERIODO_10HZ 400
#define NUM_FREC_MUESTREADAS 20
#define T_PANTALLA 40

void calculaModuloDFT(int muestraADC);
int mod2esc(int *modulo);
int calculaSeno(int frecuencia, int muestra);

void creaArrayFrecuencias(int inicial, int final);

int* getPmodFrecTot(void);

void configPasoFrecPointers();
void calculaModuloDFT2(int muestraADC);

extern int modFrecTot[NUM_FREC_MUESTREADAS]; 

#endif