//------------------------------------------------------------------------------
// m5272adc-dac.c
//
//   Funciones de configuración y control de los conversores ADC/DAC de la
//   plataforma de desarrollo ENT2004CF
//
// Autor: Javier Guillén Álvarez
//------------------------------------------------------------------------------
#ifndef __M5272ADC_DAC_C__
#define __M5272ADC_DAC_C__

#include "m5272.h"
#include "m5272lib.c"

//--------------------------------------------------------------
//     RUTINAS DE CONFIGURACIÓN Y MANEJO DEL DAC Y DEL ADC
//--------------------------------------------------------------
  
#define QSPI_QMR_INIT 0x8000		// Valor de inicio del registro QMR del QSPI
#define QDLYR_SPE_MASK 0x8000		// Máscara para activar la Tx del DAC y el ADC
#define QIR_SPIF_MASK 0x0001		// Máscara para leer el flag de fin de Tx

// MACRO: QSPI_setBaudRate(baudios) - Fija la velocidad de Tx del QSPI
#define QSPI_setBaudRate(baudios) 	mbar_writeShort(MCFSIM_QMR, QSPI_QMR_INIT | MCF_CLK/(2*baudios))

// MACRO: QSPI_setENDQP - Hace que ENDQP apunte al último comando de COMMAND_RAM a transmitir
#define QSPI_setENDQP(numComandos)	mbar_writeShort(MCFSIM_QWR, 0x1000 | ((numComandos - 1) << 8))

// MACRO: QSPI_activaTx - Inicia la Tx del QSPI
#define QSPI_activaTx 	mbar_writeShort(MCFSIM_QDLYR, mbar_readShort(MCFSIM_QDLYR)|QDLYR_SPE_MASK)

// MACRO: QSPI_rstSPIF - Borra el flag de fin de Tx del QSPI
#define QSPI_rstSPIF 	mbar_writeShort(MCFSIM_QIR, mbar_readShort(MCFSIM_QIR)|QIR_SPIF_MASK)

// MACRO: QSPI_finTx - Devuelve '1' cuando ha terminado la transmisión del QSPI
#define QSPI_finTx 	(mbar_readShort(MCFSIM_QIR) & QIR_SPIF_MASK)

//------------------------------------------------------------------  
//                      CONFIGURACIÓN DEL QSPI
//------------------------------------------------------------------  

//------------------------------------------------------------------
// void DAC_ADC_init()
//
// Descripción:
//    Inicializa el QSPI para el uso del DAC y del ADC.
//
// Autor: Javier Guillén Álvarez
//------------------------------------------------------------------
void DAC_ADC_init()
{  
  mbar_writeShort(MCFSIM_ICR4, 0x8000); 	// Desactivar interr QSPI
  mbar_writeLong(MCFSIM_PACNT, 0x00800000); 	// Puerto A como Puerto IO y QSPI_CS1
  
  mbar_writeShort(MCFSIM_QDLYR, 0x0000);	// Retardos inicial y final por defecto, QSPI deshabilitado
  mbar_writeShort(MCFSIM_QIR, 0xD00D);		// Sin interrupciones y borrar SPIF

  mbar_writeShort(MCFSIM_QMR,QSPI_QMR_INIT);	// Maestro,16bits,CPOL = 0,CPHA = 0,BAUD sin definir 
 
}

//------------------------------------------------------------------  
//                      FUNCIONES DEL DAC
//------------------------------------------------------------------  

#define DAC_BAUD_RATE 10000000				// Baudios de Tx serie del DAC (Máximo 10000000)

void DAC_escribeTxRAM(int dato){
  mbar_writeShort(MCFSIM_QAR, QSPI_TX_RAM_START); 	// Puntero datos para transmitir
  mbar_writeShort(MCFSIM_QDR, dato << 1); 		// Escribe el dato  en TX RAM

  // El formato de los 16 bits a transmitir al DAC es:
  //  --- --- --- ----- ----- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---
  // | 0 | 0 | 0 | D11 | D10 | D9 | D8 | D7 | D6 | D5 | D4 | D3 | D2 | D1 | D0 | 0 |
  //  --- --- --- ----- ----- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---
  // donde Dx es el bit x del dato que se convertirá
}

void DAC_escribeCommandRAM(){
  mbar_writeShort(MCFSIM_QAR, QSPI_COMMAND_RAM_START); 	// Puntero commands
  mbar_writeShort(MCFSIM_QDR, 0x4D00); 			// Comando Tx, CS1 no continua >8 bits SIN retardos 
}

//---------------------------------------------------------
// void DAC_dato(int dato)
//
// Descripción: 
//    Envía un dato al DAC para su conversión.
//
// Autor: Javier Guillén Álvarez
//---------------------------------------------------------
void DAC_dato(int dato)
{
  static UBYTE primeraVez=1;

  if(!primeraVez){
    while(!QSPI_finTx){}	 	// Espera hasta fin de Tx (SPIF)
  }else{
    primeraVez = 0;
  } 
  
  QSPI_rstSPIF;				// Reset flag de fin de Tx

  QSPI_setBaudRate(DAC_BAUD_RATE);	// Master,16bits,DAC_QMR_BAUD Hz,CPOL=0,CPHA=0	
  
  DAC_escribeTxRAM(dato & 0xFFF);	// Escribe en TX_RAM el dato que convertirá el DAC
  DAC_escribeCommandRAM();		// Escribe en COMMAND_RAM los comandos del QSPI

  QSPI_setENDQP(1);			// Hace que el puntero ENDQP del QSPI apunte al 
					// primer comando de COMMAND_RAM 
  QSPI_activaTx; 			// Activa la Tx 
   
}

