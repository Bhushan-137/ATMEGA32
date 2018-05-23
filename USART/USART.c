/*
 * USART11.c
 *
 * Created: 5/15/2018 10:27:59 AM
 *  Author: Pranjali Narkhede
 */ 


/*
 * USART1.c
 *
 * Created: 5/14/2018 12:03:35 PM
 *  Author: Pranjali Narkhede
 */ 

#define F_CPU 1000000		//CPU speed
#define BAUD	4800		//Baud rate
#include<avr/io.h>
#include<avr/interrupt.h>
#include "USART11.h"	//created header file

#include<util/delay.h>
#include<math.h>
unsigned char data;

void USARTinit(unsigned int ubrr)
{
	UCSRC=0;
	UBRRH=(ubrr)>>8;		//storing higher bits in UBRRH
	UBRRL=(ubrr);			//storing lower bits here.
	UCSRB=1<<TXEN|1<<UDRIE;		//enable receiver and transmitter
	UCSRC=1<<URSEL|1<<UCSZ1|1<<UCSZ0;		//transmitting 8 bit data	
}
void USARTtransmit(unsigned char data)		//USART transmission function
{
	while(!(UCSRA&(1<<UDRE)));		//loop will run till the buffer is empty
	UDR=data;		//then complete data is copied to UDR
	//PORTB=UDR;		//display UDR on portB
}
void USART_send_string(char str[])		//Send string function
{
	unsigned char j=0;
	while(str[j]!=0)		// loop will run till the end of the string.
	{
		USARTtransmit(str[j]);	
		_delay_ms(500);		//delay of 500ms
		j++;
	}
}
unsigned char USARTreceive(void)		//Receiving data
{
	while(!(UCSRA&(1<<RXC)));		//loop will run till every data is received.
	return UDR;	
}


void send(char str[])
{
	unsigned int myubrr	= floor(F_CPU/16/BAUD)-1;	//value to be stored in UBRR register.
	unsigned char a;
	DDRB=0XFF;			// Port B as output.
	USARTinit(myubrr);		// Initialize USART
	USART_send_string(str);		// send any string.

   while(1)
    {
        a=USARTreceive();
		PORTB=a;
	}
	
}