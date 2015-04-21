#include "m5272.h"
#include "megiddo.h"
#include <string.h>
#include <stdio.h>

#define MCFSIM_UTB1                     0x14C

//------------------------------------------------------
//void enviarSMS(char* numTelefono,char* textoEnviar)
//
//Descripci�n:
//   Este m�todo se utiliza para enviar un mensaje a un	   
//   n�mero de tel�fono determinado. Para ello se 
//   utilizan las variables numTelefono y textoEnviar
//   en las cuales se debe introducir como un array de
//   tipo char el nombre telef�nico y el mensaje.
//
//   Previamente se debe inicializar el m�dulo GSM
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
//Descripci�n:
//   Envia la estad�stica calculada hasta el momento
//   de enviar el mensaje. La estad�stica se env�a al
//   n�mero de tel�fono especificado en la variable
//   numTelefono.
//
//   Se env�an tres mensajes con el n�mero de partidas
//   jugadas y la puntuaci�n obtenida por los jugadores
//   uno y dos. No se pueden mandar todos los datos
//   juntos en un SMS deb�do a que no entra en el mismo.
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
//Descripci�n:
//   Envia la estad�stica calculada hasta el momento
//   de enviar el mensaje. La estad�stica se env�a al
//   n�mero de tel�fono especificado en la variable
//   numTelefono.
//
//   Se env�an cuatro mensajes con el n�mero de partidas
//   jugadas y la puntuaci�n obtenida por los jugadores
//   uno, dos y tres. No se pueden mandar todos los datos
//   juntos en un SMS deb�do a que no entra en el mismo.
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

