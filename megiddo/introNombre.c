#include "m5272lib.h"
#include "megiddo.h"
#include <string.h>

//definimos las constantes para cada una de las teclas del teclado matricial
static char* teclas[] = {
  /*1*/ ".,!?1",
  /*2*/ "ABC2",
  /*3*/ "DEF3",
  /*4*/ "GHI4",
  /*5*/ "JKL5",
  /*6*/ "MNOÑ6",
  /*7*/ "PQRS7",
  /*8*/ "TUV8",
  /*9*/ "WXYZ9",
};
 
//metodo para la introduccion del nombre del jugador.devuelve una cadena de caracteres con el nombre del jugador
char* introNombre (void)
{
  static char nombre[20];
  int pos_nombre = 0;
  char* tecla = 0;
  int contador = 0;
  int pos_tecla = 0;
  
  //reinicia el array de nombre.
  memset (nombre, 0, sizeof(nombre));
  

  output("INTRODUZCA EL NOMBRE DEL JUGADOR:\r\n");
  output("Pulse A para avanzar, B para borrar , E para espacio y\
 las teclas del 1 al 9 funcionan con los mismos caracteres que un telefono movil\r\n");
  output("Una vez introducido el nombre completo, pulse F para terminar\r\n");
  while (1) {
    int i = 0;
    char c = teclado();

    if ((c >= '1') && (c <= '9')) {
      if (tecla == teclas[c - '1']) { // repetida
	output("\b");
	pos_tecla = (pos_tecla + 1) % strlen(tecla);
      }
      else { // primera vez
	tecla = teclas[c - '1'];
	pos_tecla = 0;
      }
      
      nombre[pos_nombre] = tecla[pos_tecla];
      outch(tecla[pos_tecla]);
      
      //retardo(2000);
      continue;
    }
    //switch para los casos en los que la tecla pulsada no es ninguno de los 9 digitos que introduce una letra, numero o simbolo
    switch (c) {
      //tecla avanzar.cada vez que se quiere poner una nueva letra hay que pulsarla .   
    case 'A':
      tecla = 0;
      contador ++;
      pos_nombre ++;
      break;
      //tecla borrar.retrocede a la anterior letra en el caso de que se quiera cambiar.
    case 'B':
      output("\b");
      pos_tecla = 0;
      pos_nombre -- ;
      break;
      //tecla espacio
    case 'E':
      nombre[pos_nombre++] = ' ';
      break;
      //tecla fin.se pulsa cuando el nombre esta completo.
    case 'F'  :
      contador ++;
      for (i=0; i<contador; i++){
         output("\b");
         continue;
      }
      return nombre;
    }
  
  }
}

