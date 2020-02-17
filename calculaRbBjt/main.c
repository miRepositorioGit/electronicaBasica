/** calculaRbBjt. 			calcula e imprime par�metros de polarizaci�n de un transistor bipolar.
*  Descripci�n:
*		Se polariza un trnsistor NPN amplificador de proposito general en configuraci�n emisor com�n.
*       se calcula la magnitud de la corriente de colector, Rload = 10kOhm, 
*       calcula la magnitud Ib desde la expresi�n de ganancia de corriente hfe = Ic / Ib 

**/


#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
	
	float Vce_sat = 0.60;			// ca�da de tensi�n [1]
	float Vbe_on  = 0.70;			// ca�da de tensi�n [1]
	float Vinput  = 5.00;			// Vsenal 
	float hfe	  = 200.0;			// registro del instrumento de medici�n
	float Rload   = 10000;          // resistor de carga
	float Vcc	  = 5.0;            // tensi�n de polarizaci�n
	
	
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
