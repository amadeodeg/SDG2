//------------------------------------------------------------------------------
// Cadena_GNU.c
//
//   Lee del teclado una cadena de caracteres terminada por retorno de carro y
//   la reproduce en el terminal.
//
// Autores: Juan Manuel Montero, Rubén San Segundo Y José Luis Pau
// Adaptado a C por: Javier Guillén Álvarez
//------------------------------------------------------------------------------
#include "m5272lib.c"

//------------------------------------------------------
// void getCad(char* cadena, int tamMax)
//
// Descripción:
//   Lee una cadena del teclado carácter a carácter 
//   haciendo eco en el terminal.
//
// Parámetros:
//   char* cadena
//     puntero al búfer dónde almacena la cadena leída.
//   int tamMax
//     capacidad de caracteres en cadena
//
// Autor:
//   Javier Guillén Álvarez
//------------------------------------------------------
void getCad(char* cadena, int tamMax)
{
  int i = 0;
  
  do{
    cadena[i] = inch();		// Lee un carácter sin eco

    if(cadena[i] != '\b'){	
      outch(cadena[i]);		// Imprime cualquier carácter menos '\b'
    }else{ 			
      if(i > 0){		
        outch('\b');
        i -= 2;
      }else{			// Si '\b' está en la primera posición
        i--;			// se ignora	
      }
    }
  }while((cadena[i] != '\r') && (++i < tamMax - 3));

  output("\r\n");	// Se guardan e imprimen los caracteres de 
  cadena[i++] = '\r';	// retorno de carro
  cadena[i++] = '\n';	// cambio de línea
  cadena[i]   = '\0';	// y fin de cadena
  
  return;
}  

//------------------------------------------------------
// void bucleMain(void)
//
// Descripción:
//   Función del programa principal
//
//------------------------------------------------------
#define MAX_CADENA 128	// Tamaño reservado para la cadena

void bucleMain(void)
{
  char cadena[MAX_CADENA];

  // Imprime primera parte del mensaje 
  output("INTRODUZCA UNA CADENA (MÁX: ");
  // Imprime el máximo número de caracteres que se pueden escribir
  outNum(10, MAX_CADENA - 3, 0);	// Se reservan 3 caracteres para 
		                        //  - retorno de carro ('\r')
                		        //  - nueva línea ('\n')
		                        //  - fin de cadena ('\0')
  // Imprime el final del mensaje
  output(" CARACTERES)\r\n");

  // Lee una cadena del teclado
  getCad(cadena, MAX_CADENA);

  // Imprime la cadena leída
  output(cadena);
}

//------------------------------------------------------
// void __init(void)
//
// Descripción:
//   Función por defecto de inicialización del sistema
//
//------------------------------------------------------
void __init(void) {}

//---------------------------------------------------------
// Definición de rutinas de atención a la interrupción
// Es necesario definirlas aunque estén vacías
void rutina_int1(void){}
void rutina_int2(void){}
void rutina_int3(void){}
void rutina_int4(void){}
void rutina_tout0(void){}
void rutina_tout1(void){}
void rutina_tout2(void){}
void rutina_tout3(void){}
