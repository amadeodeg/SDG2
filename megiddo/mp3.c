#include "m5272.h"
#include "megiddo.h"

void set16_puertoS (UWORD valor);

//int contadorRetardo=0;

//------------------------------------------------------
// void inicializarMP3(void)
//
// Descripción:
//   Inicializar el MP3. Antes de comenzar a utilizar el MP3
//   hay que inicializarlo llamando a esta función.
//   Se ponen los 16 puertos a nivel alto.
//------------------------------------------------------
void inicializarMP3(void)
{
  set16_puertoS(0xFFFF);
}


//------------------------------------------------------
// void activarMP3(void)
//
// Descripción:
//   Activa el MP3 para que pueda comenzarse a utilizar.
//   De caso contrario este esta inactivo y no puede utilizarse.
//   Se ponen los 4 pines inferiores a nivel bajo durante
//   un segundo para que el MP3 se active. Los pines son
//   S0 (pin 1), S1 (pin 2), S2 (pin 3) y S3 (pin 4)
//
//   
//------------------------------------------------------
void activarMP3(void)
{
  set16_puertoS(0xFFF0);
  ms_sleep (1000);
  set16_puertoS(0xFFFF);
}


//------------------------------------------------------
// void desactivarMP3(void)
//
// Descripción:
//   Deactiva el MP3 para que pueda comenzarse a utilizar.
//   Para que este este inactivo y no pueda utilizarse.
//   Se ponen los 4 pines superiores a nivel bajo durante
//   un segundo para que el MP3 se reinicie y quede
//   desactivado. Los pines son
//   S12 (pin 18), S13 (pin 19), S14 (pin 20) y S15 (pin 21)
//
//   
//------------------------------------------------------
void desactivarMP3(void)
{
  set16_puertoS(0x0FFF);
  ms_sleep (1000);
  set16_puertoS(0xFFFF);
}
