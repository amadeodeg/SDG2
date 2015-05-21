#ifndef CALCULOS_H
#define CALCULOS_H

#define NUM_MUESTRAS_PERIODO_10HZ 400 //Tamaño del array guardado.
#define NUM_FREC_MUESTREADAS 20 //Numero de frecuencias para las que se calcula la DFT
#define T_PANTALLA 40 //Tiempo en ms de refresco de pantalla

void calculaModuloDFT(int muestraADC);
int mod2esc(int *modulo);
int calculaSeno(int frecuencia, int muestra);
void creaArrayFrecuencias(int inicial, int final);
int* getPmodFrecTot(void);
void configPasoFrecPointers();
void calculaModuloDFT2(int muestraADC);

#endif