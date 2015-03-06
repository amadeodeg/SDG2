//------------------------------------------------------------------------------
// CocheFantastico_GNU.c
//
//   El "Coche Fant�stico" tiene en su parte frontal un esc�ner con una luz que
//   peri�dicamente se mueve de derecha a izquierda y, a continuaci�n de 
//   izquierda a derecha.
//
// Autores: Juan Manuel Montero, Rub�n San Segundo Y Jos� Luis Pau
// Adaptado a C por: Javier Guill�n �lvarez
//------------------------------------------------------------------------------

#include "m5272lib.c"
#include "m5272gpio.c"		// Incluye funciones del m�dulo general de I/O

//---------------------------------------------------------
// void cocheFantastico(void)
//
// Descripci�n:
//   Desplaza un bit en el puerto de salida de izquierda a
//   derecha y viceversa
//
// Autor:
//   Javier Guill�n �lvarez
//---------------------------------------------------------
void cocheFantastico(void)
{
  UWORD valor = 1;	// Valor a escribir en el puerto de salida
  UINT retVal = 50000;	// Retardo introducido en microsegundos. (aprox. 50ms)

  while(TRUE)
  {
    // Desplazamiento del bit hacia la izquierda 
    for(valor = 1; valor < 0x8000; valor = valor << 1){
      retardo(retVal);
      set16_puertoS(valor);
    }

    // Desplazamiento del bit hacia la derecha 
    for(valor = 0x08000; valor > 1; valor = valor >> 1){
      retardo(retVal);
      set16_puertoS(valor);
    }
  }
}

//---------------------------------------------------------
// void __init(void)
//
// Descripci�n:
//   Funci�n por defecto de inicializaci�n del sistema
//
//---------------------------------------------------------
void __init(void)
{
  set16_puertoS(1);		// Inicializa el puerto de Salida a 1
}

//---------------------------------------------------------
// void bucleMain(void)
//
// Descripci�n:
//   Funci�n del programa principal
//
//---------------------------------------------------------
void bucleMain(void)
{
  cocheFantastico();
}

//---------------------------------------------------------
// Definici�n de rutinas de atenci�n a la interrupci�n
// Es necesario definirlas aunque est�n vac�as
void rutina_int1(void){}
void rutina_int2(void){}
void rutina_int3(void){}
void rutina_int4(void){}
void rutina_tout0(void){}
void rutina_tout1(void){}
void rutina_tout2(void){}
void rutina_tout3(void){}
