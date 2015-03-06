//------------------------------------------------------------------------------
// CocheFantastico_GNU.c
//
//   El "Coche Fantástico" tiene en su parte frontal un escáner con una luz que
//   periódicamente se mueve de derecha a izquierda y, a continuación de 
//   izquierda a derecha.
//
// Autores: Juan Manuel Montero, Rubén San Segundo Y José Luis Pau
// Adaptado a C por: Javier Guillén Álvarez
//------------------------------------------------------------------------------

#include "m5272lib.c"
#include "m5272gpio.c"		// Incluye funciones del módulo general de I/O

//---------------------------------------------------------
// void cocheFantastico(void)
//
// Descripción:
//   Desplaza un bit en el puerto de salida de izquierda a
//   derecha y viceversa
//
// Autor:
//   Javier Guillén Álvarez
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
// Descripción:
//   Función por defecto de inicialización del sistema
//
//---------------------------------------------------------
void __init(void)
{
  set16_puertoS(1);		// Inicializa el puerto de Salida a 1
}

//---------------------------------------------------------
// void bucleMain(void)
//
// Descripción:
//   Función del programa principal
//
//---------------------------------------------------------
void bucleMain(void)
{
  cocheFantastico();
}

//---------------------------------------------------------
// Definición de rutinas de atención a la interrupción
// Es necesario definirlas aunque estén vacías
void rutina_int1(void){}
void rutina_int2(void){}
void rutina_int3(void){}
void rutina_int4(void){}
void rutina_tout0(void){}
void rutina_tout1(void){}
void rutina_tout2(void){}
void rutina_tout3(void){}
