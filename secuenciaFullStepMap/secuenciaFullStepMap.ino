/** 
 *    
 *
 */ 

#define F_CPU 16000000UL // Defining the CPU Frequency for Delay Calculation in delay.h 
// Arduino UNO used a 16Mhz Crystal as Clock Source
#include <avr/io.h> // Contains all the I/O Register Macros
//#include <avr/util.h> // Generates a Blocking Delay
#include <util/delay.h>


//void setup() {
// 
//}
//void loop() {
//}

uint8_t fullStep[] ={0x03,
            0x06,
            0x0c,
            0x09};

            
uint8_t auxTime    = 50;
uint8_t steps      = 100;
uint8_t cntPasosCw = 200;

int main(void)
 {
     DDRC |= (1<<PC0)|(1<<PC1)|(1<<PC2)|(1<<PC3); // Configuring PC0-PC3 as Output
     PORTC = 0x00;
   
     for(;;)
{
     uint8_t index = 0;
      for (steps=0;steps<200;steps++)
        {
        for (index = 0;index<4;index++)
            {
             PORTC = fullStep[index];
            _delay_ms(auxTime);       // Delay of n Second
            }
        }

                 
        for (steps=0;steps<200;steps++)
        {
          PORTC = fullStep[3];
            _delay_ms(auxTime);       // Delay of n Second
          PORTC = fullStep[2];
            _delay_ms(auxTime);       // Delay of n Second
          PORTC = fullStep[1];
            _delay_ms(auxTime);       // Delay of n Second
          PORTC = fullStep[0];
            _delay_ms(auxTime);       // Delay of n Second  
        }

      //  while(1){}
  }
 }
// 
