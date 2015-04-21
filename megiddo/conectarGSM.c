#include "m5272.h"
#include "megiddo.h"
#include <string.h>
#include <stdio.h>

#ifndef NDEBUG
#define DEBUG(x) x
#else
#define DEBUG(x)
#endif

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

#define POS_RADIO			71//posicion del radio en el sms
#define POS_CIRCULO			72//posicion del circulo en el sms


#define NUM_DATOS 100

static BYTE datos_recibidos[NUM_DATOS];	//array donde se guardan los datos recibidos 
static BYTE coordenadas[2];//array donde se guarda las coordenadas al leer un sms

//juanjo y jorge, hemos declarado esto estatico, si algun problema comentadlo.

//------------------------------------------------------
//void CLR_zona_datos(void)
//
//Descripción:
//   Funcion que se encarga de limpiar la zona de datos 
//   rellenandola con ceros.
//   Esto se hace debido a que la implementacion de la 
//   funcion output imprime hasta encontrarse un $00 de
//   manera que es la unica forma de poder usarla
//   para imprimir caracter a caracter lo recibido.
//------------------------------------------------------

void CLR_zona_datos(void){
  int i;
  for (i = 0; i < NUM_DATOS; i++)
    datos_recibidos[i] = 0;
}


//------------------------------------------------------
//void inicilaizarGSM(void)
//
//Descripción:
//   Funcion de inicialización de los registros de la 
//   UART y configuración de los parámetros de transmisión
//   dados en la cabecera del programa.
//   Antes de comenzar a utilizar el GPS se debe inicializar.
//------------------------------------------------------

void inicializarGSM (void)
{
  /* Reset Transmisor */
  mbar_writeByte(MCFSIM_UCR1,MSKI_UCR1);
  ms_sleep (3);
	
  /* Reset Receptor */
  mbar_writeByte(MCFSIM_UCR1,MSKII_UCR1);
  ms_sleep (3);

  /* Reset Mode Register */
  mbar_writeByte(MCFSIM_UCR1,MSKIII_UCR1);
  ms_sleep (3);
	
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

  /* Borra la zona de datos */
  CLR_zona_datos();
}

//------------------------------------------------------
//void introducirPIN(int PIN)
//
//Descripción:
//   Se introduce el PIN en la tarjeta. Debe llamarse antes 
//   de utilizar el sistema GSM.   
//------------------------------------------------------

void introducirPIN (char* pin)
{
  char buf [1024];
  sprintf (buf,"AT+CPIN=%s",pin);

  enviaSerie(buf);
  recibeSerie();
  CLR_zona_datos();
	
}

//------------------------------------------------------
//void enviaSerie(char* mensaje)
//
//Descripción:
//   Funcion que se encarga de enviar por el puerto 
//   serie los datos pasados como parametro seguido 
//   de un retorno de carro.
//------------------------------------------------------

void enviaSerie(char* mensaje){
	DEBUG(printf ("Enviando: %s\n", mensaje));
	while(*mensaje){		//mientras el mensaje no haya acabado
		BYTE estado = mbar_readByte(MCFSIM_USR1);	//obtenemos estado
		BYTE estado_tx = estado & TX_RDY;		//cogemos bit tx_rdy
		if(estado_tx != TX_RDY) continue;
		mbar_writeByte(MCFSIM_UTB1,*mensaje++);
		ms_sleep (3);
	}
	mbar_writeByte(MCFSIM_UTB1,0x0D);
}

//------------------------------------------------------
//void recibeSerie(void)
//
//Descripción:
//   Esta funcion se encarga de leer los datos recibidos 
//   por el puerto serie y almacenarlos en el array de 
//   bytes datos_recibidos.
//------------------------------------------------------

void recibeSerie(void)
{
  int i=0;
  int loop = 0;
  while(loop < 75000000){
    //obtenemos estado
    BYTE estado_tx = mbar_readByte(MCFSIM_USR1);
    estado_tx = estado_tx & RX_RDY; //cogemos bit rx_rdy
    if (estado_tx != RX_RDY) {
      loop++;
      continue;
    }
    //almacenamos byte en zona dedicada
    datos_recibidos[i] = mbar_readByte(MCFSIM_UTB1);
    putchar (datos_recibidos[i]); fflush(stdout);
    i++;
    loop=0;					
  }
	
}

//------------------------------------------------------
//void recibeSerie2(void)
//
//Descripción:
//   Esta funcion se encarga de leer los datos recibidos 
//   por el puerto serie y almacenarlos en el array de 
//   bytes datos_recibidos.
//------------------------------------------------------

BYTE recibeSerie2(void){
  int i=0;
  int j=0;
	
  int loop = 0;
  while (loop < 50000000){	
    BYTE estado_tx = mbar_readByte(MCFSIM_USR1);	//obtenemos estado
    estado_tx = estado_tx & RX_RDY;
    if(estado_tx != RX_RDY){
      loop++;
      continue;
    }						//cogemos bit rx_rdy
    datos_recibidos[i] = mbar_readByte(MCFSIM_UTB1);//almacenamos byte
    j++;

    if (j==POS_RADIO)	
      coordenadas[0] = datos_recibidos[i];

    if(j==POS_CIRCULO)	
      coordenadas[1] = datos_recibidos[i];

    i++;
    loop=0;					
  }
  return 0;
}

BYTE getRadio(){
	return coordenadas[0];
}

BYTE getCirculo(){
	return coordenadas[1];
}

void vaciaTarjeta()
{
  int i;
  for(i=0;i<100;i++){
    enviaSerie("AT+CMGD=1");//se elimina el mensaje recien recibido
    recibeSerie();
    CLR_zona_datos();
  }
}
