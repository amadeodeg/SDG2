#include "calculos.h"
#include <stdlib.h>
#include "tasks.h"
#include "m5272adc_dac.h"
#include "mytime.h"

#define PERIOD 25 //ms
#define PRIORITY 2
#define STACK_SIZE 1024 //bytes
#define DEBUG 1

static pthread_t t_sensor1_sim;

static void* int_sim (void* arg){
  //struct timeval timeout;

  struct timeval next_activation;
  struct timeval now, timeout;

  struct timespec t1, t2;
  current_utc_time(&t1);
  current_utc_time(&t2);

  gettimeofday (&next_activation, NULL);

  while (1) {
    // struct timeval *period = task_get_period (pthread_self());
    // timeout.tv_sec = period->tv_sec;
    // timeout.tv_usec = period->tv_usec;
    // select (0, NULL, NULL, NULL, &timeout) ;
    struct timeval *period = task_get_period (pthread_self());
    timeval_add (&next_activation, &next_activation, period);
    gettimeofday (&now, NULL);
    timeval_sub (&timeout, &next_activation, &now);
    select (0, NULL, NULL, NULL, &timeout) ;

    if (DEBUG) {
      current_utc_time(&t2);
      //printf("%f\n", MIL_MILLONES * (t2.tv_sec - t1.tv_sec) + t2.tv_nsec - t1.tv_nsec);
      t1 = t2;
    }
    calculaModuloDFT(ADC_dato());
  }
  return NULL;
}

void sensor1_setup_sim (void){
  t_sensor1_sim = task_new ("int_sim", int_sim, PERIOD, PERIOD, PRIORITY, STACK_SIZE);
}

void configModo1(){
	sensor1_setup_sim();
}



