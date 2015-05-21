#include "m5272adc_dac.h"
#include "m5272lib.h"


void set16_puertoS (UWORD valor) {
	DAC_dato((int)valor);
}

UWORD get16_puertoS() {
	return 0x0000;
}

void set_gpio(int gpio, int valor){
	DAC_dato(valor);
}
