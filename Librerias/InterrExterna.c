//------------------------------------------------------------------------------
// InterrExterna_GNU.c
//
//   Ejemplo para aprender el manejo de interrupciones externas con la
//   plataforma ENT2004CF.
//
// Autores: Ricardo de C�rdoba, Juan Manuel Montero y Rub�n San Segundo
// Adaptado a C por: Javier Guill�n �lvarez
//------------------------------------------------------------------------------
#include "m5272.h"
#include "m5272lib.c"

#define V_BASE 0x40			// Direcci�n de inicio de los vectores de interrupci�n
#define DIR_VINT1 4 * (V_BASE + 1)	// Direcci�n del vector de INT1

//------------------------------------------------------
// void rutina_int1(void)
//
// Descripci�n:
//   Funci�n de atenci�n a la interrupci�n para la
//   interrupci�n externa.
//------------------------------------------------------
void rutina_int1(void)
{
  // Imprime el mensaje de la interrupci�n
  output("HE DETECTADO UN FLANCO DE SUBIDA\r\n");

  // Al ser interrupci�n externa debemos volverla a activar
  mbar_writeLong(MCFSIM_ICR1, 0xB8888888);
}

//------------------------------------------------------
// void __init(void)
//
// Descripci�n:
//   Funci�n por defecto de inicializaci�n del sistema
//------------------------------------------------------
void __init(void)
{
  // Fijamos el comienzo de vectores de interrupci�n en V_BASE
  mbar_writeByte(MCFSIM_PIVR,V_BASE); 

  // Escribimos la direcci�n de la funci�n de atenci�n a la interrupci�n
  ACCESO_A_MEMORIA_LONG(DIR_VINT1) = (ULONG) _prep_INT1;

  // Imprimimos el mensaje de comienzo
  output("COMIENZA EL PROGRAMA\r\n");
  
  // Configuramos INT1 para que se active con flanco de subida
  mbar_writeLong(MCFSIM_PITR, mbar_readLong(MCFSIM_PITR) | 0x80000000);

  // Marcamos la interrupci�n INT1 como no pendiente y de nivel 3
  mbar_writeLong(MCFSIM_ICR1, 0xB8888888);
  
  // Habilitamos interrupciones
  sti();	
}

//------------------------------------------------------
// void bucleMain(void)
//
// Descripci�n:
//   Funci�n del programa principal
//------------------------------------------------------
void bucleMain(void){}

//---------------------------------------------------------
// Definici�n de rutinas de atenci�n a la interrupci�n
// Es necesario definirlas aunque est�n vac�as
void rutina_int2(void){}
void rutina_int3(void){}
void rutina_int4(void){}
void rutina_tout0(void){}
void rutina_tout1(void){}
void rutina_tout2(void){}
void rutina_tout3(void){}
