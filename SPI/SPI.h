//SPI
//#include "SPI.h"		..this should be included in the test file.
//In the circuit, connect MOSI,MISO,SCK of master to MOSI,MISO,SCK of slave.
//for master operation master in SPI function should be given 1 and for slave should be given 0.
//Here PB1 is taken as output and connected to SS bar pin of slave. Make PB1 0 to activate the slave.
//ISR should be copied to test file. Here in ISR incrementing is operated but can be used of required operation.


#ifndef SPI_h
#define SPI_h
#define F_CPU 1000000			//defining CPU speed.
#include<avr/io.h>
#include <avr/interrupt.h>
#include<util/delay.h>		//for delay operation.
unsigned int temp;    //temporary variable required in data transmission. 
void SPIinitmaster(void);		//Initializing the SPI as Master.
void SPIinitslave(void);		//Initializing SPI as slave. 
void SPI(unsigned int master,unsigned char data);	// Carries out SPI operation.. This function should only be called in the test file. 
#endif

/*
ISR(SPI_STC_vect)		//when entire data is transmitted, this ISR is accessed if SPIE is high.
{
	cli();
	_delay_ms(500);
	SPDR=temp;
	while(!(SPSR&(1<<SPIF)));
	sei();
	temp++;
}*/