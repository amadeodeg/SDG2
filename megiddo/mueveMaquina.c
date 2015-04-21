#include "m5272lib.h"
#include "megiddo.h"

#define FILAS 6
#define COLUMNAS 6
#define JUGADOR '1'

static int tablero2[FILAS][COLUMNAS]; 

int aleatorio(){
  static int next = 37;
  next=(next*110452305)+12345;
  return (next/65546)%32768;
}

int nivel;

void asignarNivel(char a)
{
  nivel = a - '1';
}

void comeFicha2(int fila, int columna, int jugador);


void compruebaEspiral2(int fila, int incfila, int columna, int inccol, int jugador)
{
  //
  //Comprueba que puede comer en espiral
  //
  if ((incfila !=0) && (inccol!=0)){

    if(columna<3){

      if((leerDatos((fila+incfila)%6,(columna+inccol)%6)!=LIBRE)
	 &&(leerDatos((fila+incfila+1)%6,(columna+inccol+1)%6)!=LIBRE)
	 &&(leerDatos((fila+incfila)%6,(columna+inccol)%6)!=jugador)
	 &&(leerDatos((fila+incfila+1)%6,(columna+inccol+1)%6)!=jugador)) {
					
	tablero2[(fila+incfila)%6][(columna+inccol)%6]=jugador;
	tablero2[(fila+incfila+1)%6][(columna+inccol+1)%6]=jugador;
	comeFicha2((fila+incfila)%6,(columna+inccol)%6,jugador);
	comeFicha2((fila+incfila+1)%6,(columna+inccol+1)%6,jugador);
      }
      if((leerDatos((fila+incfila+3)%6,(columna+inccol+1)%6)!=LIBRE)
	 &&(leerDatos((fila+incfila+4)%6,(columna+inccol)%6)!=LIBRE)
	 &&(leerDatos((fila+incfila+3)%6,(columna+inccol+1)%6)!=jugador)
	 &&(leerDatos((fila+incfila+4)%6,(columna+inccol+1)%6)!=jugador)) {
				
	tablero2[(fila+incfila)%6][(columna+inccol+1)%6]=jugador;
	tablero2[(fila+incfila+1)%6][(columna+inccol)%6]=jugador;
	comeFicha2((fila+incfila)%6,(columna+inccol+1)%6,jugador);
	comeFicha2((fila+incfila+1)%6,(columna+inccol)%6,jugador);
      }
    }
	
    if(columna>2){
      if((leerDatos((fila+incfila)%6,(columna-inccol)%6)!=LIBRE)
	 &&(leerDatos((fila+incfila+1)%6,(columna-inccol-1)%6)!=LIBRE)
	 &&(leerDatos((fila+incfila)%6,(columna-inccol)%6)!=jugador)
	 &&(leerDatos((fila+incfila+1)%6,(columna-inccol-1)%6)!=jugador)){
				
	tablero2[(fila+incfila)%6][(columna-inccol)%6]=jugador;
	tablero2[(fila+incfila+1)%6][(columna-inccol-1)%6]=jugador;
	comeFicha2((fila+incfila)%6,(columna-inccol)%6,jugador);
	comeFicha2((fila+incfila+1)%6,(columna-inccol-1)%6,jugador);
      }
      if((leerDatos((fila-incfila)%6,(columna-inccol)%6)!=LIBRE)
	 &&(leerDatos((fila-incfila-1)%6,(columna-inccol-1)%6)!=LIBRE)
	 &&(leerDatos((fila-incfila)%6,(columna-inccol)%6)!=jugador)
	 &&(leerDatos((fila-incfila-1)%6,(columna-inccol-1)%6)!=jugador)){
				
	tablero2[(fila-incfila)%6][(columna-inccol)%6]=jugador;
	tablero2[(fila-incfila-1)%6][(columna-inccol-1)%6]=jugador;
	comeFicha2((fila-incfila)%6,(columna-inccol)%6,jugador);
	comeFicha2((fila-incfila-1)%6,(columna-inccol-1)%6,jugador);
      }
    }
  }

}


