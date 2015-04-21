#include "m5272.h"
#include "megiddo.h"
#include <string.h>
#include <stdio.h>

#define MCFSIM_UTB1                     0x14C

//------------------------------------------------------
//void enviarSMS(char* numTelefono,char* textoEnviar)
//
//Descripción:
//   Este método se utiliza para enviar un mensaje a un	   
//   número de teléfono determinado. Para ello se 
//   utilizan las variables numTelefono y textoEnviar
//   en las cuales se debe introducir como un array de
//   tipo char el nombre telefónico y el mensaje.
//
//   Previamente se debe inicializar el módulo GSM
//   correctamente y pasar a MODO TEXTO.
//------------------------------------------------------

void enviarSMS(char* numTelefono,char* textoEnviar)
{
	char buf [1024];
	sprintf (buf, "AT+CMGS=\"%s\"",numTelefono );

	enviaSerie(buf);
	recibeSerie();
	CLR_zona_datos();

	enviaSerie(textoEnviar);
	mbar_writeByte(MCFSIM_UTB1,0x01A);	//caracter de confirmacion
	recibeSerie();
	CLR_zona_datos();


}

//------------------------------------------------------
//void enviarEstadisticaSMSDosJugadores(char* numTelefono)
//
//Descripción:
//   Envia la estadística calculada hasta el momento
//   de enviar el mensaje. La estadística se envía al
//   número de teléfono especificado en la variable
//   numTelefono.
//
//   Se envían tres mensajes con el número de partidas
//   jugadas y la puntuación obtenida por los jugadores
//   uno y dos. No se pueden mandar todos los datos
//   juntos en un SMS debído a que no entra en el mismo.
//   Por coherencia se dividen en tres.
//------------------------------------------------------

void enviarEstadisticaSMSDosJugadores(char* numTelefono)
{
	char buf1 [1024];
	char buf2 [1024];
	char buf3 [1024];

	sprintf (buf1, " N Partidas=\"%d\"",getNumPartidas());
	sprintf (buf2, ";N Punt J1=\"%d\"",getPuntos(1));
	sprintf (buf3, ";N Punt J2=\"%d\"",getPuntos(2));
	
	enviarSMS(numTelefono,buf1);
	enviarSMS(numTelefono,buf2);
	enviarSMS(numTelefono,buf3);
}

//------------------------------------------------------
//void enviarEstadisticaSMSTresJugadores(char* numTelefono)
//
//Descripción:
//   Envia la estadística calculada hasta el momento
//   de enviar el mensaje. La estadística se envía al
//   número de teléfono especificado en la variable
//   numTelefono.
//
//   Se envían cuatro mensajes con el número de partidas
//   jugadas y la puntuación obtenida por los jugadores
//   uno, dos y tres. No se pueden mandar todos los datos
//   juntos en un SMS debído a que no entra en el mismo.
//   Por coherencia se dividen en cuatro mensajes.
//------------------------------------------------------

void enviarEstadisticaSMSTresJugadores(char* numTelefono)
{
	char buf1 [1024];
	char buf2 [1024];
	char buf3 [1024];
	char buf4 [1024];

	sprintf (buf1, " N Partidas=\"%d\"",getNumPartidas());
	sprintf (buf2, ";N Punt J1=\"%d\"",getPuntos(1));
	sprintf (buf3, ";N Punt J2=\"%d\"",getPuntos(2));
	sprintf (buf4, ";N Punt J3=\"%d\"",getPuntos(3));

	enviarSMS(numTelefono,buf1);
	enviarSMS(numTelefono,buf2);
	enviarSMS(numTelefono,buf3);
	enviarSMS(numTelefono,buf4);
}

