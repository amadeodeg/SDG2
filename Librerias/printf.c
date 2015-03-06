/*
 * _printf.c
 *
 * cl�sica funci�n printf simplificada y adaptada al MCF5272
 *
 * Adaptado por Miguel Morales
 */
#include "stdarg.h"

#include "m5272lib.h"

#include "printf.h"

/* conversi�n a min�sculas de una letra */
#define MINUSCULAS(c)		(((c >= 'A') && (c <= 'Z'))? c+= 'a'-'A' : c)

/*==============================*/
void	_printf(char *formato,...)
/*==============================*/
{
	/* tipos simples que soporta _printf */
//	char caracter;
	char *texto;
	int entero;

	va_list args;

/* le indicamos que el �ltimo argumento fijo es formato */
va_start(args,formato);

/* recorremos toda la cadena de formato */
while (*formato != '\0') {

	/* si encontramos indicios de querer representar un tipo */
	if (*formato == '%') {
		
		formato++;
	
		/* lo convertimos a min�sculas */
		switch (MINUSCULAS(*formato)) {
		
			/* int */
			case 'd':
			case 'i':	entero = va_arg(args,int);
					outNum(10,entero,0);
					break;
			/* char 
			case 'c':	caracter = va_arg(args,char);
					outch(caracter);
					break;
			*/
			/* char * */
			case 's':	texto = va_arg(args,char*);
					output(texto);
					break;
			/* s�mbolo % */
			case '%':	outch(*formato);
					break;
			}
		}
	/* si no representamos el caracter */
	else
		outch(*formato);
	formato++;
	}
/* fin de los argumentos */
va_end(args);
}
