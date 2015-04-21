#include "megiddo.h"

//------------------------------------------------------
//int exploraFila (i,jugador)
//
//explora que si hay seis jugadors en una columna
//------------------------------------------------------

int exploraFila1(i,jugador) 
{
  int num = 0; 
  int j;

  for (j=0; j<6;j ++){
    if(leerDatos(i,j) == jugador){
      num++;
    }
  }return num;
}

//------------------------------------------------------
//int exploraColumna (i,jugador)
//
//explora que si hay seis jugadors en una columna
//------------------------------------------------------
				
int exploraColumna1(i,jugador) 
{
  int num = 0; 
  int j;

  for (j=0; j<6;j ++){
    if(leerDatos(j,i) == jugador){
      num++;
    }
  }return num;
}

//------------------------------------------------------
//int exploraDiagonalPpal(i,jugador)
//
// explora las diagonalas de derecha a izquierda
//------------------------------------------------------

int exploraDiagonalPpal1(i, jugador)
{
  int num = 0; 
  int j;

  for (j=0; j<6;j++){
    if(leerDatos(i,j) == jugador){
      num++;
      i++;
      if(i>5)	i= 0;
    }
  }
  return num;
}

//------------------------------------------------------
//int exploraDiagonalSecundaria(i,jugador)
//
// explora las diagonalas de derecha a izquierda
//------------------------------------------------------

int exploraDiagonalSecundaria1(i, jugador)
{
  int num = 0; 
  int j;
	
  for(j=5; j>=0;j--){
    if(leerDatos(i,j) == jugador){
      num++;
      i--;
      if (i<0)
	i= 5;		
    }
  }
  return num;	
}

//-------------------------------------------------------------------------------------------
// ganador()
//
// Descripción:
//   Método que comprueba si se gana.
//-------------------------------------------------------------------------------------------

void busca_megiddos (int jugador)
{
  struct jugador_t* j = getJugador(jugador);
  int i;

  j->megiddos = 0;
  for (i=0; i<6; i++){
    if (exploraFila1(i,jugador) == 6) j->megiddos++;	
    if (exploraColumna1(i,jugador) == 6) j->megiddos++;
    if (exploraDiagonalPpal1(i,jugador) == 6) j->megiddos++;
    if (exploraDiagonalSecundaria1(i,jugador) == 6) j->megiddos++;
  }
  if (j->megiddos == 0) return;
  switch (j->megiddos){
  case 1:
    getJugador(jugador)->contPuntos +=6;
    break; 
  case 2:
    getJugador(jugador)->contPuntos += 18;
    break;
  case 3:
    getJugador(jugador)->contPuntos += 30;
    break;
  default:
    getJugador(jugador)->contPuntos += 36;
    return;
  }
}
	
int contadorFichasComidas(int jugador)
{
  struct jugador_t* j = getJugador(jugador);
  j->fichasComidas += 2;

  return j->fichasComidas;
}


BOOL total_ganado (int jugador) 
{
  struct jugador_t* j = getJugador(jugador);
  if (j->contPuntos >= 36)
    return TRUE;
  return FALSE;  
}

BOOL juego_ganado (int jugador) 
{
  struct jugador_t* j = getJugador(jugador);
  if (j->fichasComidas >= 6)
    return TRUE;
  if (j->megiddos > 0)
    return TRUE;
  return FALSE;  
}
