#include "m5272.h"
#include "megiddo.h"

#define BORRA_REF 02           // Valor de borrado de interr. pendientes de tout1 para TER1.
#define V_BASE 0x40				  // Dirección de inicio de los vectores de interrupción
#define DIR_VTMR0 4*(V_BASE+5)			  // Dirección del vector de TMR0

#define FREC_INT0 1000				  // Frec. de interr. TMR1 = 1000 Hz (cada 1ms)
#define CNT_INT0 MCF_CLK/(FREC_INT0*80*16)	  // Valor de precarga del temporizador de interrupciones TRR1

// array con la frecuencia y duración de cada nota	
static
struct nota_t {
  int frec;
  int duracion;
} melodia[] = {
  { 784,  166 }, 
  { 784,  166 }, 
  { 784,  166 }, 
  { 1047, 333 }, 
  { 1047, 166 }, 
  { 1568, 666 }, 
  { 1,    166 }, 
  { 1568, 166 }, 
  { 1760, 111 }, 
  { 1568, 83 },  
  { 1397, 166 }, 
  { 1568, 1333 },
  { 1,    166 }, 
  { 784,  166 }, 
  { 784,  166 }, 
  { 784,  166 }, 
  { 1047, 333 }, 
  { 1047, 166 }, 
  { 1568, 666 }, 
  { 1,    166 }, 
  { 1568, 166 }, 
  { 1760, 111 }, 
  { 1568, 83 },  
  { 1397, 166 }, 
  { 1760, 166 }, 
  { 1568, 444 }, 
  { 1,    333 }, 
  { 1047, 166 }, 
  { 1047, 166 }, 
  { 1047, 166 }, 
  { 1976, 444 }, 
  { 1568, 222 }, 
  { 1047, 166 }, 
  { 1047, 166 }, 
  { 1047, 166 }, 
  { 1976, 444 }, 
  { 1568, 222 }, 
  { 1047, 166 }, 
  { 1047, 166 }, 
  { 1047, 166 }, 
  { 1976, 166 }, 
  { 1760, 166 }, 
  { 1976, 166 }, 
  { 2093, 666 }, 
  { 1047, 166 }, 
  { 1047, 166 }, 
  { 1047, 166 }, 
  { 1047, 166 }, 
  { 1047, 166 }, 
  { 1047, 444 }, 
  { 0, 0 }, 
};


//------------------------------------------------------
// void avanza_musica (void)
//
// Descripción:
//   
//   El método se encarga de reproducir cada nota
//  a la frecucia y durante la duración deseados
//
//------------------------------------------------------

static
void avanza_musica (void)
{
  static int i = 0;
  int frecuencia = melodia[i].frec;
  int duracion = melodia[i].duracion;
  if (melodia[++i].duracion == 0) {
    i = 0;
  }

  if (! efectoActivo()) {
    mbar_writeShort(MCFSIM_TCN0, 0x0000);
    mbar_writeShort(MCFSIM_TRR0, MCF_CLK/(2*80*16*frecuencia));
    mbar_writeShort(MCFSIM_TMR0, 0x4F3D);
  }
  tareaTemporizada (duracion, avanza_musica);
}

//------------------------------------------------------
// void musica_on (void)
//
// Descripción:
//   
//   Activa música sistema
//
//------------------------------------------------------


void
musica_on (void)
{
  tareaTemporizada (1, avanza_musica);
}

//------------------------------------------------------
// void musica_on (void)
//
// Descripción:
//   
//   Desactiva música sistema
//
//------------------------------------------------------


void
musica_off (void)
{
  eliminarTareaTemporizada (avanza_musica);
}

static
void __attribute__((interrupt_handler)) isr_timer0 (void)
{
  mbar_writeShort (MCFSIM_TER0,BORRA_REF); 
}

//------------------------------------------------------
// void configurarSonidoSistema(void)
//
// Descripción:
//   
//   Configura el timer para su correcto funcionamiento
//
//------------------------------------------------------


void configurarSonidoSistema(void)
{
  // Fija comienzo de vectores de interrupción en V_BASE.
  mbar_writeByte(MCFSIM_PIVR,V_BASE);
  // Escribimos la dirección de la función para TMR0
  ACCESO_A_MEMORIA_LONG(DIR_VTMR0)= (ULONG)isr_timer0;
  // TMR0: PS=0x50-1 CE=00 OM=1 ORI=1 FRR=1 CLK=10 RST=1
  mbar_writeShort(MCFSIM_TMR0, 0x4F3C);
  // Ponemos a 0 el contador del TIMER0
  mbar_writeShort(MCFSIM_TCN0, 0x0000);		
  // Fijamos la cuenta final del contador
  mbar_writeShort(MCFSIM_TRR0, CNT_INT0);
  // Marca la interrupción del TIMER0 como no pendiente
  mbar_writeLong(MCFSIM_ICR1, 0x8888EF88);
  // y de nivel 4.
  sti();
}
