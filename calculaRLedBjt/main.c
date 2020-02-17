/*** calculaRLedBjt.dev    Calcula la resistencia de colector y base, para un polarizar un transistor bipolar NPN en modo emisor común.
Descripción:
				Calcular las magnitudes de resistencia en las terminales de colector y base para polarizar un
		transistor bipolar NPN de proposito general BC54, como interruptor accionado por corriente eléctrica.
		 
		La suma algebraica de los consumos de tensión, en un circuito serie, i constante, es igual a cero. LTK
		
		Calcular la resistencia de colector.   Considerando que:
				
	Se determinan los consumos de tensión de cada componente electrónico a través de la ecuación [1], 
	expresada con la ley de Ohm. La magnitud de corriente eléctrica en un circuito serie tiene la misma magniitud en 
	todos los elementos.	
	
	Se expresa el consumo de tensión del resistor de carga, Rl, expresado por la ley de Ohm. 
	
	Se propone la magnitud de corriente de un led, emisor de luz, color rojo [650nm - 670nm] con If = 20mA y Vf = 2.1V 
como condición de polarización recomendada en hoja de datos OptoSupply 5mm Round Red LED OSR7CA5111A [6].  

	Se propone un consumo de tensión entre terminales c-e del BJT conforme a los máximos absolutos, tabulados en hoja de
especificaciones del fabdricante Vce_sat   = 0.60 [7]. 

	Se registra con instrumento de medición la Hfe del BJT, hfe = 200. Por lo que Hfe = Ic / Ib [5].

		Calcular la resistencia de base.
		
	Se expresa el consumo de tensión del resistor de base, Rb, expresado por la ley de Ohm. 	
	Se propone que:
	1] V_inputHigh y IOH, como una funte de polarización en el modo SOURCE. Output high voltage Voh: 4.1 V @  IOH < 25mA    [4] 
    2] el consumo de tensión en b-e Vbe_sat	= 0.77
	3] un factor de seguridad de 1.414 * ib     		
	4] el calculo de la magnitud de ib es obtenido de Hfe registrado = Ic / Ib.
	

Vled_sat + Vce_sat + Vrl = V_polarizacion	[1]
i= 20mA 									[2]
Vrl = iRled 								[3]
Vled_sat + Vce_sat + iRled = V_polarizacion	[1]

	De esta última despejando Rled.

Rled = (V_polarizacion - Vled_sat - Vce_sat) / i
Hfe  = 200 [5]

Referencias 

[1]  Ley de voltajes Kirchoff 
[2]  corriente consumo Led:20mA
[3]  tensión eléctrica consimida por el led
[4]  ATmega48A-PA-88A-PA-168A-PA-328-P-DS 
      Table 30-1 
	  Output high voltage Voh: 4.1 V
	  
	  
	3. Although each I/O port can SOURCE more than the test conditions (20mA at VCC = 5V, 10mA at VCC = 3V) under steady state conditions (non-transient), the
		following must be observed:
			ATmega48A/PA/88A/PA/168A/PA/328/P:
		1] The sum of all IOH, for ports C0 - C5, D0- D4, ADC7, RESET should not exceed 150mA.
		2] The sum of all IOH, for ports B0 - B5, D5 - D7, ADC6, XTAL1, XTAL2 should not exceed 150mA.
		If IIOH exceeds the test condition, VOH may exceed the related specification. Pins are not ensured to source current greater than the listed test condition.
	  
	  4. Although each I/O port can SINK more than the test conditions (20mA at VCC = 5V, 10mA at VCC = 3V) under steady state conditions (non-transient), the
         following must be observed:
				ATmega48A/PA/88A/PA/168A/PA/328/P:
		1] The sum of all IOL, for ports C0 - C5, ADC7, ADC6 should not exceed 100mA.
		2] The sum of all IOL, for ports B0 - B5, D5 - D7, XTAL1, XTAL2 should not exceed 100mA.
		3] The sum of all IOL, for ports D0 - D4, RESET should not exceed 100mA.
		If IOL exceeds the test condition, VOL may exceed the related specification. Pins are not ensured to sink current greater than the listed test condition. 
    
	 http://ww1.microchip.com/downloads/en/DeviceDoc/ATmega48A-PA-88A-PA-168A-PA-328-P-DS-DS40002061A.pdf
[5]  índice de ganancia de corriente, registrado experimetalmente para Bc547.
[6]  OptoSupply 5mm Round Red LED OSR7CA5111A  http://www.optosupply.com/uppic/201682624017.pdf
[7]  Fairchild NPN General Purpose Amplifier. http://www.farnell.com/datasheets/59764.pdf
**/


