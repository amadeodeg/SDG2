//------------------------------------------------------------------------------
// Teclado_LCD_GNU.c
//
//   Programa ejemplo para el manejo de un teclado matricial y un LCD
//
// Autores: Juan Manuel Montero y Rubén San Segundo.
// Adaptado a C por: Javier Guillén Álvarez
//------------------------------------------------------------------------------
#include "m5272lib.c"
#include "m5272gpio.c"
#include "m5272lcd.c"

#define MAX_TECLAS 12	// Número máximo de caracteres por línea del LCD

#define NUM_FILAS 4	// Número de filas en el teclado matricial
#define NUM_COLS 4	// Número de columnas en el teclado matricial
#define EXCIT 1		// Excitación de salida bit 0

//------------------------------------------------------
// char teclado(void)
//
// Descripción:
//   Explora el teclado matricial y devuelve la tecla 
//   pulsada
//------------------------------------------------------
char teclado(void)
{
  //char tecla;
  BYTE fila, columna, fila_mask;
  static char teclas[4][4] = {{"123C"},
                              {"456D"},
                              {"789E"},
                              {"A0BF"}};
  // Bucle de exploración del teclado
  while(TRUE){

    // Excitamos una columna
    for(columna = NUM_COLS - 1; columna >= 0; columna--){
      set_puertoS(EXCIT << columna);		// Se envía la excitación de columna
      retardo(1150);				// Esperamos respuesta de optoacopladores

      // Exploramos las filas en busca de respuesta
      for(fila = NUM_FILAS - 1; fila >= 0; fila--){
        fila_mask = EXCIT << fila;		// Máscara para leer el bit de la fila actual
        if(lee16_puertoE() & fila_mask){		// Si encuentra tecla pulsada,
          while(lee16_puertoE() & fila_mask);	//   Esperamos a que se suelte
          retardo(1150);			//   Retardo antirrebotes
          return teclas[fila][columna];		//   Devolvemos la tecla pulsada
        }
      }
      // Siguiente columna
    }
    // Exploración finalizada sin encontrar una tecla pulsada
  }
  // Reiniciamos exploración
}

//------------------------------------------------------
// void __init(void)
//
// Descripción:
//   Función por defecto de inicialización del sistema
//------------------------------------------------------
void __init(void)
{
  LCD_reset();	// Reseteamos el LCD
  LCD_init();	// e inicializamos el display
}

//------------------------------------------------------
// void bucleMain(void)
//
// Descripción:
//   Función del programa principal
//------------------------------------------------------
void bucleMain(void)
{
  char tecla;

  // NOTA: Las siguientes variables son estáticas para que se mantenga su valor 
  // entre llamada y llamada a bucleMain
  static int teclasEscritas = 0;		// Nº de teclas en display
  static BOOL primeraLinea = TRUE;		// Indica si estamos en la 1ª línea
  

  // Leemos una tecla del teclado
  tecla = teclado();

  // Situamos el cursor en la posición adecuada
  if(teclasEscritas++ >= MAX_TECLAS){	// Si hemos llenado una línea,
    if(primeraLinea){			//   Si era la línea 1,
      LCD_inst(LIN_2LCD);		//     cambiamos a la línea 2
    }else{				//   Si no,
      LCD_inst(CLR_DISP);		//     Limpiamos el display
      LCD_inst(LIN_1LCD);		//     y volvemos a la línea 1
    }
    // Actualizamos variables de estado
    primeraLinea = !primeraLinea;
    teclasEscritas = 1;
  }
  LCD_dato(tecla);	// Escribimos en el display la tecla pulsada
}

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
