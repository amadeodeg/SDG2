//------------------------------------------------------------------------------
// m5272lib.c
//
//   Funciones para la plataforma de desarrollo ENT2004CF
//
// Actualizada por: Javier Guillén Álvarez
//------------------------------------------------------------------------------

#ifndef __M5272LIB_C__
#define __M5272LIB_C__

#include "m5272lib.h"

//------------------------------------------------------------------------------
// INLINE void _exit(int status)
//
// Descripción: Finaliza la ejecución en curso
// Entrada:     int status, código de salida del programa (ignorado fuera de simulación)
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
// Descripción: lee una tecla del teclado del PC
// Entrada:     void
// Salida:      void
// Devuelve:    char, carácter leído
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
// Descripción: lee una tecla del teclado del PC y la escribe en el terminal
// Entrada:     void
// Salida:      void
// Devuelve:    char, carácter leído
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
// Descripción: imprime carácteren la pantalla del PC
// Entrada:     char ch, carácter que imprimir
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
// Descripción: 
//   Imprime en el terminal el valor de 'num' en la base indicada con o sin 
//   signo y en mayúsculas o minúsculas.
//
// Entrada:     
//   UINT base, 
//     base del número 'num'
//   long num,
//     número a imprimir
//   UBYTE opciones,
//     Combinación de los flags SIN_SIGNO y MAYUSC indicando si la impresión
//     es sin signo y/o en mayúsculas. 
//     Valor 0 para minúsculas con signo.
//
// Modificado por: Javier Guillén Álvarez
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
// Descripción:
//   Imprime en el terminal el número 'n' con 'dec' cifras
//   decimales en base 'base' con/sin signo y en mayúsculas/minúsculas.
// 
// NOTA: El redondeo siempre es hacia abajo en la última cifra
//
// Autor: Javier Guillén Álvarez
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
// Descripción: imprime un texto en la pantalla del PC
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
// Descripción: Introduce un retardo de los microsegundos indicados aproximadamente
//
// NOTA: La fórmula de cálculo de 'ret' proporciona un error de +-5% si
//       microsegundos >= 100. El error aumenta para tiempos menores.
//
// Autor: Javier Guillén Álvarez
//------------------------------------------------------------------------------
INLINE void retardo(UINT microsegundos) 
{
  UINT ret = (44 * microsegundos - 32)/16;
  while(ret--);
}

//------------------------------------------------------------------------------
// INLINE LONG _strlen(char *st)
//
// Descripción: Calcula la longitud de una cadena de char terminada en 0
// Entrada:     char *st, puntero a la cadena de texto que medir (acabada en 0)
// Salida:      void
// Devuelve:    LONG, número de caracteres de la cadena (sin contar el 0 final)
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
// Descripción: Inicializa una zona de memoria con un valor determinado
// Entrada:     char *dest, char *src fuente de la información, size_t tamaño a copiar
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
// Descripción: Sets the first num bytes pointed by buffer to the value specified by c parameter.
// Entrada:     char *buffer, int c, size_t número de bytes
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