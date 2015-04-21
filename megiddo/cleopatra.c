#include "m5272lib.h" 
#include "megiddo.h" 
 
static int cleopatrilla;

void cleopatra(int fila, int columna, int jugador) 
{
  //explora por COLUMNA

  if (((leerDatos((fila),columna+1)==jugador) || (leerDatos((fila),columna-1)==jugador)) && (columna > 1) && (columna < 4)){ 

    //puede que haya cleopatra. 


    if(leerDatos((fila),columna+1)==jugador){ 


      if((leerDatos((fila),columna+2)!=jugador) && (leerDatos((fila),columna+2)!=LIBRE) && (leerDatos((fila),columna-1)!=jugador) && (leerDatos((fila),columna-1)!=LIBRE)){ 

	//hay cleopatra 
	contadorFichasComidas(jugador);
	insertarDatos((fila),(columna+2),jugador);
	insertarDatos((fila),(columna-1),jugador);

      }

    }


    if(leerDatos((fila),columna-1)==jugador){ 


      if((leerDatos((fila),columna-2)!=jugador) && (leerDatos((fila),columna-2)!=LIBRE) && (leerDatos((fila),columna+1)!=jugador) && (leerDatos((fila),columna+1)!=LIBRE)){ 

	//hay cleopatra 

	contadorFichasComidas(jugador); 
	insertarDatos((fila),(columna-2),jugador);
	insertarDatos((fila),(columna+1),jugador);

      }

    }

  }


  //explora por CIRCULO
		
  if (((leerDatos((fila+1)%6,columna)==jugador) || (leerDatos((fila-1)%6,columna)==jugador))){ 

    //puede que haya cleopatra. 

    if(leerDatos((fila+1)%6,(columna))==jugador){ 

			
      if((leerDatos((fila+2)%6,(columna))!=jugador) && (leerDatos((fila+2)%6,(columna))!=LIBRE) && (leerDatos((fila-1)%6,(columna))!=jugador) && (leerDatos((fila-1)%6,(columna))!=LIBRE)){ 

	//hay cleopatra 
	contadorFichasComidas(jugador); 
	insertarDatos(((fila+2)%6),(columna),jugador);
	insertarDatos(((fila-1)%6),(columna),jugador);

      }

    }


    if(leerDatos((fila-1)%6,(columna))==jugador){ 


      if((leerDatos((fila-2)%6,(columna))!=jugador) && (leerDatos((fila-2)%6,(columna))!=LIBRE) && (leerDatos((fila+1)%6,(columna))!=jugador) && (leerDatos((fila+1)%6,(columna))!=LIBRE) ){ 

	//hay cleopatra 
	contadorFichasComidas(jugador); 
	insertarDatos((fila-2)%6,(columna),jugador);
	insertarDatos((fila+1)%6,(columna),jugador);

      }

    }
  }
	
	
  //exploramos diagonales derechas /
	
	
	
	
  if (((leerDatos((fila-1)%6,(columna+1)%6) ==jugador) || (leerDatos((fila+1)%6,(columna-1)%6)==jugador))){ 
	
    if(leerDatos((fila-1)%6,(columna+1)%6)==jugador){ 
		
      if((leerDatos((fila+1)%6,(columna-1)%6)!=jugador) && (leerDatos((fila+1)%6,(columna-1)%6)!=LIBRE) && (leerDatos((fila-2)%6,(columna+2)%6)!=jugador) && (leerDatos((fila-2)%6,(columna+2)%6)!=LIBRE)){ 

	//hay cleopatra 
	contadorFichasComidas(jugador); 
	insertarDatos((fila+1)%6,(columna-1)%6,jugador);
	insertarDatos((fila-2)%6,(columna+2)%6,jugador);

      }

		
		
    }
		
    if(leerDatos((fila+1)%6,(columna-1)%6)==jugador){ 


      if((leerDatos((fila-1)%6,(columna+1)%6)!=jugador) && (leerDatos((fila-1)%6,(columna+1)%6)!=LIBRE) && (leerDatos((fila+2)%6,(columna-2)%6)!=jugador) && (leerDatos((fila+2)%6,(columna-2)%6)!=LIBRE) ){ 

	//hay cleopatra 
	contadorFichasComidas(jugador); 
	insertarDatos((fila-1)%6,(columna+1)%6,jugador);
	insertarDatos((fila+2)%6,(columna-2)%6,jugador);

      }

    }

	
	
  }

	
	
  //exploramos diagonales izquierdas
  if (((leerDatos(((fila-1)%6),(columna-1)%6)==jugador) || (leerDatos(((fila+1)%6),(columna+1)%6)==jugador))){ 
	
    if(leerDatos((fila+1)%6,((columna+1)%6))==jugador){ 

		
      if((leerDatos((fila-1)%6,((columna-1)%6))!=jugador) && (leerDatos((fila-1)%6,((columna-1)%6))!=LIBRE) && (leerDatos((fila+2)%6,((columna+2)%6))!=jugador) && (leerDatos((fila+2)%6,((columna+2)%6))!=LIBRE)){ 

	//hay cleopatra 
	contadorFichasComidas(jugador); 
	insertarDatos(((fila-1)%6),((columna-1)%6),jugador);
	insertarDatos(((fila+2)%6),((columna+2)%6),jugador);

      }

		
		
    }
		
    if(leerDatos((fila-1)%6,((columna-1)%6))==jugador){ 


      if((leerDatos((fila+1)%6,((columna+1)%6))!=jugador) && (leerDatos((fila+1)%6,((columna+1)%6))!=LIBRE) && (leerDatos((fila-2)%6,((columna-2)%6))!=jugador) && (leerDatos((fila-2)%6,(columna-2)%6)!=LIBRE)){ 

	//hay cleopatra 
	contadorFichasComidas(jugador); 
	insertarDatos((fila+1)%6,((columna+1)%6),jugador);
	insertarDatos((fila-2)%6,((columna-2)%6),jugador);

      }
    }
  }
}


void setCleopatra (int selec)
{
  cleopatrilla = selec;
}

int getCleopatra (void)
{
  return cleopatrilla;
}
