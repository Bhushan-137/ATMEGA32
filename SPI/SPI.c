/*
 * SPI.c
 *
 * Created: 5/8/2018 1:04:52 PM
 *  Author: bhushan Narkhede
 */ 

#define F_CPU 1000000
#include<avr/io.h>
#include <avr/interrupt.h>
#include "SPI.h"
#include<util/delay.h>
unsigned int temp;
void SPIinitmaster()
{
	DDRB=1<<PB5|1<<PB7|1<<PB1|1<<PB2;	//setting MOSI,SCK and PB1 as output
	PORTB=0<<PB1;		//for SS bar of the slave, PB1 should be made low.
	SPCR=(1<<SPE)|(1<<MSTR)|1<<SPR0;	// for master, MSTR should be high and for both master and slave SPE has to be higH,(SPR0/SPR1) gives prescalar.
	
}
void SPIinitslave()
{
	DDRB=0X0;	//For slave, PORTB will be input except MISO pin.
	DDRB|=1<<PB6;	// MISO as output.
	SPCR=(1<<SPE);	//for slave only SPE is made high
}
void SPI(unsigned int master,unsigned char data)
{
	sei();
	DDRA=0XFF;
	if (master==1)
	{
		SPIinitmaster();	//Initialize SPI as master
		SPDR=data;		// transfer any data to the slave; in this eg it is 7
		while(!(SPSR&(1<<SPIF)));		// program will wait till complete data is transfered
		PORTA=SPDR;
	}
	else
	{
		SPIinitslave();		//Initialize SPI as slave.
		SPDR=data;		//data to be sent to master.
		while(!(SPSR&(1<<SPIF)));		//wait till entire data is transferred.
		PORTA=SPDR;		//copy the content to PORTA.
	}
}
/*
ISR(SPI_STC_vect)		//when entire data transmission is done, this ISR is accessed if SPIE is high.
{
	cli();
	_delay_ms(500);
	SPDR=temp;
	while(!(SPSR&(1<<SPIF)));
	sei();
	temp++;
}*/