
//ADC// 

//Here converted DC value is stored in address p and (p+1). You can access the output by defining PORTB=*p and PORTC=*(p+1) in your main program.
//AC input to be given at ADC1 pin on PORTA.

#include<avr/io.h>
#define F_CPU 1000000		//CPU speed 1Mhz 
#include "ADCp.h"
#include<avr/interrupt.h>		//calling header file
unsigned int *p;
unsigned int* ADCconv(void)
{
	ADMUX=1<<MUX0|1<<REFS0;				//input on ADC1 pin and AVcc should be given 5V while AREF should be grounded.
	ADCSRA=1<<ADEN|1<<ADSC|1<<ADPS1|1<<ADPS0;		//enabling ADC, starting ADC conversion, and giving prescalar of 8.
	while(!(ADCSRA&(1<<ADIF)));				//wait till entire data is converted.
	*p=ADCL;				//LSB of output is stored at address p 
	*(p+1)=ADCH;			//MSB of output is stored at address (p+1)
	return(p);			//returning address of p
}
void convert(void)
{
	p=ADCconv();
	PORTC=*p;		//LSB of the output.
	PORTB=*(p+1);		////MSB of the output.
}
