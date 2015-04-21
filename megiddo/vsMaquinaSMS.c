#include <stdio.h>
#include "m5272lib.h"
#include "m5272.h"
#include "megiddo.h"

#define MCFSIM_USR1                     0x144
#define MCFSIM_UTB1                     0x14C
#define RX_RDY                          0x01
#define JUGADOR 			1
#define POS_RADIO			71//posicion del radio en el sms
#define POS_CIRCULO			72//posicion del circulo en el sms


void eliminaMensaje(char* posicion){
	
	char buf [1024];
	sprintf (buf,"AT+CMGD=%s",posicion);
		
	recibeSerie();
	CLR_zona_datos();
}


void leeInsertaSMS(){

int fila, columna; 

   
	enviaSerie("AT+CMGR=1");
	recibeSerie();
	CLR_zona_datos();
	
	enviaSerie("AT+CMGR=1");
		
	recibeSerie2();
	fila=getRadio()-'A';
	outch(fila);
	columna=getCirculo() - '0';
	outch(columna);
	insertarDatos(fila, columna, JUGADOR);
	comeFicha(fila, columna, JUGADOR);
	getTablero();
	CLR_zona_datos();
	
	//eliminaMensaje(1);
	
}

static
void initModem (void)
{
  output("\n\nEspere un momento, conectando con el modem...\n");
		
  inicializarGSM();
  CLR_zona_datos();
  enviaSerie("AT");
  recibeSerie();
  CLR_zona_datos();
  enviaSerie("AT+CPIN=2237");
  recibeSerie();
  CLR_zona_datos();
  enviaSerie("AT+CMGF?");
  recibeSerie();
  CLR_zona_datos();
  enviaSerie("AT+CMGF=1");
  recibeSerie();
  CLR_zona_datos();
}

//-------------------------------------------------------
//
//Metodo principal del modo jugador vs maquina via SMS
//
//comprueba si hay ganador
//pide que situe la ficha en el tablero
//comprueba que esa posicion no este ocupada
//la añade al tablero y come las fichas que sean pertinentes
//imprime el tablero
//cambia el turno
//
//-------------------------------------------------------

void vsMaquinaSMS (void)
{
  char tecla;
 
  output("Pulse 1 para nivel fácil;\n 2-nivel medio;\n 3-nivel difícil\n");
  do {
    tecla = teclado();
    if (tecla>='1' && tecla<='3'){ 
      asignarNivel(tecla);
      break;
    }
    output ("pulse correctamente");

  } while (TRUE);

  limpiarTablero ();
  initJugadores ();
  initModem ();
  nuevo_jugador_persona_sms (0);
  nuevo_jugador_maquina (1);
  
  jugar ();
}
