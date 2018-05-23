
//To generate wave pulses of required time period and duty cycle in various modes and also a counter to calculate frequency of input wave.
//Copy the commented ISR's to the main program to use this source file. Required ISR's are commented with their respective modes.

//#include "timerhead.h"			...Give this header in the test file.

//NOTE:- assign the values to the variables in the test file too if those variables are used in the ISR. eg: period=0.02; dutycycle=50; wavenormal(0.02,50);

#ifndef timerhead_h
#define timerhead_h
#include<avr/io.h>
#include<avr/interrupt.h>		//Interrupt Library
#define F_CPU 1000000		//defining CPU speed
float period;		//required period of the output wave.
unsigned int dutycycle;		//required dutycycle of the output wave.
unsigned int count,prev,freq;		// initializing variables
void wavenormal(float period,unsigned int dutycycle);		//Normal Mode
void wavectc(float period);		//CTC Mode..Duty cycle cannot be changed.
void wavefpwm(float period,unsigned int dutycycle);		//Fast PWM Mode
void countfreq(void);		//This gives the frequency of input wave. Input wave must be given at ICP1 pin.
#endif

/*			ISR for counting frequency
ISR(TIMER1_CAPT_vect)		//This ISR  is required for input capture mode.
{
	cli();			//clearing any further interrupts
	
	count++;			//since initial waveform generated is not steady, we count after some delay ie say 100 pulses.
	if(count>=50)
	{
		freq=floor(976.5625/(ICR1-prev))+1;		//freq indicates the calculated frequency of input wave.
		PORTA=freq;		//display freq on PORTA,
		TIMSK=~(1<<TICIE1);		//disabling input capture enable to stop after finding frequency.
	}
	prev=ICR1;		//storing previous ICR1 value which is required in calculation.
	
	sei();		//enabling interrupts.
}
*/
/*ISR(TIMER0_OVF_vect)		//Normal Mode
{
cli();		//clearing interrupts

if(PORTB&0X01)					//rest is toggle part.
{
TCNT0=256-floor(9.76125*period*(100-dutycycle));	//after 255 TCNT0 should again return to initialized value instead of 0.
PORTB&=0X00;
}
else
{
TCNT0=256-floor(9.76125*period*dutycycle);		//after 255 TCNT0 should again return to initialized value instead of 0.
PORTB|=0X01;
}
sei();		//enabling interrupts.
}*/

/*ISR(TIMER0_COMP_vect)			//CTC mode
{
	cli();
	
	sei();
}*/

/*		//Fast PWM mode
ISR(TIMER0_COMP_vect)
{
	cli();
	sei();
}
ISR(TIMER0_OVF_vect)
{
	cli();
	TCNT0=floor(OCR0-9.765625*(dutycycle*period))+1;		//it takes TCNT to calculated value instead of 0.
	sei();
}
*/