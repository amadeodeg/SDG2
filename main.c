#include "m5272adc_dac.h"
#include "m5272gpio.h"
#include "teclado_matricial.h"
#include "interrupciones.h"
#include "calculos.h"
#include "mytime.h"
#include "m5272lcd.h"
#include "m5272lib.h"
#include <time.h>
#include <stdint.h>

#define DEBUG 1
#define MODO_1 1
#define MODO_RANGO_2 2
#define MODO_TEST_9 9
#define MODO_TEST_8 8
#define PIN_RAMPA 16 //PIN 4
#define FREC_TEST 100


void
startModoDefault (uint16_t puertoS)
{
    while(1) {
    //     //struct timespec t1, t2;
    //     int i;
         struct timespec ts;
         struct timespec timePulse = {0, 1000000};
     //    int ms = T_PANTALLA/NUM_FREC_MUESTREADAS*100;
		
    //     //current_utc_time(&t1);
    //     for (i = 0; i < NUM_FREC_MUESTREADAS; i++){
    //         //if (DEBUG) printf("Frec: %d Dato: %d\n", i, mod2esc(getPmodFrecTot()+i));
    //         DAC_dato(mod2esc(getPmodFrecTot()+i));

    //         ts.tv_sec = ms / 1000;
    //         ts.tv_nsec = (ms % 1000) * 1000000;
    //         nanosleep(&ts, NULL);
    //     }
    //     //current_utc_time(&t2);
    //     //printf("%f\n", MIL_MILLONES * (t2.tv_sec - t1.tv_sec) + t2.tv_nsec - t1.tv_nsec);
    //     //reset bit inico rampa
		
        set16_puertoS(puertoS = (puertoS | 0x0010));  //bit 4 a uno el resto como estaba
        nanosleep(&timePulse,NULL);
        set16_puertoS(puertoS = (puertoS & 0xFFDF)); //bit 4 a 0 resto como estaba
         if (DEBUG) printf("PuertoS:%d\n", puertoS);
     }
}


void
startModoTestDAC ()
{
    int cont = 0;
    struct timespec timePulse = {0, 250000};
    while (1) {
        DAC_dato(calculaSeno(FREC_TEST, cont));
        cont = (cont+1)%NUM_FREC_MUESTREADAS;
        nanosleep(&timePulse, NULL);
    }
}

void
startModoTestADC_DAC ()
{
    struct timespec timePulse = {0, 250000};
    while(1) {
        DAC_dato(ADC_dato());
        nanosleep(&timePulse, NULL);
    }
}

void
configMinima ()
{
    DAC_ADC_init();
    if (DEBUG)
        printf("DAC configurado\n");
    LCD_reset();
    LCD_init();
    if (DEBUG)
        printf("LCD configurado\n");
	
}

void
configModo1 ()
{
    configInt4k();
}

void
configModo2 ()
{
    int inicial = 50;
    int final = 2000;

    LCD_write_s("F start");
    inicial = get_numero_teclado();
    LCD_write_s("F end");
    final = get_numero_teclado();
    if (DEBUG)
        printf("inicial: %d final %d \n", inicial, final);

    creaArrayFrecuencias(inicial, final);
    configInt4k();

}


int
main (int argc, char const *argv[])
{   
    uint16_t puertoS;
    int teclaModo;
    char* letra = "Modo";
    struct timespec t1 = {2, 0};

    if(DEBUG)
        printf("Empieza el programa\n");
    configMinima();
    puertoS = 32; // LED 5

    if (DEBUG)
        printf("ConfigMinima\n");
    while(*letra){        // Imprime "HOLA" en el display
        LCD_dato(*letra++);   // car·cter a car·cter
        nanosleep(&t1,NULL);        // Mantenemos el mensaje 1 segundo
    }
    teclaModo = get_tecla() - '0';
    if (DEBUG)
        printf("tecla: %d\n", teclaModo);

    switch (teclaModo){

    case MODO_RANGO_2:
        configModo2();
        if (DEBUG)
            printf("Modo2 configurado\n");
        startModoDefault(puertoS);
        break;

    case MODO_TEST_9:
        startModoTestDAC();
        break;

    case MODO_TEST_8:
        startModoTestADC_DAC();
        break;

    case MODO_1:
    default:
        configModo1();
        if (DEBUG)
            printf("Modo1 configurado\n");
        startModoDefault(puertoS);
        if (DEBUG)
            printf("Modo1 empezado \n");
        break;
    }

    return 0;
}
