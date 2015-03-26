#include "calculos.h"
#include <stdlib.h>
#include "tasks.h"
#include "m5272adc_dac.h"

static pthread_t t_sensor1_sim;

static void*int_sim (void* arg){
  struct timeval timeout;
  
  while (1) {
    struct timeval *period = task_get_period (pthread_self());
    timeout.tv_sec = period->tv_sec;
    timeout.tv_usec = period->tv_usec
      - (period->tv_usec / 4);
    select (0, NULL, NULL, NULL, &timeout) ;

    calculaModuloDFT(ADC_dato());
  }
}

void sensor1_setup_sim (void){
  t_sensor1_sim = task_new ("int_sim", int_sim, 25, 25, 2, 1024);
}

void configModo1(){
	sensor1_setup_sim();
}



