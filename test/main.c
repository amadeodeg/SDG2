#include "m5272gpio.h"
#include <time.h>
#include <stdint.h>
#include "m5272lcd.h"
#include <stdio.h>
#include "interrupciones.h"

int main(int argc, char const *argv[])
{	
	struct timespec t = { 5, 0 };
	set16_puertoS(32);
	nanosleep(&t,NULL);
	configModo1();
	while(1){
		nanosleep(&t,NULL);
	}
	return 0;
}