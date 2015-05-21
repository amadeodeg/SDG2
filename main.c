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

#define DEBUG 0

#define MODO_1 1
#define MODO_RANGO_2 2
#define MODO_TEST_9 9
#define MODO_TEST_8 8
#define PIN_RAMPA 4 //Pin por el que se saca el reset de la rampa.
#define T_RESET_RAMPA 1000    //Tiempo del pulso de rampa en us.
#define FREC_TEST 100
#define T_AJUSTE 14 //Tiempo que tarda en sacar por el DAC en us.

//Ejecuta el modo por defecto. Muestra por en el osciloscopio la DFT calculada.
void
startModoDefault ()
{
    int i;
    int dato;
    int us = (T_PANTALLA/NUM_FREC_MUESTREADAS)*1000-14;
    int * modFrecTot = getPmodFrecTot();
    while(1) {
        for (i = 0; i < NUM_FREC_MUESTREADAS; i++){
            dato = mod2esc(modFrecTot+i); 
            cli(); //Se desabilitan las interrupciones para evitar colisiones con el ADC
            DAC_dato(dato); //Dura aprox 8 us
            sti(); //Se habilitan las interrupciones.
            usleep(us);
        }
        set_gpio(PIN_RAMPA, 1);
        usleep(T_RESET_RAMPA);    
        set_gpio(PIN_RAMPA, 0);  
     }
}

//Ejecuta el modo de prueba del DAC. Saca un seno de frecuencia FREC_TEST
void
startModoTestDAC ()
{
    int dato;
    int cont = 0;
    while (1) {
        dato = calculaSeno(FREC_TEST, cont);
        DAC_dato(dato);
        cont = (cont+1)%NUM_FREC_MUESTREADAS;
        usleep(250); //Para frecuencia de muestreo de 4kHz
    }
}

//Ejecuta el modo de prueba del ADC. Saca en el DAC lo que entra por el ADC.
void
startModoTestADC_DAC ()
{
    while(1) {
        DAC_dato(ADC_dato());
        usleep(250); //Para frecuencia de muestreo de 4kHz
    }
}

//Configura lo comun para todos los modos.
void
configMinima ()
{
    DAC_ADC_init();
    if (DEBUG) {
        printf("DAC_ADC configurado\n");
    }
    LCD_reset();
    LCD_init();
    if (DEBUG) {
        printf("LCD configurado\n");
    }
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
    if (DEBUG){
        printf("inicial: %d final %d \n", inicial, final);
    }
    creaArrayFrecuencias(inicial, final);
    configInt4k();
}

//Programa principal. Configura lo necesario y permite elegir el modo de funcionamiento.
int
main (int argc, char const *argv[])
{   
    int teclaModo;
    char* modo = "Modo";

    if(DEBUG) {
        printf("Empieza el programa\n");
    }
    configMinima();

    if (DEBUG) {
        printf("ConfigMinima\n");
    }

    LCD_write_s(modo);
    
    teclaModo = get_tecla() - '0';

    if (DEBUG) {
        printf("tecla: %d\n", teclaModo);
    }

    switch (teclaModo){

    case MODO_RANGO_2:
        configModo2();

        modo = " 2";
        LCD_write_s(modo);

        if (DEBUG) {
            printf("Modo2 configurado\n");
        }

        startModoDefault();

        break;

    case MODO_TEST_9:
        modo = " 9";
        LCD_write_s(modo);
        startModoTestDAC();
        break;

    case MODO_TEST_8:
        modo = " 8";
        LCD_write_s(modo);
        startModoTestADC_DAC();
        break;

    case MODO_1:
    default:
        modo = " 1";
        LCD_write_s(modo);

        configModo1();
        
        if (DEBUG) {
            printf("Modo1 configurado\n");
        }

        startModoDefault();

        if (DEBUG) {
            printf("Modo1 empezado \n");
        }
        
        break;
    }

    return 0;
}
