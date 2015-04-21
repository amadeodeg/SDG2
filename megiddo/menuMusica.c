
#include "m5272lib.h"
#include "megiddo.h"

static int tipoMusica=0;
//-------------------------------------------------------------------------------------------
// menuMusica()
//
// Descripción:
//   Método que saca el menú para elegir la musica (entre mp3 y ordenador).
//-------------------------------------------------------------------------------------------

char menuMusica() {
  
  char teclaPulsada;
  output("Introduzca A para musica mp3 y B para musica de ordenador.\r\n");

  desactivarMP3();	 //desactiva la música por defecto
  //desactivar la musica por ordenador


  //Usamos el método teclado() para ver la tecla pulsada

  
  while (TRUE) {
	teclaPulsada = teclado();
  	if (teclaPulsada == 'A'){		//opción MP3
   	 activarMP3();
   	 tipoMusica=1;
   	 output("Ha elegido escuchar musica mp3.\r\n");
	 break;
  	}
  	else if (teclaPulsada == 'B'){		//opción ordenador
    		configurarSonidoSistema();
		efectoActivo();
		tipoMusica=2;
    		output("Ha elegido escuchar musica de ordenador.\r\n");
		break;
  	}
  	else {
    		output("ERROR: Tecla no válida. Introducir 'A' o 'B'.\r\n");
  	}
  }
  	return teclaPulsada;

}

//-------------------------------------------------------------------------------------------
// int getTipoMusica()
//
// Método que devuelve el tipo de musica. Si no se ha inicializado el juego, dará 0.
//
//-------------------------------------------------------------------------------------------
int getTipoMusica(){
  return tipoMusica;
} 
