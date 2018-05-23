/*
 * twi3.c
 *
 * Created: 5/18/2018 4:21:20 PM
 *  Author: Pranjali Narkhede
 */ 


/*
 * twi2.c
 *
 * Created: 5/18/2018 11:15:13 AM
 *  Author: Pranjali Narkhede
 */ 

//NOTE:- YOU NEED TO CLEAR THE TWINT FLAG AFTER EVERY TRANSMISSION MANUALLY BY SETTING THE TWINT BIT 1 since after every transmission flag is set but not cleared.

#define F_CPU 1000000			//setting  CPU speed
#define SCL 50000		//Setting Serial Clock speed
#include<avr/io.h>
#include "twi3.h"
#include<avr/interrupt.h>
void Master_init()		//initialize Master
{
	TWSR=0;
	TWBR=0X02;			//((F_CPU/SCL)-16)/2
}
void Master_start()		//Sending start bit
{
	TWCR=1<<TWEN|1<<TWSTA|1<<TWINT;		//making enable high, sending start bit, setting interrupt flag
	while(!(TWCR&(1<<TWINT)));		//wait till start bit is transmitted
}
void TWI_init_slave(unsigned char  address) // Function to initialize slave
{
	TWAR=address;    // Assign slave address to TWAR
}
void slave_receive()		//Receiving data by the slave
{
	TWCR=1<<TWEN|1<<TWEA|1<<TWINT;		//Setting TWI enable,acknowledge bit and interrupt
	while(!(TWCR&(1<<TWINT)));			//waiting for acknowledge bit to be sent.
}
void Send_add(unsigned char addr)		//Sending slave address and read/write bit
{
	TWDR=addr;		//storing address+read/write bit in TWDR...for read bit=1,write=0
	TWCR=1<<TWEN|1<<TWINT;		// Setting TWINT bit
	while(!(TWCR&(1<<TWINT)));		//waiting for transmission to complete/ flag to set.
	//while(!(TWSR==0x18));
}
void Send_data(unsigned char data)		//Sending data
{
	TWDR=data;
	TWCR=1<<TWEN|1<<TWINT;		//Setting TWINT bit
	while(!(TWCR&(1<<TWINT)));	////waiting for transmission to complete/ flag to set.
}
void Send(unsigned char master, unsigned char data, unsigned int address)  //Function to be called.
{
	if(master==1)
	{
		Master_init();		//initialize Master
		Master_start();		//Sending start bit
		Send_add(address);		//Sending slave address and read/write bit
		Send_data(data);		//Sending data
		while(1);
	}
	else
	{
			DDRA=0xFF;		//Making PortA as output
			TWI_init_slave(address+1);		//initializing slave
			slave_receive();		//receiving the data
			PORTA=TWDR;				//Copying content of TWDR TO Port A.
	}
}