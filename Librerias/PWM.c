//------------------------------------------------------------------------------
// PWM_GNU.c
//
//   Programa sencillo para la utilización de PWM0 con la plataforma ENT2004CF
//
// Autores:          Juan Manuel Montero, Rubén San Segundo y 
//                   Álvaro de Guzmán Fernández González
//
// Adaptado a C por: Javier Guillén Álvarez
//------------------------------------------------------------------------------
#include "m5272.h"
#include "m5272lib.c"

#define FCR1_MASK 0x40

UBYTE ciclo, config, cksel;

//------------------------------------------------------
// void bucleMain(void)
//
// Descripción:
//   Función del programa principal
//
//------------------------------------------------------
void menu(void)
{
  char tecla;

  // Leemos un carácter del teclado del PC
  tecla = inch();
 
  // Procesamos la tecla pulsada
  switch(tecla)
  {    
    case '1':			// Si es tecla '1',
      if(ciclo == 255)		//   Si el ciclo de trabajo es máximo,
        config |= FCR1_MASK;	//     Activamos bit FRC1
      else			//   Si no,
        ciclo++;		//     Incrementamos el ciclo de trabajo
    break;
    case '2':    		// Si es tecla '2',
      if(config & FCR1_MASK)	//   Si FRC1 vale 1,
        config &= 0xBF;		//     Lo desactivamos
      else if(ciclo > 0)	//   Si no, si el ciclo es mayor que 0
          ciclo--;		//     Lo decrementamos
    break;
    case '3':			// Si es tecla '3',
      if(cksel > 0)		//   Decrementamos cksel
        cksel--;		//   mientras sea mayor que 0
    break;
    case '4':			// Si es tecla '4',
      if(cksel < 15)		//   Incrementamos cksel
        cksel++;		//   mientras sea menor que 15
    break;
  }

  // Actualizamos el valor de cksel en config
  config = (config & 0xF0) | cksel;
}

//------------------------------------------------------
// void __init(void)
//
// Descripción:
//   Función por defecto de inicialización del sistema
//
//------------------------------------------------------
void __init(void)
{
  // Inicializamos los parámetros de configuración del PWM0
  ciclo = 128;			// Ciclo de trabajo = 50%
  cksel = 8;			// Preescalado = 8  (F = 1KHz)
  config = 0x80 | cksel;	// PWM habilitado, LVL=0, FRC1=0

  // Mostramos las opciones del menú en el terminal
  output("GENERACIÓN DE LA SEÑAL PWM\r\n");
  output("------------------------------------------------------\r\n");
  output("TECLA 1 INCREMENTA CICLO DE TRABAJO, TECLA 2 DISMINUYE\r\n");
  output("TECLA 3 INCREMENTA FRECUENCIA, TECLA 4 DISMINUYE\r\n");
}

//------------------------------------------------------
// void bucleMain(void)
//
// Descripción:
//   Función del programa principal
//
//------------------------------------------------------
void bucleMain(void)
{
  // Definimos el ciclo de trabajo en el registro PWWD0
  mbar_writeByte(MCFSIM_PWWD0,ciclo);	
  
  // Ajustamos la frecuencia de funcionamiento y el bit FRC1
  mbar_writeByte(MCFSIM_PWCR0,config);
  
  // Actualizamos los parámetros del PWM0 en función de las teclas pulsadas
  menu();	
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