void compruebaCirculo2(int fila, int incfila, int columna, int inccol, int jugador)
{
  //
  //Comprueba que come en un circulo
  //
  if ((incfila !=0) && (inccol==0)){
    if((tablero2[(fila+incfila)%6][columna]!=LIBRE)
       &&(tablero2[(fila+incfila+1)%6][columna]!=LIBRE)
       &&(tablero2[(fila+incfila)%6][columna]!=jugador)
       &&(tablero2[(fila+incfila+1)%6][columna]!=jugador)){
				
      tablero2[(fila+incfila)%6][columna]=jugador;
      tablero2[(fila+incfila+1)%6][columna]=jugador;
      comeFicha2((fila+incfila)%6,columna,jugador);
      comeFicha2((fila+incfila+1)%6,columna,jugador);
    }
  }
}




void compruebaRadio2 (int fila, int incfila, 
		      int columna, int inccol, int jugador)
{
  //
  //Comprueba que come en un radio
  //
  if ((incfila ==0) && (inccol!=0)){
    if((tablero2[fila][(columna+inccol)%6]!=LIBRE)
       &&(tablero2[fila][(columna+inccol+1)%6]!=LIBRE)
       &&(tablero2[fila][(columna+inccol)%6]!=jugador)
       &&(tablero2[fila][(columna+inccol+1)%6]!=jugador)){
				
      tablero2[fila][(columna+inccol)%6]=jugador;
      tablero2[fila][(columna+inccol+1)%6]=jugador;
      comeFicha2(fila,(columna+inccol)%6,jugador);
      comeFicha2(fila,(columna+inccol+1)%6,jugador);

    }
  }

}

void comeFicha2(int fila, int columna, int jugador)
{
	
  //comprobamos si come ficha en el mismo radio
  if((columna<3)&&(tablero2[fila][columna+3]==jugador)){
    compruebaRadio2(fila,0,columna,1,jugador);	
  }
  if((columna>2)&&(tablero2[fila][columna-3]==jugador)){
    compruebaRadio2(fila,0,columna,4,jugador);
  }

  //comprobamos si come ficha en el mismo circulo
  if(tablero2[(fila+3)%6][columna]==jugador){
    compruebaCirculo2(fila,1,columna,0,jugador);
    compruebaCirculo2(fila,4,columna,0,jugador);
  }

  //comprobamos si se come ficha en espiral
  if(tablero2[(fila+3)%6][(columna+3)%6]==jugador){
    compruebaEspiral2(fila,1,columna,1,jugador);//hacia la derecha	
		
  }

}


//-------------------
//
//void rellenaTablero2(void)
//
//Hace una copia del tablero.
//
//-----------------------

void rellenaTablero2(void)
{
  int q,k;
  for(q = 0;q<6;q++){
    for(k=0;k<6;k++){
      tablero2[q][k] = leerDatos(q, k);
    }
  }
}



//------------------------------------------------------
//int exploraFila2 (i,jugador)
//
//explora que si hay seis jugadors en una columna
//------------------------------------------------------

int exploraFila2(int i,char jugador) 
{
  int num ; 
  int j;

  num = 0;
  for (j=0; j<6;j ++){
    if(tablero2[i][j] == jugador){
      num++;
    }
  }
  return num;
}

 //------------------------------------------------------
 //int exploraColumna2 (i,jugador)
 //
 //explora que si hay seis jugadors en una columna
 //------------------------------------------------------
				
int exploraColumna2(int i,char jugador) {
  int num ; 
  int j;
  num = 0;
  for (j=0; j<6;j ++){
    if(tablero2[j][i] == jugador){
      num++;
    }
  }
  return num;
}

//------------------------------------------------------
//int exploraDiagonalPpal2(i,jugador)
//
// explora las diagonalas de derecha a izquierda
//------------------------------------------------------

int exploraDiagonalPpal2(int i,char jugador)
{
  int num ; 
  int j;

  num = 0;
  for (j=0; j<6;j++){
    if(tablero2[i][j] == jugador){
      num++;
      i++;
      if(i>5)	i= 0;
    }
  }
  return num;
}

//------------------------------------------------------
//int exploraDiagonalSecundaria2(i,jugador)
//
// explora las diagonalas de derecha a izquierda
//------------------------------------------------------

int exploraDiagonalSecundaria2(int i,char jugador)
{
  int num ; 
  int j;

  num = 0;
	
  for(j=5; j>=0;j--){
    if(tablero2[i][j] == jugador){
      num++;
      i--;
      if(i<0)	i= 5;		
    }
  }
  return num;	
}

