#include "m5272adc_dac.h"
#include "m5272gpio.h"
#include "teclado_matricial.h"
#include "interrupciones.h"
#include "calculos.h"
#include "mytime.h"
#include "m5272lcd.h"
#include "m5272lib.h"
#include <time.h>
#include <unistd.h>
#include <stdint.h>

#define DEBUG 1
#define MODO_1 1
#define MODO_RANGO_2 2
#define MODO_TEST_9 9
#define MODO_TEST_8 8
#define PIN_RAMPA 4 
#define FREC_TEST 100


void
startModoDefault ()
{
     int i;
     int dato;
     int us = (T_PANTALLA/NUM_FREC_MUESTREADAS)*1000-14;
     //int numero = 3317;
     int * modFrecTot = getPmodFrecTot();
    //struct timespec timePulse = {0, 1000000};
    while(1) {
        //struct timespec t1, t2;
       
        //struct timespec ts;
         
		
        //current_utc_time(&t1);
        for (i = 0; i < NUM_FREC_MUESTREADAS; i++){
            //if (DEBUG) printf("Frec: %d Dato: %d\n", i, mod2esc(getPmodFrecTot()+i));
            set_gpio(5,1);
            dato = mod2esc(modFrecTot+i); 
            cli(); //COMENTAR PARA SIM
            //if (DEBUG) printf("%d, ", ADC_dato());
            
            DAC_dato(dato); //~8us
            
            sti(); //COMENTAR PARA SIM
            
            // ts.tv_sec = ms / 1000;
            // ts.tv_nsec = (ms % 1000) * 1000000;
            // nanosleep(&ts, NULL);
            set_gpio(5,0);
            usleep(us);
        }
        //current_utc_time(&t2);
        //printf("%f\n", MIL_MILLONES * (t2.tv_sec - t1.tv_sec) + t2.tv_nsec - t1.tv_nsec);
        //reset bit inico rampa
		//usleep(40000);
        set_gpio(PIN_RAMPA, 1);  //bit 4 a 1 el resto como estaba
        //nanosleep(&timePulse, NULL);
        //if(DEBUG) printf("me duermo\n");
        usleep(1000);
        //if(DEBUG) printf("me despierto\n");
        set_gpio(PIN_RAMPA, 0); //bit 4 a 0 resto como estaba
        
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
    //gpio_setup();
    //if (DEBUG)
     //   printf("GPIO configurado\n");
    DAC_ADC_init();
    if (DEBUG)
        printf("DAC_ADC configurado\n");
    LCD_reset();
    LCD_init();
    if (DEBUG)
        printf("LCD configurado\n");
	
}

void
configModo1 ()
{
    configPasoFrecPointers();
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
    int teclaModo;
    char* letra = "Modo";

    if(DEBUG)
        printf("Empieza el programa\n");
    configMinima();

    if (DEBUG)
        printf("ConfigMinima\n");

    while(*letra){       
        LCD_dato(*letra++);   // car·cter a car·cter
        usleep(20000);      // Mantenemos el mensaje 1 segundo
    }
    
    teclaModo = get_tecla() - '0';
    if (DEBUG)
        printf("tecla: %d\n", teclaModo);

    switch (teclaModo){

    case MODO_RANGO_2:
        configModo2();
        letra = "2";
        while(*letra){       
            LCD_dato(*letra++);   // car·cter a car·cter
            usleep(20000);        // Mantenemos el mensaje 1 segundo
        }
        if (DEBUG)
            printf("Modo2 configurado\n");
        startModoDefault();
        break;

    case MODO_TEST_9:
        startModoTestDAC();
        break;

    case MODO_TEST_8:
        startModoTestADC_DAC();
        break;

    case MODO_1:
    default:
    letra = "1";
        while(*letra){       
            LCD_dato(*letra++);   // car·cter a car·cter
            usleep(20000);        // Mantenemos el mensaje 1 segundo
        }
        configModo1();
        
        if (DEBUG)
            printf("Modo1 configurado\n");
        startModoDefault();
        if (DEBUG)
            printf("Modo1 empezado \n");
        break;
    }

    return 0;
}
