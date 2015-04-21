#include "m5272lib.h"
#include "megiddo.h"



void comeFicha(int fila, int columna, int jugador);



/**
**Metodo comprueba
**
**A este metodo se llama cuando se cumple la condicion de que tres posiciones mas alla de nuestra ficha (en cualquier direccion)
**hay una ficha nuestra.
**Comprueba que a partir de la posicion a la que se pretende mover, busca que en las dos posiciones siguientes
**(hacia la derecha, izquierda, arriba, abajo, diagonales) las fichas que hay son del contrario(y no estan vacias),
**si se cumple esa condicion, se comen esas fichas y despues se comprueba si ese suceso provoca una nueva situacion
**para comer
**
**/

void compruebaEspiral (int fila, int incfila, 
		       int columna, int inccol, 
		       int jugador)
{
  //
  //Comprueba que puede comer en espiral 
  //
  if ((incfila !=0) && (inccol!=0)){
    if(columna<3){

      if((leerDatos((fila+incfila)%6,(columna+inccol)%6)!=LIBRE)
	 &&(leerDatos((fila+incfila+1)%6,(columna+inccol+1)%6)!=LIBRE)
	 &&(leerDatos((fila+incfila)%6,(columna+inccol)%6)!=jugador)
	 &&(leerDatos((fila+incfila+1)%6,(columna+inccol+1)%6)!=jugador)){
				
	contadorFichasComidas(jugador); 
			
	insertarDatos((fila+incfila)%6,(columna+inccol)%6,jugador);
	insertarDatos((fila+incfila+1)%6,(columna+inccol+1)%6,jugador);
	comeFicha((fila+incfila)%6,(columna+inccol)%6,jugador);
	comeFicha((fila+incfila+1)%6,(columna+inccol+1)%6,jugador);
      }
      if((leerDatos((fila+incfila+3)%6,(columna+inccol+1)%6)!=LIBRE)
	 &&(leerDatos((fila+incfila+4)%6,(columna+inccol)%6)!=LIBRE)
	 &&(leerDatos((fila+incfila+3)%6,(columna+inccol+1)%6)!=jugador)
	 &&(leerDatos((fila+incfila+4)%6,(columna+inccol+1)%6)!=jugador)){
				
	contadorFichasComidas(jugador); 
				
	insertarDatos((fila+incfila+3)%6,(columna+inccol+1)%6,jugador);
	insertarDatos((fila+incfila+4)%6,(columna+inccol)%6,jugador);
	comeFicha((fila+incfila+3)%6,(columna+inccol+1)%6,jugador);
	comeFicha((fila+incfila+4)%6,(columna+inccol)%6,jugador);
      }
    }
	
    if(columna>2){
      if((leerDatos((fila+incfila)%6,(columna-inccol)%6)!=LIBRE)
	 &&(leerDatos((fila+incfila+1)%6,(columna-inccol-1)%6)!=LIBRE)
	 &&(leerDatos((fila+incfila)%6,(columna-inccol)%6)!=jugador)
	 &&(leerDatos((fila+incfila+1)%6,(columna-inccol-1)%6)!=jugador)){
						
	contadorFichasComidas(jugador); 
				
	insertarDatos((fila+incfila)%6,(columna-inccol)%6,jugador);
	insertarDatos((fila+incfila+1)%6,(columna-inccol-1)%6,jugador);
	comeFicha((fila+incfila)%6,(columna-inccol)%6,jugador);
	comeFicha((fila+incfila+1)%6,(columna-inccol-1)%6,jugador);
      }
      if((leerDatos((fila-incfila)%6,(columna-inccol)%6)!=LIBRE)
	 &&(leerDatos((fila-incfila-1)%6,(columna-inccol-1)%6)!=LIBRE)
	 &&(leerDatos((fila-incfila)%6,(columna-inccol)%6)!=jugador)
	 &&(leerDatos((fila-incfila-1)%6,(columna-inccol-1)%6)!=jugador)){
						
	contadorFichasComidas(jugador); 
				
	insertarDatos((fila-incfila)%6,(columna-inccol)%6,jugador);
	insertarDatos((fila-incfila-1)%6,(columna-inccol-1)%6,jugador);
	comeFicha((fila-incfila)%6,(columna-inccol)%6,jugador);
	comeFicha((fila-incfila-1)%6,(columna-inccol-1)%6,jugador);
      }
    }
  }

}




void compruebaCirculo(int fila, int incfila, int columna, int jugador)
{
	
//
//Comprueba que come en un circulo
//
	if((leerDatos((fila+incfila)%6,columna)!=LIBRE)
		 &&(leerDatos((fila+incfila+1)%6,columna)!=LIBRE)
		 	&&(leerDatos((fila+incfila)%6,columna)!=jugador)
		 		&&(leerDatos((fila+incfila+1)%6,columna)!=jugador)){	

		contadorFichasComidas(jugador);
		 				
	      insertarDatos((fila+incfila)%6,columna,jugador);
	      insertarDatos((fila+incfila+1)%6,columna,jugador);
	      comeFicha((fila+incfila)%6,columna,jugador);
	      comeFicha((fila+incfila+1)%6,columna,jugador);

}}

void compruebaRadio(int fila, int columna, int inccol, int jugador){

//
//Comprueba que come en un radio
//
	if((leerDatos(fila,(columna+inccol)%6)!=LIBRE)
		&&(leerDatos(fila,(columna+inccol+1)%6)!=LIBRE)
			&&(leerDatos(fila,(columna+inccol)%6)!=jugador)
				&&(leerDatos(fila,(columna+inccol+1)%6)!=jugador)){
				
		contadorFichasComidas(jugador); 
						
	      insertarDatos(fila,(columna+inccol)%6,jugador);
	      insertarDatos(fila,(columna+inccol+1)%6,jugador);
	      comeFicha(fila,(columna+inccol)%6,jugador);
	      comeFicha(fila,(columna+inccol+1)%6,jugador);

}
}



void comeFicha(int fila, int columna, int jugador)
{
	
  //comprobamos si come ficha en el mismo radio
  if((columna<3)&&(leerDatos(fila,columna+3)==jugador)){
	compruebaRadio(fila,columna,1,jugador);	
  }
  if((columna>2)&&(leerDatos(fila,columna-3)==jugador)){
	compruebaRadio(fila,columna,4,jugador);
  }

  //comprobamos si come ficha en el mismo circulo
  if(leerDatos((fila+3)%6,columna)==jugador){
	compruebaCirculo(fila,1,columna,jugador);
	compruebaCirculo(fila,4,columna,jugador);
  }

  //comprobamos si se come ficha en espiral
  if(leerDatos((fila+3)%6,(columna+3)%6)==jugador){
	
	compruebaEspiral(fila,1,columna,1,jugador);//sentencia que comprueba todas las posibles espirales en un sentido
					    // y otro
		
	
  }

}
