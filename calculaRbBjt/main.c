/** calculaRbBjt. 			calcula e imprime parámetros de polarización de un transistor bipolar.
*  Descripción:
*		Se polariza un trnsistor NPN amplificador de proposito general en configuración emisor común.
*       se calcula la magnitud de la corriente de colector, Rload = 10kOhm, 
*       calcula la magnitud Ib desde la expresión de ganancia de corriente hfe = Ic / Ib 

**/


#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
	
	float Vce_sat = 0.60;			// caída de tensión [1]
	float Vbe_on  = 0.70;			// caída de tensión [1]
	float Vinput  = 5.00;			// Vsenal 
	float hfe	  = 200.0;			// registro del instrumento de medición
	float Rload   = 10000;          // resistor de carga
	float Vcc	  = 5.0;            // tensión de polarización
	
	
	float VsatOut = Vcc - Vce_sat;  // 
	float Ic_max  = Vcc / Rload;	// 
	float Ib	  = Ic_max / hfe;	// hfe = Ic / Ib
	float VsatIn  = Vinput - Vbe_on;//
	float Rb	  = VsatIn / Ib;	// 
	float Pd	  = Vcc * Ic_max;   // Potencia de disipacion
	
	printf("%s %+e %s\n",  " VsatOut: "  , VsatOut, " [V]");
	printf("%s %+e %s\n",  " Ic_max : "  , Ic_max,  " [A]");
	printf("%s %+e %s\n",  " Ib     : "  , Ib,      " [A]");
	printf("%s %+e %s\n",  " VsatIn : "  , VsatIn,  " [V]");
	printf("%s %+e %s\n",  " Rb     : "  , Rb   ,   " [Ohm]");
	printf("%s %+e %s\n",  " Pd     : "  , Pd   ,   " [Watt]");	
	
	return 0;
}
