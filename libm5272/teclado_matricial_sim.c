#include <stdio.h>
#include <math.h>

int get_tecla(void){
	int tecla;
	tecla = getchar();
	return tecla;
}

int get_numero_teclado(void){
	int numero;
	scanf("%d", &numero);
  	return numero;
}