//------------------------------------------------------------------------------
// m5272lib.h
//
//   Definición de tipos y declaración de funciones para la plataforma de 
//   desarrollo ENT2004CF
//
// Actualizada por: Javier Guillén Álvarez
//------------------------------------------------------------------------------

#ifndef __M5272LIB_H__
#define __M5272LIB_H__

//------------------------------------------------------------------
//                       DEFINICIÓN DE TIPOS
//------------------------------------------------------------------
typedef enum {TRUE=1, FALSE=0} BOOL;		// Tipo binario TRUE=1, FALSE=0

typedef enum {IMPAR=1, PAR=0} PAR_IMPAR;	// Para distinguir interrupciones pares(0) e impares(1)

typedef signed char BYTE;			// Tipo de una variable que ocupa 1 byte con signo
typedef unsigned char UBYTE;			// Tipo de una variable que ocupa 1 byte sin signo
typedef signed short int WORD;			// Tipo de una variable que ocupa 2 bytes con signo
typedef unsigned short int UWORD;		// Tipo de una variable que ocupa 2 bytes sin signo
typedef signed long int LONG;			// Tipo de una variable que ocupa 4 bytes con signo
typedef unsigned long int ULONG;		// Tipo de una variable que ocupa 4 bytes sin signo
typedef unsigned int UINT;			// Tipo de una variable que ocupa 4 bytes sin signo

//------------------------------------------------------------------
//                       DEFINICIÓN DE MACROS
//------------------------------------------------------------------
#define INLINE
#define SIN_SIGNO 1	// Flag para las funciones outNum y outNumDec
#define MAYUSC    2	// Flag para las funciones outNum y outNumDec

#define RET_1S		1000000		// Constante para un retardo de 1seg. aprox. en retardo()
#define RET_15MS        15000		// Constante para un retardo de 15ms aprox. en retardo()
#define RET_3MS		3000		// Constante para un retardo de 3ms aprox. en retardo()

// Permite acceder al contenido de la dirección de memoria 'dir'
#define ACCESO_A_MEMORIA_LONG(dir) (*(ULONG *)(dir))

// Instrucción BSET en ensamblador para poner a 1 un bit de un byte de memoria
#define bsetb(bit,mem) __asm__ __volatile__ ("bset.b %0,%1"::"n"(bit),"m"(mem))

// Instrucción BCLR en ensamblador para poner a 0 un bit de un byte de memoria
#define bclrb(bit,mem) __asm__ __volatile__ ("bclr.b %0,%1"::"n"(bit),"m"(mem))

// Instrucción BSET en ensamblador para poner a 1 un bit de 4 bytes de memoria
#define bsetl(bit,mem) __asm__ __volatile__ ("moveal %1,%%a0\n\t" "move.l (%%a0),%%d0\n\t" "bset.l %0,%%d0\n\t" "move.l %%d0,(%%a0)\n\t"::"n"(bit),"m"(mem):"d0", "memory", "a0")

// Instrucción BCLR en ensamblador para poner a 0 un bit de 4 bytes de memoria
#define bclrl(bit,mem) __asm__ __volatile__ ("moveal %1,%%a0\n\t" "move.l (%%a0),%%d0\n\t" "bclr.l %0,%%d0\n\t" "move.l %%d0,(%%a0)\n\t"::"n"(bit),"m"(mem):"d0", "memory", "a0")

// Desahabilita las interrupciones
#define cli() __asm__ __volatile__ ( "move.w %%sr, %%d0 \n\t ori.l #0x0700,%%d0 \n\t move.w %%d0, %%sr \n\t" : : : "d0", "memory")

// Finaliza la ejecución en curso
#define exit(status) _exit(status)

// Habilita las interrupciones
#define sti() asm volatile ( "move.w %%sr, %%d0 \n\t andi.l #0xF8FF,%%d0 \n\t move.w %%d0, %%sr \n\t" : : : "d0", "memory")

//------------------------------------------------------------------
//       DECLARACIÓN DE FUNCIONES IMPLEMENTADAS EN m5272lib.c
//------------------------------------------------------------------
// Finaliza la ejecución en curso
INLINE void _exit(int status);

// Lee tecla del teclado del PC sin eco
INLINE char inch(void);

// Lee tecla con eco en el terminal
INLINE char inche(void);

// Escribe el carácter ch
INLINE void outch(char ch);

// Imprime en el terminal el valor de 'num' en la base indicada 
void outNum(UINT base, long num, UBYTE opciones);

// Imprime en el terminal el número 'n' con 'dec' cifras decimales
void outNumDec(UINT base, double n, UINT dec, UBYTE opciones);

// Escribe la cadena ASCIIZ que empieza en start
INLINE void output(char *start);

// Introduce aprox. el retardo expresado en microsegundos
INLINE void retardo(UINT microsegundos); 

// Devuelve longitud de cadena 
INLINE LONG _strlen(char *st);

extern void _prep_TOUT0(void);
extern void _prep_TOUT1(void);
extern void _prep_TOUT2(void);
extern void _prep_TOUT3(void);
extern void _prep_TIN0(void);
extern void _prep_INT3(void);
extern void _prep_INT2(void);
extern void _prep_INT1(void);

#endif
