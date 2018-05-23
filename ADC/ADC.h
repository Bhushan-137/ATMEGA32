//ADC//

//Here converted DC value is stored in address p and (p+1). You can access the output by defining PORTB=*p and PORTC=*(p+1) in your main program.
//AC input to be given at ADC1 pin on PORTA.

//NOTE:- //Input should be given oat ADC1 pin and AVcc pin should be given 5V while AREF pin should be grounded.
//Just call the function convert() in the infinitely running while loop.

//LSB of the output is displayed at PORTC and MSB is displayed at PORTB so declare PORTB and C as output. 
//Also just define the function void convert(void) in the test file if the warning implicit declaration comes.

//#include "ADCp.h"   ...This should be included in the test file.

//Calculations:- (Vin/AVcc)*1024 = output seen in PORTB and PORTC.

#ifdef ADCp_h
#define ADCp_h
#include<avr/io.h>
#include<avr/interrupt.h>
#define F_CPU 1000000		//defining CPU speed		
unsigned int *p;		//defining a pointer to store the address of variable which contain the DC value.
unsigned int* ADCconv(void);	//This function converts AC to DC and stores the DC value at address p and (p+1)
void convert(void);		//This function is used for continuous conversion of AC to DC.
#endif

/* This ISR should be included in the test file. 
ISR(ADC_vect)
{
	cli();
	convert();
	sei();
}
*/