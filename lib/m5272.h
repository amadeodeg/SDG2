/****************************************************************************/
/*
 *	m5272.h -- Motorola Coldfire 5272 Support
 *
 *	(C) Copyright 2001, Key Technology (http://www.keyww.com)
 */

/****************************************************************************/
#ifndef	m5272_h
#define	m5272_h
/****************************************************************************/


/*
 *	Define master clock frequency of our 5272.
 */

#define	MCF_CLK		66000000

/*
 * Place to put internal registers
 */

#define	MCF_MBAR	0x10000000
#define mbar_readLong(x)	*((volatile unsigned long *) (MCF_MBAR + x))
#define mbar_writeLong(x,y)	*((volatile unsigned long *) (MCF_MBAR + x)) = y
#define mbar_readShort(x)	*((volatile unsigned short *) (MCF_MBAR + x))
#define mbar_writeShort(x,y)	*((volatile unsigned short *) (MCF_MBAR + x)) = y
#define mbar_readByte(x)	*((volatile unsigned char *) (MCF_MBAR + x))
#define mbar_writeByte(x,y)	*((volatile unsigned char *) (MCF_MBAR + x)) = y

/* Rutinas de I/O de memoria */
#define escribe_byte(x,y)       *((volatile unsigned char *) x) = y
#define lee_byte(x)             *((volatile unsigned char *) x)
#define escribe_word(x,y)       *((volatile unsigned short int *) x) = y
#define lee_word(x)             *((volatile unsigned short int *) x)
#define escribe_long(x,y)       *((volatile unsigned long int *) x) = y 
#define lee_long(x)             *((volatile unsigned long int *) x)

/*
 * Size of internal RAM
 */

#define INT_RAM_SIZE 4096

/*
 *	Define the 5272 SIM register set addresses.
 */
#define	MCFSIM_SCR		0x04		/* System Configuration */
#define	MCFSIM_SPR		0x06		/* System Protection */
#define	MCFSIM_ICR1		0x20		/* Intr Ctrl reg 1 (r/w) */
#define	MCFSIM_ICR2		0x24		/* Intr Ctrl reg 2 (r/w) */
#define	MCFSIM_ICR3		0x28		/* Intr Ctrl reg 3 (r/w) */
#define	MCFSIM_ICR4		0x2c		/* Intr Ctrl reg 4 (r/w) */

#define	MCFSIM_PITR			0x34		/* Programmable Interrupt Transition */
#define	MCFSIM_PIWR			0x38		/* Programmable Interrupt Wakeup */
#define	MCFSIM_PIVR			0x3F		/* Programmable Interrupt Vector */

#define	MCFSIM_PACNT			0x80		/* Port A Control (r/w) */
#define	MCFSIM_PADDR			0x84		/* Port A Direction (r/w) */
#define	MCFSIM_PADAT			0x86		/* Port A Value (r/w) */
#define	MCFSIM_PBCNT			0x88		/* Port B Control */
#define	MCFSIM_PBDDR			0x8C		/* Port B Direction */
#define	MCFSIM_PBDAT			0x8E		/* Port B Value */
#define	MCFSIM_PDCNT			0x98		/* Port D Control */

#define	MCFSIM_CSBR0			0x40		/* CS 0 Base reg (r/w) */
#define	MCFSIM_CSOR0			0x44		/* CS 0 Option reg (r/w) */
#define	MCFSIM_CSBR1			0x48		/* CS 1 Base reg (r/w) */
#define	MCFSIM_CSOR1			0x4c		/* CS 1 Option reg (r/w) */
#define	MCFSIM_CSBR2			0x50		/* CS 2 Base reg (r/w) */
#define	MCFSIM_CSOR2			0x54		/* CS 2 Option reg (r/w) */
#define	MCFSIM_CSBR3			0x58		/* CS 3 Base reg (r/w) */
#define	MCFSIM_CSOR3			0x5c		/* CS 3 Option reg (r/w) */
#define	MCFSIM_CSBR4			0x60		/* CS 4 Base reg (r/w) */
#define	MCFSIM_CSOR4			0x64		/* CS 4 Option reg (r/w) */
#define	MCFSIM_CSBR5			0x68		/* CS 5 Base reg (r/w) */
#define	MCFSIM_CSOR5			0x6c		/* CS 5 Option reg (r/w) */
#define	MCFSIM_CSBR6			0x70		/* CS 6 Base reg (r/w) */
#define	MCFSIM_CSOR6			0x74		/* CS 6 Option reg (r/w) */
#define	MCFSIM_CSBR7			0x78		/* CS 7 Base reg (r/w) */
#define	MCFSIM_CSOR7			0x7c		/* CS 7 Option reg (r/w) */

