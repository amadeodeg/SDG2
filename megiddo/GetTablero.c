//------------------------------------------------------------------------------
// Teclado_GNU.c
//
//   Programa ejemplo para el manejo de un teclado matricial.
//
// Autores: Juan Manuel Montero y Rubén San Segundo.
// Adaptado a C por: Javier Guillén Álvarez
//------------------------------------------------------------------------------
#include "m5272lib.h"
#include "megiddo.h"

static
void outPosicion (int fila, int columna)
{
  char ch = leerDatos (fila, columna);
  if (ch == LIBRE)
    ch = '-';
  if (ch < 10)
    ch += '1';
  outch (ch);
}

//-------------------------------------------
// getTablero
//
// metodo que obtiene el tablero de juego
// 
//-------------------------------------------

void getTablero()
{
  int i, j, f, g, h, k, l, m;

  output("La posicion actual del tablero es:\r\n\0");
  output("      A                B\r\n\r\n\0");
  //este bucle imprime la parte superior del tablero(coordenada 1 y 2)
  for (f=0; f<6; f++){
    for (g=4-f; g<12; g++){
      outch(' ');
    }		
    outPosicion (0,f);
    for(j=12-2*f;j>0;j--){	
      outch(' ');
    }	
    outPosicion(1,f);
    outch('\n');
  }
  //este bucle imprime la linea de coordenada 6
  output("F ");
  for(h=0;h<6;h++){
    outPosicion (5,h);
    outch(' ');
  }
  output("  ");
  //este bucle imprime la linea de coordena 3
  for(i=5;i>=0;i--){
    outch(' ');
    outPosicion (2,i);
	
  }
  output(" C");
  outch('\n');
  //este bucle imprime las lineas de coordenadas 4 y 5
  for(k =5;k>=0;k--){//este bucle imprime la parte superior del tablero(coordenada 1 y 2)
    for(l=k+8;l>0;l--){
      outch(' ');
    }		
    outPosicion (4,k);
    for(m=2*k;m<12;m++){	
      outch(' ');
    }	
    outPosicion (3,k);
    outch('\n');
  }
  output("\n      E                D\r\n\0");
	
}


