#include <stdio.h>
#include "m5272.h"
#include "m5272lib.h"

//registros de la UART1
#define MCFSIM_UTB1                     0x14C
#define MCFSIM_URB1                     0x14C
#define MCFSIM_UIMR1                    0x154
#define MCFSIM_USR1                     0x144
#define MCFSIM_UCSR1                    0x144
#define MCFSIM_UCR1                     0x148
#define MCFSIM_UMRX1                    0x140
#define MCFSIM_UDU1                     0x158
#define MCFSIM_UDL1                     0x15C

//mascaras de uso de la UART
#define MSKI_UCR1                     0x30
#define MSKII_UCR1                    0x20
#define MSKIII_UCR1                   0x10
#define MSK_UMR11                     0x13
#define MSK_UMR21                     0x07
#define MSK_UCSR1                     0xDD
#define MSK_UIMR1                     0x00
#define MSK_UDU1                      0x00
#define MSK_UDL1                      0xD7
#define MSKIV_UCR1                    0x05
#define RX_RDY                        0x01
#define TX_RDY		              0x04

#define NUM_DATOS 100

BYTE datos_recibidos[NUM_DATOS];	//array donde se guardan los datos recibidos 


/* ------------------------------------------------------------------------------
   Funcion de inicialización de los registros de la UART y configuración de
   los parámetros de transmisión dados en la cabecera del programa
-------------------------------------------------------------------------------*/
void UART_init(void){
	
  /* Reset Transmisor */
  mbar_writeByte(MCFSIM_UCR1,MSKI_UCR1);
  retardo(RET_3MS);
	
  /* Reset Receptor */
  mbar_writeByte(MCFSIM_UCR1,MSKII_UCR1);
  retardo(RET_3MS);

  /* Reset Mode Register */
  mbar_writeByte(MCFSIM_UCR1,MSKIII_UCR1);
  retardo(RET_3MS);
	
  /* Sin paridad, 8 bits de datos */
  mbar_writeByte(MCFSIM_UMRX1,MSK_UMR11);

  /* Modo normal, 1 bit de parada */
  mbar_writeByte(MCFSIM_UMRX1,MSK_UMR21);
	
  /*reloj de la UART:CLK/32 */
  mbar_writeByte(MCFSIM_UCSR1,MSK_UCSR1);
	
  /* Deshabilitar interrupciones */
  mbar_writeByte(MCFSIM_UIMR1,MSK_UIMR1);
	
  /* VELOCIDAD=9600=66E6/(32XUD)==>UD=215=$D7 */
  mbar_writeByte(MCFSIM_UDU1,MSK_UDU1);
  mbar_writeByte(MCFSIM_UDL1,MSK_UDL1);
	
  /* Habilitar rx y tx */
  mbar_writeByte(MCFSIM_UCR1,MSKIV_UCR1);

}

/* -----------------------------------------------------------------------------
   Funcion que se encarga de limpiar la zona de datos rellenandola con ceros.
   Esto se hace debido a que la implementacion de la funcion output imprime
   hasta encontrarse un $00 de manera que es la unica forma de poder usarla
   para imprimir caracter a caracter lo recibido.
------------------------------------------------------------------------------*/
void CLR_zona_datos(void)
{
  int i;
  for(i=0;i<NUM_DATOS;i++)
    datos_recibidos[i]=0;
}

/* ------------------------------------------------------------------------------
   Funcion que se encarga de enviar por el puerto serie los datos pasados como
   parametro seguido de un retorno de carro.
------------------------------------------------------------------------------- */
void enviaSerie(char* mensaje)
{
  while(*mensaje){		//mientras el mensaje no haya acabado
    BYTE estado = mbar_readByte(MCFSIM_USR1);	//obtenemos estado
    BYTE estado_tx = estado & TX_RDY;		//cogemos bit tx_rdy
    if(estado_tx != TX_RDY) continue;
    mbar_writeByte(MCFSIM_UTB1,*mensaje++);
    retardo(RET_3MS);
  }
  mbar_writeByte(MCFSIM_UTB1,0x0D);
}


/* ------------------------------------------------------------------------------
   Esta funcion se encarga de leer los datos recibidos por el puerto serie y
   almacenarlos en el array de bytes datos_recibidos.
------------------------------------------------------------------------------- */
void recibeSerie(void){
  int i=0;
	
  int loop = 0;
  while(loop < 1000000){	
    BYTE estado_tx = mbar_readByte(MCFSIM_USR1);	//obtenemos estado
    estado_tx = estado_tx & RX_RDY;
    if(estado_tx != RX_RDY){
      loop++;
      continue;
    }						//cogemos bit rx_rdy
    datos_recibidos[i] = mbar_readByte(MCFSIM_UTB1);//almacenamos byte
    //en zona dedicada
    putchar(datos_recibidos[i]); fflush(stdout);
    i++;
    loop=0;					
  }
	
}
 
/* ------------------------------------------------------------------------------
   Rutina principal. Envia la serie de comandos AT necesaria para el envio del
   mensaje. Envia los comandos uno a uno y recibe el eco generado por el terminal
   que es lo que presenta por pantalla.
-------------------------------------------------------------------------------*/
int main (void)
{ 
	
  UART_init();
  CLR_zona_datos();	
  puts("\nSe comprueba la linea");
	
  enviaSerie("AT");
  recibeSerie();
  CLR_zona_datos();
	
  puts("\nSe introduce el PIN de la tarjeta");
	
  enviaSerie("AT+CPIN=2520");
  recibeSerie();
  CLR_zona_datos();
	
  puts("\nActiva modo texto");
	
  enviaSerie("AT+CMGF=1");
  recibeSerie();
  CLR_zona_datos();
	
  puts("\nEnvía SMS");
	
  enviaSerie("AT+CMGS=\"+34626188197\"");
  recibeSerie();
  CLR_zona_datos();
	
  enviaSerie("mensaje de prueba");
  mbar_writeByte(MCFSIM_UTB1,0x01A);	//caracter de confirmacion
  recibeSerie();
  CLR_zona_datos();

  while(1);
  return 0;
}
