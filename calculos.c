#include <stdio.h>

#ifndef SYMBOL
#define NUM_MUESTRAS_PERIODO_10HZ 400
#define N_FRECS 20
#define NUM_MUESTRAS_CADA_SENO
#define SIZE(a) (sizeof(a)/sizeof(*a))
#define NUM_FREC_MUESTREADAS 20
#define NUM_MUESTRAS_CALCULO 80
#define PI 3.14
#endif 


static int sinusoide10Hz[NUM_MUESTRAS_PERIODO_10HZ]={0, 12, 25, 38, 51, 64, 77, 89, 102, 115, 128, 140, 153, 166, 178, 191, 203, 216, 228, 240, 253, 265, 277, 289, 301, 313, 325, 336, 348, 360, 371, 383, 394, 405, 416, 427, 438, 449, 460, 470, 481, 491, 501, 511, 521, 531, 541, 551, 560, 569, 579, 588, 596, 605, 614, 622, 630, 639, 647, 654, 662, 669, 677, 684, 691, 698, 704, 711, 717, 723, 729, 735, 741, 746, 751, 756, 761, 766, 770, 774, 778, 782, 786, 790, 793, 796, 799, 802, 804, 806, 809, 810, 812, 814, 815, 816, 817, 818, 818, 819, 819, 819, 818, 818, 817, 816, 815, 814, 812, 811, 809, 807, 804, 802, 799, 796, 793, 790, 786, 783, 779, 775, 771, 766, 761, 757, 752, 746, 741, 736, 730, 724, 718, 712, 705, 698, 692, 685, 678, 670, 663, 655, 647, 639, 631, 623, 615, 606, 597, 588, 579, 570, 561, 552, 542, 532, 522, 512, 502, 492, 482, 471, 461, 450, 439, 428, 417, 406, 395, 384, 372, 361, 349, 338, 326, 314, 302, 290, 278, 266, 254, 242, 229, 217, 204, 192, 179, 167, 154, 142, 129, 116, 103, 91, 78, 65, 52, 39, 27, 14, 1, -12, -25, -38, -51, -63, -76, -89, -102, -115, -127, -140, -153, -165, -178, -190, -203, -215, -228, -240, -252, -264, -277, -289, -301, -313, -324, -336, -348, -360, -371, -382, -394, -405, -416, -427, -438, -449, -460, -470, -481, -491, -501, -511, -521, -531, -541, -551, -560, -569, -579, -588, -597, -605, -614, -622, -631, -639, -647, -655, -662, -670, -677, -684, -691, -698, -705, -711, -718, -724, -730, -735, -741, -746, -752, -757, -762, -766, -771, -775, -779, -783, -787, -790, -794, -797, -800, -802, -805, -807, -809, -811, -813, -815, -816, -817, -818, -819, -819, -820, -820, -820, -819, -819, -818, -817, -816, -815, -813, -812, -810, -808, -806, -803, -800, -798, -794, -791, -788, -784, -780, -776, -772, -768, -763, -758, -753, -748, -743, -737, -731, -725, -719, -713, -707, -700, -693, -686, -679, -672, -665, -657, -649, -641, -633, -625, -616, -608, -599, -590, -581, -572, -563, -554, -544, -534, -524, -515, -504, -494, -484, -473, -463, -452, -441, -431, -420, -408, -397, -386, -375, -363, -351, -340, -328, -316, -304, -292, -280, -268, -256, -244, -231, -219, -207, -194, -182, -169, -156, -144, -131, -118, -106, -93, -80, -67, -55, -42, -29, -16};
static int frecuenciasMuestreo[NUM_FREC_MUESTREADAS]={50, 100, 200, 300, 400, 500, 600, 700, 800, 900, 1000, 1100, 1200, 1300, 1400, 1500, 1600, 1700, 1800, 1900};

static int modFrecTot[NUM_FREC_MUESTREADAS];

//Pripera muestra 0
int calculaSeno(int frecuencia, int muestra){
	int M = frecuencia/10;
	return sinusoide10Hz[M*muestra%SIZE(sinusoide10Hz)];
	
}

int calculaCoseno(int frecuencia, int muestra){
	int M = frecuencia/10;
	//   a/4==a>>2 desplazamiento de birs a la derecha
	return sinusoide10Hz[(M*muestra+(NUM_MUESTRAS_PERIODO_10HZ>>2))%SIZE(sinusoide10Hz)];
}

void calculaModuloDFT(int muestraADC){
	static numMuestrasLeidas=0;
	static int modFrecCos[NUM_FREC_MUESTREADAS];
	static int modFrecSen[NUM_FREC_MUESTREADAS];
	

	int i;
	for (i = 0; i < NUM_FREC_MUESTREADAS; i++){
		modFrecCos[i]+=muestraADC*calculaCoseno(2*PI*frecuenciasMuestreo[i]/NUM_MUESTRAS_CALCULO,i);
		modFrecSen[i]+=muestraADC*calculaSeno(2*PI*frecuenciasMuestreo[i]/NUM_MUESTRAS_CALCULO,i);
	}

	numMuestrasLeidas++;

	if (muestraADC>=NUM_MUESTRAS_CALCULO){
		int i=0;
		for(i;i<NUM_FREC_MUESTREADAS;i++){
			// a/1024 == a>>10 desplazamiento bits a la derecha
			modFrecCos[i]=modFrecCos[i]>>10;
			modFrecSen[i]=modFrecSen[i]>>10;
			modFrecTot[i]=modFrecCos[i]*modFrecCos[i]+modFrecSen[i]*modFrecSen[i];

			modFrecCos[i]=0;
			modFrecSen[i]=0;
		}
		numMuestrasLeidas=0;
	}



}




int main(int argc, char const *argv[])
{
	int a = calculaCoseno(100,10);
	printf("%d\n", a);
	return 0;
}

