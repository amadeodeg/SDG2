//------------------------------------------------------------------------------
// DAC_GNU.c
//
//   Programa sencillo para mostrar el manejo de un conversor Digital
//   Anal�gico utilizando QSPI (Queued Serial Peripheral Interface).
//
// Autores: Juan Manuel Montero y Rub�n San Segundo
// Adaptado a C por: Javier Guill�n �lvarez
//------------------------------------------------------------------------------
#include "m5272lib.c"
#include "m5272adc_dac.c"

//------------------------------------------------------
// void __init(void)
//
// Descripci�n:
//   Funci�n por defecto de inicializaci�n del sistema
//
//------------------------------------------------------
void __init(void)
{
  DAC_ADC_init();
}

//------------------------------------------------------
// void bucleMain(void)
//
// Descripci�n:
//   Funci�n del programa principal
//
//------------------------------------------------------
void bucleMain(void)
{
  WORD valor, incremento = 100;

  // Imprime intrucciones
  output("CONECTE EL OSCILOSCOPIO EN LA SALIDA ANAL�GICA\r\n");
  output("PULSE UNA TECLA CUANDO EST� LISTO PARA MEDIR LA SE�AL...\r\n");

  // Espera a que se pulse una tecla
  inch();

  // Imprime mensaje de generando se�al
  output("...GENERANDO SE�AL TRIANGULAR...\r\n");

  // Bucle de generaci�n de se�al
  while(TRUE)
  {
    // Rampa de subida
    for(valor = 0; valor <= 0xFFF; valor += incremento)
      DAC_dato(valor);

    // Rampa de bajada
    for(valor = 0xFFF; valor >= 0; valor -= incremento)
      DAC_dato(valor);
  }
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
