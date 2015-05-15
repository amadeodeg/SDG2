#include "m5272adc_dac.h"
#include "m5272lib.h"


void set16_puertoS (UWORD valor) {
	DAC_dato((int)valor);
}

UWORD* get_puertoS() {
	return 0x0000;
}
