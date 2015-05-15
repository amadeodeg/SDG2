#ifndef M5272GPIO_H
#define M5272GPIO_H
#include "m5272lib.h"

void set_puertoS_H (UBYTE valor);
#define set_puertoS_L(valor) set_puertoS(valor)
void set_puertoS (UBYTE valor);
void set16_puertoS (UWORD valor);
UWORD lee16_puertoE (void);
UBYTE lee_puertoE (void);
void gpio_setup(void);
UBYTE lee_puerto1(void);
void set_puerto1 (UBYTE valor);
void set_puerto0 (UBYTE valor);
void set_led(UWORD valor);
UWORD get16_puertoS();
void set_gpio(int gpio, int valor);

#endif

