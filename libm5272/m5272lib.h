
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

#define RET_1S		1000000		// Constante para un retardo de 1seg. aprox. en retardo()
#define RET_15MS        15000		// Constante para un retardo de 15ms aprox. en retardo()
#define RET_3MS		3000		// Constante para un retardo de 3ms aprox. en retardo()

#define ACCESO_A_MEMORIA_LONG(dir) (*(ULONG *)(dir))

// Desahabilita las interrupciones
#ifndef cli
#define cli() __asm__ __volatile__ ( "move.w %%sr, %%d0 \n\t ori.l #0x0700,%%d0 \n\t move.w %%d0, %%sr \n\t" : : : "d0", "memory")
#endif

// Habilita las interrupciones
#ifndef sti
#define sti() asm volatile ( "move.w %%sr, %%d0 \n\t andi.l #0xF8FF,%%d0 \n\t move.w %%d0, %%sr \n\t" : : : "d0", "memory")
#endif

#endif
