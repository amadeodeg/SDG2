//------------------------------------------------------------------------------
// m5272gpio.c
//
//   Funciones del módulo de entrada salida de propósito general de la
//   plataforma de desarrollo ENT2004CF
//
// Actualizada por: Javier Guillén Álvarez
//------------------------------------------------------------------------------
#ifndef __M5272GPIO_C__
#define __M5272GPIO_C__

#include "m5272.h"
#include "m5272lib.c"

UWORD puertoS; // Contendrá una copia del valor del puerto S para posibilitar su lectura

//-------------------------------------------------------------
// void set_puertoS_H (UBYTE valor)
//
// Descripción:
//   Escribe en el byte alto del puerto de salida el valor
//
// Autor: Javier Guillén Álvarez
//-------------------------------------------------------------
void set_puertoS_H (UBYTE valor)
{
  UWORD* pchar;
  puertoS &= 0x00FF;
  puertoS |= (UWORD) (valor << 8);  
  pchar=(UWORD*)BASE_PUERTO_S;
  (*pchar)=puertoS;
}

//-------------------------------------------------------------
// void set_puertoS (UBYTE valor)
//
// Descripción:
//   Escribe en el byte bajo del puerto de salida
//
// Autor: Javier Guillén Álvarez
//-------------------------------------------------------------
// ALIAS para mantener compatibilidad con versiones anteriores
// de la librería.
#define set_puertoS_L(valor) set_puertoS(valor)

void set_puertoS (UBYTE valor)
{
  UWORD* pchar;
  puertoS &= 0xFF00;
  puertoS |= (UWORD) valor;  
  pchar=(UWORD*)BASE_PUERTO_S;
  (*pchar)=puertoS;
}

//-------------------------------------------------------------------
// void set_puertoS_L (UBYTE valor)
//
// Alias de 'set_puertoS(UBYTE valor)' para mantener compatibilidad
// con versiones anteriores de la librería.
//-------------------------------------------------------------------

void set16_puertoS (UWORD valor)
{
  UWORD* pchar;
  puertoS = valor;
  pchar=(UWORD*)BASE_PUERTO_S;
  (*pchar)=puertoS;
}

//------------------------------------------
// UWORD lee16_puertoE (void)
//
// Descripción:
//   Lee los 16 bits del puerto de entrada
//------------------------------------------
UWORD lee16_puertoE (void)
{
  return *((UWORD*) BASE_PUERTO_E);
}

//-------------------------------------------
// UBYTE lee_puertoE (void)
//
// Descripción:
//   Lee el byte bajo del puerto de entrada
//-------------------------------------------
UBYTE lee_puertoE (void)
{
  return  (UBYTE)*((UWORD*) BASE_PUERTO_E);
}

//-------------------------------------------------
// void gpio_setup(void)
// 
// Descripción:
//  Configuración del módulo de entrada/salida de 
//   propósito general del M5272 (GPIO) 
//
//-------------------------------------------------
void gpio_setup(void)
{  
  // Configuracion del puerto A
  mbar_writeLong(MCFSIM_PACNT, 0x00000000);	// Puerto A como Puerto IO
  mbar_writeShort(MCFSIM_PADDR, 0x7E80);	// Son todo entradas

  // Configuracion del puerto B
  // El puerto B comparte los pines Ethernet y la primera UART
  mbar_writeLong(MCFSIM_PBCNT, 0x55554155); 
  mbar_writeShort(MCFSIM_PBDDR, 0x0000); 	// Sólo afecta a PB5 y PB6 (in)
}

//----------------------------------------------------
//          Rutinas de I/O de los puertos 0 y 1
//----------------------------------------------------
UBYTE lee_puerto1(void)
{
  UWORD puerto,mascara;
  puerto=(UWORD)(mbar_readLong(MCFSIM_PADAT)>>16);
  mascara=((puerto>>1)&0x80);	// Valor IOPRT 15
  puerto&=0x7F; 		// IO_PORT14-IOPORT8
  puerto|=mascara;
  return ((UBYTE)(puerto&0xFF));
}

void set_puerto1 (UBYTE valor)
{
  UWORD puerto,mascara;
  puerto=(UWORD)(mbar_readLong(MCFSIM_PADAT)>>16);
  mascara=valor;
  mascara<<=1;
  mascara&=0x00100; // Valor IOPRT 15
  mascara|=((UWORD)valor&0x7F); 
  puerto&=0xFE80; // Ponemos a cero el valor leido
  puerto|=mascara;
  mbar_writeShort(MCFSIM_PADAT,puerto);
}

void set_puerto0 (UBYTE valor)
{
  UBYTE* pchar;
  pchar=(UBYTE*)BASE_PUERTO0;
  (*pchar)=valor;
}

//--------------------------------------------------------
// void set_led(UWORD valor)
//
// Descripción:
//   Presenta un valor en los LEDs de información de la
//   placa Antares. 
//
// Por ejemplo: set_led(0x07)
//
//     |   SLD0   |   SLD1   |    SLD2    |    SLD3    |
//     |----------|----------|------------|------------|
//     |    ON    |    ON    |     ON     |     OFF    | 
// 
// Autor: Alberto Quintana Ocaña
//--------------------------------------------------------
void set_led(UWORD valor)
{
  UWORD puerto1_valor;	// Valor del puerto IO 1
  UWORD mascara;	// Máscara con el valor de los LEDs
			// en las posiciones del puerto 1
  puerto1_valor=(UWORD) (mbar_readLong(MCFSIM_PADAT)>>16);
  mascara=0x0000;
  valor=valor&0x0F;
  mascara=((valor<<10)&0x3000);
  mascara=(((valor<<9)&0x0600)|mascara);
  puerto1_valor&=0xC9FF;// Ponemos a cero los bits de los LEDS
  puerto1_valor|=mascara;
  mbar_writeShort(MCFSIM_PADAT,puerto1_valor);
  set_puerto0(valor|(valor<<4));
}

#endif