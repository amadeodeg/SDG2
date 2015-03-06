//------------------------------------------------------------------------------
// Cadena_GNU.c
//
//   Lee del teclado una cadena de caracteres terminada por retorno de carro y
//   la reproduce en el terminal.
//
// Autores: Juan Manuel Montero, Rub�n San Segundo Y Jos� Luis Pau
// Adaptado a C por: Javier Guill�n �lvarez
//------------------------------------------------------------------------------
#include "m5272lib.c"

//------------------------------------------------------
// void getCad(char* cadena, int tamMax)
//
// Descripci�n:
//   Lee una cadena del teclado car�cter a car�cter 
//   haciendo eco en el terminal.
//
// Par�metros:
//   char* cadena
//     puntero al b�fer d�nde almacena la cadena le�da.
//   int tamMax
//     capacidad de caracteres en cadena
//
// Autor:
//   Javier Guill�n �lvarez
//------------------------------------------------------
void getCad(char* cadena, int tamMax)
{
  int i = 0;
  
  do{
    cadena[i] = inch();		// Lee un car�cter sin eco

    if(cadena[i] != '\b'){	
      outch(cadena[i]);		// Imprime cualquier car�cter menos '\b'
    }else{ 			
      if(i > 0){		
        outch('\b');
        i -= 2;
      }else{			// Si '\b' est� en la primera posici�n
        i--;			// se ignora	
      }
    }
  }while((cadena[i] != '\r') && (++i < tamMax - 3));

  output("\r\n");	// Se guardan e imprimen los caracteres de 
  cadena[i++] = '\r';	// retorno de carro
  cadena[i++] = '\n';	// cambio de l�nea
  cadena[i]   = '\0';	// y fin de cadena
  
  return;
}  

//------------------------------------------------------
// void bucleMain(void)
//
// Descripci�n:
//   Funci�n del programa principal
//
//------------------------------------------------------
#define MAX_CADENA 128	// Tama�o reservado para la cadena

void bucleMain(void)
{
  char cadena[MAX_CADENA];

  // Imprime primera parte del mensaje 
  output("INTRODUZCA UNA CADENA (M�X: ");
  // Imprime el m�ximo n�mero de caracteres que se pueden escribir
  outNum(10, MAX_CADENA - 3, 0);	// Se reservan 3 caracteres para 
		                        //  - retorno de carro ('\r')
                		        //  - nueva l�nea ('\n')
		                        //  - fin de cadena ('\0')
  // Imprime el final del mensaje
  output(" CARACTERES)\r\n");

  // Lee una cadena del teclado
  getCad(cadena, MAX_CADENA);

  // Imprime la cadena le�da
  output(cadena);
}

//------------------------------------------------------
// void __init(void)
//
// Descripci�n:
//   Funci�n por defecto de inicializaci�n del sistema
//
//------------------------------------------------------
void __init(void) {}

//---------------------------------------------------------
// Definici�n de rutinas de atenci�n a la interrupci�n
// Es necesario definirlas aunque est�n vac�as
void rutina_int1(void){}
void rutina_int2(void){}
void rutina_int3(void){}
void rutina_int4(void){}
void rutina_tout0(void){}
void rutina_tout1(void){}
void rutina_tout2(void){}
void rutina_tout3(void){}