#include <stdio.h>
#include <stdlib.h>


 struct  absoluteMaximunRatings{
					
					float Vled_sat;			// tensión polarización Vf led [6]
					float Iled;             // corriente polarizaciónI
						
					float Vce_sat;			// consumo de tensión e-c
					float Vbe_sat;      	// consumo de tensión b-e
					float Vce_corte;        // Umbral de tensión máxima
					float Veb_corte;		// Umbral de tensión máxima
					float Ic;				// Corriente de colector
					float Hfe;				// ganacia de corriente registrada empiricamente
					float factSeg;			// factor seguridad
					
					float V_polarizacion;  // Polarización del circuito transistorizado	
					float V_inputHigh;     // Tensión de senal de entrada
				}  ;

int main(int argc, char *argv[]) {
	
	struct absoluteMaximunRatings bc547;
	bc547.Vce_sat   = 0.60;				// consumo de tensión c-e
	bc547.Vbe_sat	= 0.77;				// consumo de tensión b-e
	bc547.Vce_corte = 45;               // Umbral de tensión máxima
	bc547.Veb_corte = 6.0;				// Umbral de tensión máxima
	bc547.Ic        = 0.500;			// Corriente de colector
	bc547.Hfe       = 200;				// ganacia de corriente registrada empiricamente
	bc547.factSeg   = 1.414;			// factor de seguridad

	struct absoluteMaximunRatings ledOn;
	ledOn.Iled     = 0.020;				// corriente de consumo de led
	ledOn.Vled_sat = 2.1;               // voltaje de umbral de led
	
	struct absoluteMaximunRatings Vcd;
	Vcd.V_polarizacion = 12.0;			// Tensdión de polarización del circuito
	Vcd.V_inputHigh    =  4.1;			// Tensión de senal de entrada
	
	/** calcula resistencia en serie con led,colector **/
	
	float Rload = (Vcd.V_polarizacion - ledOn.Vled_sat - bc547.Vce_sat) / ledOn.Iled;
	float sumaConsumoTension = (ledOn.Iled * Rload) +  ledOn.Vled_sat + bc547.Vbe_sat;
	float lvKirrchofCol = Vcd.V_polarizacion - sumaConsumoTension; 
	float Icolector = (Vcd.V_polarizacion - ledOn.Vled_sat - bc547.Vce_sat) / Rload;
	 	
	/** calcula corriente de base **/
	
	float Ibase = ledOn.Iled / bc547.Hfe;
	float Rbase = (Vcd.V_inputHigh - bc547.Vbe_sat) / (Ibase*bc547.factSeg);
    float lvKirrchofBase = Vcd.V_inputHigh - (Ibase*Rbase)  - bc547.Vbe_sat;

	/**  calcula potencia de disipación **/
	float Pd = Icolector * bc547.Vce_sat;
	
	/**  calcula corriente de emisor **/
	float Iemisor =  Icolector + Ibase;
	
	/** calcula ganancia corriente **/
	float Hfe = Icolector / Ibase;
	
	/** imprime resultados **/ 

	printf("\n\n");
	printf("\t %s %+3.4f \n","Icolector  :" ,Icolector);
	printf("\t %s %+3.4f \n","Ibase      :" ,Ibase);
	printf("\t %s %+3.4f \n","Iemisor    :" ,Iemisor);
	printf("\t %s %+3.4f \n","Hfe        :" , Hfe);
	
	printf("\t %s %+3.4f \n","Pd         :" ,Pd);
	printf("\t %s %+3.4f \n","Rload      :" ,Rload);
	printf("\t %s %+3.4f \n","Rbase      :" ,Rbase);
//	printf("\t %s %+3.4f \n","LVKcol     :" ,lvKirrchofCol);
//	printf("\t %s %+3.4f \n","LVKbase    :" ,lvKirrchofBase);
		
	
	return 0;
}
