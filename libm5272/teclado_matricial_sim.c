#include <stdio.h>
#include <math.h>

//Devuelve un solo caracter introducido por consola.
int 
get_tecla(void)
{
	int tecla;
	tecla = getchar();
	return tecla;
}

//Devuelve un entero introducido por consola al pulsar enter.
int 
get_numero_teclado(void)
{
	int numero;
	scanf("%d", &numero);
  	return numero;
}