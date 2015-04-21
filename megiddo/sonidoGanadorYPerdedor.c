#include "m5272.h"
#include "megiddo.h"

#define V_BASE 0x40				  // Direcci�n de inicio de los vectores de interrupci�n
#define DIR_VTMR0 4*(V_BASE+5)			  // Direcci�n del vector de TMR0
#define FREC_INT 1000				  // Frec. de interr. TMR1 = 1000 Hz (cada 1ms)
#define MULTIPLICADOR_FRECUENCIA0 2*0x50*16       // Multiplicador frecuencia para calcular el retardo del TRR0.
#define CNT_INT0 0                         	  // Valor de precarga del temporizador de interrupciones TRR0
#define CNT_INT1 MCF_CLK/(FREC_INT*0x4F*16)	  // Valor de precarga del temporizador de interrupciones TRR1
#define BORRA_REF 0x0002			  // Valor de borrado de interr. pendientes de tout1 para TER1
#define FCR1_MASK 0x40


//------------------------------------------------------------
//
//Aqu� definimos las estructuras necesarias para
//la melod�a del ganador y perdedor.
//Tambi�n definimos otrasconstantes
// 
//-------------------------------------------------------------

struct nota_t {
  int frec;
  int duracion;
};

static struct nota_t melodia_ganador[] = {
  { 523, 300 },
  { 659, 300 },
  { 784, 300 },
  {   0,   0 },
};

static struct nota_t melodia_perdedor[] = {
  { 392, 500 },
  { 330, 500 },
  { 262, 500 },
  {   0,   0 },
};

static volatile struct nota_t* melodia = 0;
static volatile int efecto = 0;

//----------------------------------------------------------
//
//int efectoActivo(void)
//
//Descripci�n:
//
//devuelve un entero que es un 1 o 0 dependiendo si hay
//efecto o no, es decir, si se esta reproduciendo alguna
//melod�a de ganador o perdedor.
//
//----------------------------------------------------------

int efectoActivo (void)
{
  return efecto;
}

//----------------------------------------------------------
//
//void avanza_efecto(void)
//
//Descripci�n:
//
//Si efecto=0 no hace nada.
//En caso contrario reproduce una nota a la frecuencia 
//y durante el tiempo deseados. Para ello configura el timer0
//y llama al m�todo tareaTemporizada
//
//----------------------------------------------------------

static
void avanza_efecto (void)
{
  int frecuencia = melodia->frec;
  int duracion = melodia->duracion;

  if (duracion == 0) { 
    efecto = 0; 
    return; 
  }
  mbar_writeShort(MCFSIM_TCN0, 0x0000);		
  mbar_writeShort(MCFSIM_TRR0, 
		  MCF_CLK/(MULTIPLICADOR_FRECUENCIA0*frecuencia));
  mbar_writeShort(MCFSIM_TMR0, 0x4F3D);
  ++melodia;
  tareaTemporizada (duracion, avanza_efecto);
}

//----------------------------------------------------------
//
//void tocarMelodiaGanador(void)
//
//Descripci�n:
//
//Cuando se llama a este m�todo se reproduce melod�a ganador
//
//----------------------------------------------------------

void tocarMelodiaGanador(void)
{
  efecto = 1;
  melodia = melodia_ganador;
  tareaTemporizada (1, avanza_efecto);
  while (efecto) ;
}

//----------------------------------------------------------
//
//void tocarMelodiaPerdedor(void)
//
//Descripci�n:
//
//Cuando se llama a este m�todo se reproduce melod�a perdedor
//
//----------------------------------------------------------

void tocarMelodiaPerdedor(void){
  efecto = 1;
  melodia = melodia_perdedor;
  tareaTemporizada (1, avanza_efecto);
  while (efecto) ;
}
