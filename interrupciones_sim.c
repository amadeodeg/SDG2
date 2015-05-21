#include "calculos.h"
#include <stdlib.h>
#include "tasks.h"
#include "m5272adc_dac.h"
#include "mytime.h"

#define PERIOD 25 //Periodo de la interrupcion en ms
#define PRIORITY 2
#define STACK_SIZE 1024 //bytes

static pthread_t t_sensor1_sim;

//Funcion de atencion a la interrupcion simulada de 4kHz
static void* int_sim (void* arg)
{
  struct timeval next_activation;
  struct timeval now, timeout;

  gettimeofday (&next_activation, NULL);

  while (1) 
  {
    struct timeval *period = task_get_period (pthread_self());
    timeval_add (&next_activation, &next_activation, period);
    gettimeofday (&now, NULL);
    timeval_sub (&timeout, &next_activation, &now);
    select (0, NULL, NULL, NULL, &timeout) ;
    calculaModuloDFT(ADC_dato());
  }

  return NULL;
}

void sensor1_setup_sim (void)
{
  t_sensor1_sim = task_new ("int_sim", int_sim, PERIOD, PERIOD, PRIORITY, STACK_SIZE);
}

//Configuracion de la interrupcion a 4kHz en simulacion.
void configInt4k()
{
	sensor1_setup_sim();
}



