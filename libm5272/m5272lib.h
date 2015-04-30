
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

#define ACCESO_A_MEMORIA_LONG(dir) (*(ULONG *)(dir))

#endif
