//------------------------------------------------------------------------------
// InterrExterna_GNU.c
//
//   Ejemplo para aprender el manejo de interrupciones externas con la
//   plataforma ENT2004CF.
//
// Autores: Ricardo de Córdoba, Juan Manuel Montero y Rubén San Segundo
// Adaptado a C por: Javier Guillén Álvarez
//------------------------------------------------------------------------------
#include "m5272.h"
#include "m5272lib.c"

#define V_BASE 0x40			// Dirección de inicio de los vectores de interrupción
#define DIR_VINT1 4 * (V_BASE + 1)	// Dirección del vector de INT1

//------------------------------------------------------
// void rutina_int1(void)
//
// Descripción:
//   Función de atención a la interrupción para la
//   interrupción externa.
//------------------------------------------------------
void rutina_int1(void)
{
  // Imprime el mensaje de la interrupción
  output("HE DETECTADO UN FLANCO DE SUBIDA\r\n");

  // Al ser interrupción externa debemos volverla a activar
  mbar_writeLong(MCFSIM_ICR1, 0xB8888888);
}

//------------------------------------------------------
// void __init(void)
//
// Descripción:
//   Función por defecto de inicialización del sistema
//------------------------------------------------------
void __init(void)
{
  // Fijamos el comienzo de vectores de interrupción en V_BASE
  mbar_writeByte(MCFSIM_PIVR,V_BASE); 

  // Escribimos la dirección de la función de atención a la interrupción
  ACCESO_A_MEMORIA_LONG(DIR_VINT1) = (ULONG) _prep_INT1;

  // Imprimimos el mensaje de comienzo
  output("COMIENZA EL PROGRAMA\r\n");
  
  // Configuramos INT1 para que se active con flanco de subida
  mbar_writeLong(MCFSIM_PITR, mbar_readLong(MCFSIM_PITR) | 0x80000000);

  // Marcamos la interrupción INT1 como no pendiente y de nivel 3
  mbar_writeLong(MCFSIM_ICR1, 0xB8888888);
  
  // Habilitamos interrupciones
  sti();	
}

//------------------------------------------------------
// void bucleMain(void)
//
// Descripción:
//   Función del programa principal
//------------------------------------------------------
void bucleMain(void){}

//---------------------------------------------------------
// Definición de rutinas de atención a la interrupción
// Es necesario definirlas aunque estén vacías
void rutina_int2(void){}
void rutina_int3(void){}
void rutina_int4(void){}
void rutina_tout0(void){}
void rutina_tout1(void){}
void rutina_tout2(void){}
void rutina_tout3(void){}
