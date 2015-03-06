//------------------------------------------------------------------------------
// DAC_GNU.c
//
//   Programa sencillo para mostrar el manejo de un conversor Digital
//   Analógico utilizando QSPI (Queued Serial Peripheral Interface).
//
// Autores: Juan Manuel Montero y Rubén San Segundo
// Adaptado a C por: Javier Guillén Álvarez
//------------------------------------------------------------------------------
#include "m5272lib.c"
#include "m5272adc_dac.c"

//------------------------------------------------------
// void __init(void)
//
// Descripción:
//   Función por defecto de inicialización del sistema
//
//------------------------------------------------------
void __init(void)
{
  DAC_ADC_init();
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
  WORD valor, incremento = 100;

  // Imprime intrucciones
  output("CONECTE EL OSCILOSCOPIO EN LA SALIDA ANALÓGICA\r\n");
  output("PULSE UNA TECLA CUANDO ESTÉ LISTO PARA MEDIR LA SEÑAL...\r\n");

  // Espera a que se pulse una tecla
  inch();

  // Imprime mensaje de generando señal
  output("...GENERANDO SEÑAL TRIANGULAR...\r\n");

  // Bucle de generación de señal
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
