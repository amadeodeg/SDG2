
#include "m5272lib.h"
#include "megiddo.h"

static int tipoMusica=0;
//-------------------------------------------------------------------------------------------
// menuMusica()
//
// Descripci�n:
//   M�todo que saca el men� para elegir la musica (entre mp3 y ordenador).
//-------------------------------------------------------------------------------------------

char menuMusica() {
  
  char teclaPulsada;
  output("Introduzca A para musica mp3 y B para musica de ordenador.\r\n");

  desactivarMP3();	 //desactiva la m�sica por defecto
  //desactivar la musica por ordenador


  //Usamos el m�todo teclado() para ver la tecla pulsada

  
  while (TRUE) {
	teclaPulsada = teclado();
  	if (teclaPulsada == 'A'){		//opci�n MP3
   	 activarMP3();
   	 tipoMusica=1;
   	 output("Ha elegido escuchar musica mp3.\r\n");
	 break;
  	}
  	else if (teclaPulsada == 'B'){		//opci�n ordenador
    		configurarSonidoSistema();
		efectoActivo();
		tipoMusica=2;
    		output("Ha elegido escuchar musica de ordenador.\r\n");
		break;
  	}
  	else {
    		output("ERROR: Tecla no v�lida. Introducir 'A' o 'B'.\r\n");
  	}
  }
  	return teclaPulsada;

}

//-------------------------------------------------------------------------------------------
// int getTipoMusica()
//
// M�todo que devuelve el tipo de musica. Si no se ha inicializado el juego, dar� 0.
//
//-------------------------------------------------------------------------------------------
int getTipoMusica(){
  return tipoMusica;
} 
