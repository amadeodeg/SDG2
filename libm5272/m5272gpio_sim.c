#include "m5272adc_dac.h"
#include "m5272lib.h"

//Saca un valor por el puerto de salida.
void set16_puertoS (UWORD valor) {
	DAC_dato((int)valor);
}

//Para mantener la compatibilidad en simulacion.
UWORD get16_puertoS() {
	return 0x0000;
}

//Saca un valor  por el puerto de salida. 
void set_gpio(int gpio, int valor){
	DAC_dato(valor);
}
