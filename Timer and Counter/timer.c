/*
 * TimerHead.c
 *
 * Created: 5/10/2018 3:49:55 PM
 *  Author: Pranjali Narkhede
 */ 

//To generate wave pulses of required time period and duty cycle in various modes and also a counter to calculate frequency of input wave. 
//Copy the commented ISR's to the main program to use this source file. Required ISR's are commented with their respective modes.

#include<avr/io.h>
#include<avr/interrupt.h>
#include<math.h>
#include "timerhead.h"	//created header file
#define F_CPU	1000000		//assigning clock speed

void wavenormal(float period,unsigned int dutycycle)
{
	sei();		//enable interrupts
	DDRB=1<<PB0;	// assigning PB0 as output
	PORTB=0X01;		//initializing PB0 as 1
	TCCR0=1<<CS02|1<<CS00;		//giving prescalar of 1024 in normal mode
	TIMSK=1<<TOIE0;		//enabling overflow interrupt flag;		//TCNT0 calculation
	while(1)
	{
		
	}
}
void wavectc(float period)		//CTC mode can only generate waves of 50% duty cycle. So there's only one parameter.
{
		sei();
		DDRB=1<<PB3;		//for CTC OC0 pin gives waveform which is PB3.
		PORTB|=0x0;		//initialize toggle
		TCCR0=1<<WGM01|1<<CS00|1<<CS02|1<<COM00;	//CTC mode is ON, prescale of 1024 and COM00 should be 1 and COMO1 should be 0 for toggle on compare match.
		TIMSK|=1<<OCIE0;		//OCIE0 should be high for output compare interrupt operation
		OCR0=floor(488.28125*period);		//calculated using CTC mode formula.
		TCNT0=0;	//initialize TCNT0 to 0;
		while(1)
		{
			
		}
}
void wavefpwm(float period,unsigned int dutycycle)
{
		sei();			//enable interrupts
		DDRB=1<<PB3;		//making OCO pin as output
		TIMSK=1<<OCIE0|1<<TOIE0;	//enabling output compare and overflow interrupts
		TCCR0=1<<WGM00|1<<WGM01|1<<COM01|1<<CS02|1<<CS00;	//selecting fast interrupt mode and toggle condition.
		OCR0=255-floor(9.765625*(100-dutycycle)*period);		//OCR0 calculation	
		TCNT0=floor(OCR0-9.765625*(dutycycle*period))+1;		// TCNT0 calculation
		
		while(1)
		{
			
		}
}

void countfreq(void)
{
	sei();		//enabling the interrupts
	DDRD=0<<PD6;		// making ICP1 pin as input. For counter, input wave should be given to ICP1 pin. 
	DDRA=0XFF;		// PORTA as output
	TCCR1A=0;
	TCCR1B=1<<ICES1|1<<CS10|1<<CS12;		//giving prescalar of 1024 and making input capture edge select as positive edge triggering output.
	TIMSK=1<<TICIE1;		//enabling input capture interrupt enable.
    while(1)
    {
        
    }
}
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