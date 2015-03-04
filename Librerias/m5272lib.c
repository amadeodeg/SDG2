//------------------------------------------------------------------------------
// m5272lib.c
//
//   Funciones para la plataforma de desarrollo ENT2004CF
//
// Actualizada por: Javier Guill�n �lvarez
//------------------------------------------------------------------------------

#ifndef __M5272LIB_C__
#define __M5272LIB_C__

#include "m5272lib.h"

//------------------------------------------------------------------------------
// INLINE void _exit(int status)
//
// Descripci�n: Finaliza la ejecuci�n en curso
// Entrada:     int status, c�digo de salida del programa (ignorado fuera de simulaci�n)
// Salida:      void
// Devuelve:    void
//------------------------------------------------------------------------------
INLINE void _exit(int status)
{
  asm volatile( "moveb #0,%%d1\n\t" "movel #0, %%d0\n\t" "trap #15\n\t"
                ::: "d0", "d1");
}

//------------------------------------------------------------------------------
// INLINE char inch(void)
//
// Descripci�n: lee una tecla del teclado del PC
// Entrada:     void
// Salida:      void
// Devuelve:    char, car�cter le�do
// Comentario:  El comportamiento de inch() es sin echo y puede reproducirse
//              en ANSI C
//------------------------------------------------------------------------------
INLINE char inch(void)
{
  char ch;
  asm volatile( "movel #0x10, %%d0\n\t" "trap #15\n\t" "movel %%d1,%0\n\t"
                : "=d" (ch) :
                : "d0", "d1");
  return (char) ch;
}

//------------------------------------------------------------------------------
// INLINE char inche(void)
//
// Descripci�n: lee una tecla del teclado del PC y la escribe en el terminal
// Entrada:     void
// Salida:      void
// Devuelve:    char, car�cter le�do
// Comentario:  El comportamiento de inche() es con eco y puede reproducirse
//              en ANSI C
//------------------------------------------------------------------------------
INLINE char inche(void)
{
  char ch;
  ch=inch();
  outch(ch);
  return (char) ch;
}

//------------------------------------------------------------------------------
// INLINE void outch(char ch)
//
// Descripci�n: imprime car�cteren la pantalla del PC
// Entrada:     char ch, car�cter que imprimir
// Salida:      void
// Devuelve:    void
//------------------------------------------------------------------------------
INLINE void outch(char ch)
{
  asm volatile( "moveb %0,%%d1\n\t" "movel #0x13, %%d0\n\t" "trap #15\n\t"
                : : "d" (ch)
                : "d0", "d1");
}

//------------------------------------------------------------------------------
// void outNum(UINT base, long num, UBYTE opciones)
//
// Descripci�n: 
//   Imprime en el terminal el valor de 'num' en la base indicada con o sin 
//   signo y en may�sculas o min�sculas.
//
// Entrada:     
//   UINT base, 
//     base del n�mero 'num'
//   long num,
//     n�mero a imprimir
//   UBYTE opciones,
//     Combinaci�n de los flags SIN_SIGNO y MAYUSC indicando si la impresi�n
//     es sin signo y/o en may�sculas. 
//     Valor 0 para min�sculas con signo.
//
// Modificado por: Javier Guill�n �lvarez
//------------------------------------------------------------------------------
// ALIAS para mantener compatibilidad con versiones anteriores de la biblioteca
#define print_number(base,sinSigno,num) outNum(base,num,sinSigno)

void outNum(UINT base, long num, UBYTE opciones)
{
  char* chars = "0123456789abcdef";
  char* charsMayusc = "0123456789ABCDEF";

  char *p, buf[32];
  unsigned long x;

  if (!(opciones & SIN_SIGNO) && num < 0){
      outch ('-');
      x = -num;
  }else
    x = num;

  p = buf + sizeof (buf);
  *--p = '\0';
  do{
    if(opciones & MAYUSC){
      *--p = charsMayusc[x % base];
    }else{
      *--p = chars[x % base];
    }
    x /= base;
  }while (x != 0);
  output (p);
}

