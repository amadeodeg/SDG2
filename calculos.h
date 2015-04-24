#ifndef CALCULOS_H
#define CALCULOS_H

#define NUM_FREC_MUESTREADAS 20
#define T_PANTALLA 40

void calculaModuloDFT(int muestraADC);
int mod2esc(int *modulo);

int* getPmodFrecTot(void);

extern int modFrecTot[NUM_FREC_MUESTREADAS];

#endif