//------------------------------------------------------------------  
//                      FUNCIONES DEL ADC
//------------------------------------------------------------------  

#define ADC_BAUD_RATE 2000000			// Baudios de Tx serie del ADC (Máximo 2000000)

void ADC_escribeTxRAM(){
  mbar_writeShort(MCFSIM_QAR, QSPI_TX_RAM_START); 	// Puntero a TX_RAM
  mbar_writeShort(MCFSIM_QDR, 0x9F9F); 			// CH0,Unipolar,no-conv.diferencial,reloj externo
  mbar_writeShort(MCFSIM_QDR, 0x0000); 			// Dummy
  mbar_writeShort(MCFSIM_QDR, 0x0000);			// Dummy
}

void ADC_escribeCommandRAM(){
  mbar_writeShort(MCFSIM_QAR, QSPI_COMMAND_RAM_START);	// Puntero a COMMAND_RAM
  mbar_writeShort(MCFSIM_QDR, 0x8E00); 			// Comando Rx,CS0 continua,8 bits, SIN retardos 
  mbar_writeShort(MCFSIM_QDR, 0x8E00); 			// Comando Rx,CS0 continua,8 bits, SIN retardos 
  mbar_writeShort(MCFSIM_QDR, 0x0E00); 			// Comando Rx,CS0 no continua,8 bits, SIN retardos 
}

int ADC_leeRxRAM(){

  int dato1, dato2, datoLeido;

  mbar_writeShort(MCFSIM_QAR, QSPI_RX_RAM_START);	// Puntero a RX_RAM
  mbar_readShort(MCFSIM_QDR); 				// Se ignora el primer dato
  dato1=mbar_readShort(MCFSIM_QDR);
  dato2=mbar_readShort(MCFSIM_QDR);
  
  // El dato leído se encuentra entre dato1 y dato2 con el siguiente formato:
  //         ---- ----- ----- ---- ---- ---- ---- ----
  // dato1: |  0 | D11 | D10 | D9 | D8 | D7 | D6 | D5 |
  //         ---- ----- ----- ---- ---- ---- ---- ----
  // dato2: | D4 |  D3 |  D2 | D1 | D0 |  0 |  0 |  0 |
  //         ---- ----- ----- ---- ---- ---- ---- ---- 

  datoLeido = dato2 >> 3;	// Reconstruye el dato leído
  datoLeido += dato1 << 5;	// a partir de dato1 y dato2

  // datoLeido = (datoLeido << 1); // Para igualar la escala con el DAC (Vmax(DAC)=2.5V;Vmax(ADC)=5.00V)
 
  return datoLeido;
}

//-----------------------------------------------------
// int ADC_dato()
//
// Descripción:
//    Devuelve un dato leído del ADC
//
// Autor: Javier Guillén Álvarez
//-----------------------------------------------------
int ADC_dato()
{
  int datoLeido;
  	
  QSPI_setBaudRate(ADC_BAUD_RATE);	// Fija la veloc. de Tx para el ADC a ADC_QMR_BAUD Hz
  ADC_escribeTxRAM();		// Escribe en TX_RAM los comandos a enviar al ADC para que realice la lectura
  ADC_escribeCommandRAM();	// Escribe en COMMAND_RAM los comandos del QSPI
  QSPI_setENDQP(3);		// Hace que el puntero ENDQP del QSPI apunte al tercer comando de COMMAND_RAM 

  QSPI_activaTx;		// Activa la Tx
  while(!QSPI_finTx){} 		// Espera hasta fin de Tx (SPIF)

  QSPI_rstSPIF;			// Reset flag de fin de Tx
  
  datoLeido = ADC_leeRxRAM();	// Lee de RX_RAM el resultado de la conversión
  
  return datoLeido;
}

//------------------------------------------------------------------------------
// void ADC_test(long int datoDAC)
//
// Descripción: 
//    Compara datoDAC con el dato leído del ADC y presenta el
//    resultado en el terminal
//
// NOTA: Para realizar el test es preciso conectar la salida analógica del DAC
//       con la entrada analógica 1 del ADC.
//       La función tiene en cuenta la diferencia de fondos de escala entre el
//       DAC y el ADC (Vmax(DAC)=2.5V;Vmax(ADC)=5.00V).
//
// Autor: Javier Guillén Álvarez
//------------------------------------------------------------------------------
void ADC_test(long int datoDAC)
{  
  int datoLeido=0,errorAbs=0,errorRelat=0;
   
  datoLeido = ADC_dato();
  
  datoLeido *= 2; // Para igualar la escala con el DAC

  output(" ");
  print_number (10, 1, (long)datoLeido);
  output("\t ");
  print_number (10, 1, (long)datoDAC);
  output("\t  ");
  
  if (datoDAC > datoLeido)
     errorAbs=datoDAC-datoLeido;
  else
     errorAbs=datoLeido-datoDAC;

  print_number (10, 1, errorAbs);
  output("\t\t  ");

  if (datoDAC>0)
     errorRelat = (100 * errorAbs)/datoDAC;
  else if (datoLeido>0)
     errorRelat = (100 * errorAbs)/datoLeido;
  else
     errorRelat = 100;

  print_number (10, 1, errorRelat);
  output("%\n");
}

#endif