//----------------------------------------------------------------------------------
// void outNumDec(UINT base, double n, UINT dec, UBYTE opciones)
//
// Descripci�n:
//   Imprime en el terminal el n�mero 'n' con 'dec' cifras
//   decimales en base 'base' con/sin signo y en may�sculas/min�sculas.
// 
// NOTA: El redondeo siempre es hacia abajo en la �ltima cifra
//
// Autor: Javier Guill�n �lvarez
//----------------------------------------------------------------------------------
// ALIAS para cuando no se especifican opciones
void outNumDec(UINT base, double n, UINT dec, UBYTE opciones)
{
  // Imprime la parte entera
  outNum(base, (int)n, opciones);  
  
  if(dec != 0){
    double dDecimal = n - (int)n;

    // Multiplica la parte decimal por 10^dec
    while(dec--){
      dDecimal *= 10;
    }

    // Imprime la marca de decimal
    outch('.');

    // Imprime 'dec' decimales
    outNum(base, (int)dDecimal, opciones);
  }
}

//------------------------------------------------------------------------------
// INLINE void output(char *start)
//
// Descripci�n: imprime un texto en la pantalla del PC
// Entrada:     char *start, texto que imprimir, terminado en 0
// Salida:      void
// Devuelve:    void
//------------------------------------------------------------------------------
INLINE void output(char *start)
{
  if (start!=0){
    int i=0;
    for (i=0; start[i]!=0; i++){
       outch(start[i]);
    }
  }
}

//------------------------------------------------------------------------------
// INLINE void retardo(UINT microsegundos) 
//
// Descripci�n: Introduce un retardo de los microsegundos indicados aproximadamente
//
// NOTA: La f�rmula de c�lculo de 'ret' proporciona un error de +-5% si
//       microsegundos >= 100. El error aumenta para tiempos menores.
//
// Autor: Javier Guill�n �lvarez
//------------------------------------------------------------------------------
INLINE void retardo(UINT microsegundos) 
{
  UINT ret = (44 * microsegundos - 32)/16;
  while(ret--);
}

//------------------------------------------------------------------------------
// INLINE LONG _strlen(char *st)
//
// Descripci�n: Calcula la longitud de una cadena de char terminada en 0
// Entrada:     char *st, puntero a la cadena de texto que medir (acabada en 0)
// Salida:      void
// Devuelve:    LONG, n�mero de caracteres de la cadena (sin contar el 0 final)
//------------------------------------------------------------------------------
INLINE LONG _strlen(char *st)
{
  LONG len = 0;
  char *pt = st;
  while (*pt++) len++;
  return len;
}

//------------------------------------------------------------------------------
// INLINE LONG memcpy(char *st)
//
// Descripci�n: Inicializa una zona de memoria con un valor determinado
// Entrada:     char *dest, char *src fuente de la informaci�n, size_t tama�o a copiar
// Salida:      void 
// Devuelve:    void puntero a la zona de memoria
//------------------------------------------------------------------------------
INLINE void *memcpy(void *dst0, const void *src0, size_t n)
{
  char* dst = (char*) dst0;
  const char* src = (const char*) src0;
  while (n--) *dst++ = *src++;
  return dst0;
}

//------------------------------------------------------------------------------
// INLINE LONG memset(char *st)
//
// Descripci�n: Sets the first num bytes pointed by buffer to the value specified by c parameter.
// Entrada:     char *buffer, int c, size_t n�mero de bytes
// Salida:      void 
// Devuelve:    void puntero a la zona de memoria
//------------------------------------------------------------------------------
INLINE void *memset(void *dst0, int c, size_t n)
{
  char* dst = (char*) dst0;
  while (n--) *dst++ = c;
  return dst0;
}

#endif