//-------------------------------------------------------------------------------------------
// ganador2()
//
// Descripción:
//   Método que comprueba si se gana.
//-------------------------------------------------------------------------------------------

BOOL ganador2(char jugador)
{
  int i;
  for (i=0; i<6; i++){
    if (exploraFila2(i,jugador) == 6) return TRUE;	
    if (exploraColumna2(i,jugador) == 6) return TRUE;
    if (exploraDiagonalPpal2(i,jugador) == 6) return TRUE;
    if (exploraDiagonalSecundaria2(i,jugador) == 6) return TRUE;
  }
  return FALSE;
}

//-------------------------
// Metodo mueveMaquina() 
//
//
//Metodo que tiene el algoritmo de movimiento de la maquina
//
//
//-------------------------

void mueveMaquina(void)
{
  static int tablero3[6][6];//tablero de referencia para comparaciones
  int nivel = 3;

  int k,w,l,m;


  //hacer una copia del tablero del jugo a tablero2 para hacer comprobaciones

  rellenaTablero2();

  //comprobar si la maquina gana

  for(w = 0;w<6;w++){
    for(k=0;k<6;k++){
      if(tablero2[w][k] == LIBRE){
	tablero2[w][k] = MAQUINA;
	comeFicha2(w, k, MAQUINA);
	if(ganador2(MAQUINA)){
	  insertarDatos(w,k,MAQUINA);
	  comeFicha(w,k,MAQUINA);
	  return;
	}
	else{
	  rellenaTablero2();
	}
				
      }
    }
  }


  //comprobar si el otro jugador puede ganar

  for(w = 0;w<6;w++){
    for(k=0;k<6;k++){
      if(tablero2[w][k] == LIBRE){
	tablero2[w][k] = JUGADOR;
	comeFicha2(w, k, JUGADOR);
	if(ganador2(JUGADOR)){
	  insertarDatos(w,k,MAQUINA);
	  comeFicha(w,k,MAQUINA);
	  return;
	}
	else{
	  rellenaTablero2();
	}
				
      }
    }
  }

  //comprobar si puede comer ficha
  if (nivel==2 || nivel==3 || (aleatorio()%2==FALSE)){
    for(w=0;w<6;w++){
      for(k=0;k<6;k++){
	tablero3[w][k] = leerDatos(w, k);
      }
    }
    for(w=0;w<6;w++){//estos dos bucles recorren el tablero en busca de un guion (casilla vacia)
      for(k=0;k<6;k++){
	if(tablero2[w][k] == LIBRE){
	  comeFicha2(w, k, MAQUINA); //intentamos comer ficha
	  //bucle que compara tablero2 con tablero3 para ver si se ha modificado
	  //comiendo ficha
	  for(l=0;l<6;l++){
	    for(m=0;m<6;m++){
	      if(tablero2[l][m]!=tablero3[l][m]){
		insertarDatos(w, k, MAQUINA);
		comeFicha(w,k,MAQUINA);
		return;
	      } 	
	    }
	  }
				
	}
      }
    }
  }
	
  if ((nivel==3) || ((nivel==2)&& (aleatorio()%2==FALSE)) ){
    //comprueba que no le pueden comer ficha
    for(w= 0;w<6;w++){//estos dos bucles recorren el tablero en busca de un guion (casilla vacia)
      for(k=0;k<6;k++){
	if(tablero2[w][k] == LIBRE){
	  comeFicha2(w, k, JUGADOR); //intentamos comer ficha
	  //bucle que compara tablero2 con tablero3 para ver si se ha modificado
	  //comiendo ficha
	  for(l=0;l<6;l++){
	    for(m=0;m<6;m++){
	      if(tablero2[l][m]!=tablero3[l][m]){
		insertarDatos(w, k, MAQUINA);
		comeFicha(w,k,MAQUINA);
		return;
	      }	
	    }
	  }
				
	}
      }
    }
  }
  //si no, mover aleatoriamente, primer guion que se encuentre
  for(w= 0;w<6;w++){
    for(k=0;k<6;k++){
      if(tablero2[w][k] == LIBRE){
	insertarDatos(w, k,MAQUINA);
	return;
      }	
    }
  }
}