#define MCFSIM_SDCR			0x180		/* SDRAM Control Register */
#define MCFSIM_SDTR			0x184		/* SDRAM Control Register */

/*******************************************/
/*    Registros del módulo Fast Ethernet   */
/*******************************************/
	
#define MCFSIM_MALR			0xC00
#define MCFSIM_MAUR			0xC04

/*******************************************/
/*  Registros del modulo de temporizacion  */
/*******************************************/

#define MCFSIM_TMR0                     0x200
#define MCFSIM_TRR0                     0x204
#define MCFSIM_TCR0                     0x208
#define MCFSIM_TCN0                     0x20C
#define MCFSIM_TER0                     0x210
#define MCFSIM_TMR1                     0x220
#define MCFSIM_TRR1                     0x224
#define MCFSIM_TCR1                     0x228
#define MCFSIM_TCN1                     0x22C
#define MCFSIM_TER1                     0x230
#define MCFSIM_TMR2                     0x240
#define MCFSIM_TRR2                     0x244
#define MCFSIM_TCR2                     0x248
#define MCFSIM_TCN2                     0x24C
#define MCFSIM_TER2                     0x250
#define MCFSIM_TMR3                     0x260
#define MCFSIM_TRR3                     0x264
#define MCFSIM_TCR3                     0x268
#define MCFSIM_TCN3                     0x26C
#define MCFSIM_TER3                     0x270

/* Registros de control del Watchdog */
#define MCFSIM_WRRR                     0x280
#define MCFSIM_WIRR                     0x284
#define MCFSIM_WCR                      0x288
#define MCFSIM_WER                      0x28C


/*******************************************/
/*        Registros del modulo PWM         */
/*******************************************/
#define MCFSIM_PWCR0                    0x00C0
#define MCFSIM_PWCR1                    0x00C4
#define MCFSIM_PWCR2                    0x00C8
#define MCFSIM_PWWD0                    0x00D0
#define MCFSIM_PWWD1                    0x00D4
#define MCFSIM_PWWD2                    0x00D8
/* Correspondencia entre frecuencias y divisor a configurar  */
/* Los módulos PWM generan una señal con un periodo obtenido */
/* de dicidir la frecuencia de reloj del sistema (66 MHz)    */
/* de la siguiente manera:                                   */
/*                                                           */
/* Frec = (66 MHz) / 256*(2^(X)) ,, X = Divisor a configurar     */ 
/*                                                           */
#define PWM_258KHZ                      0x00
#define PWM_129KHZ                      0x01
#define PWM_64KHZ                       0x02
#define PWM_32KHZ                       0x03
#define PWM_16KHZ                       0x04
#define PWM_8KHZ                        0x05
#define PWM_4KHZ                        0x06
#define PWM_2KHZ                        0x07
#define PWM_1KHZ                        0x08
#define PWM_512HZ                       0x09
#define PWM_258HZ                       0x0A
#define PWM_129HZ                       0x0B
#define PWM_66HZ                        0x0C
#define PWM_34HZ                        0x0D
#define PWM_17HZ                        0x0E
#define PWM_9HZ                         0x0F

             

/*
 *	Macro to get and set IMR register. It is 16 bits on the 5272.
 */

#define BASE_PUERTO0                    0x30000000 /* Direccion del puerto 0 */
#define BASE_PUERTO_S                   0x40000000 /* Direccion del puerto S */
#define BASE_PUERTO_E                   0x50000002 /* Direccion del puerto E */


/*******************************************/
/*        Registros del modulo QSPI         */
/*******************************************/
#define MCFSIM_QMR                    0x00A0 /* modo */
#define MCFSIM_QDLYR                  0x00A4 /* retardo */
#define MCFSIM_QWR                    0x00A8 /* wrap */
#define MCFSIM_QIR                    0x00aC /* interrupción */
#define MCFSIM_QAR                    0x00B0 /* dirección */
#define MCFSIM_QDR                    0x00B4 /* dato */

#define QSPI_TX_RAM_START             0x00
#define QSPI_RX_RAM_START             0x10
#define QSPI_COMMAND_RAM_START        0x20





/****************************************************************************/
#endif	/* m5272_h */














