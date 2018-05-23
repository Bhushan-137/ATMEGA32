//USART
//send( , , ) function to be called.
// In circuit diagram, SCL and SDA of master should be shorted with that of slave.
//Pull up resistors (1.5k ohm each) should be connected to each of SCL and SDA lines with 5V  battery on other sides.

#ifndef twi3_h
#define twi3_h
#include<avr/io.h>
#include<avr/interrupt.h>
#include<string.h>
#define F_CPU	1000000		//defining CPU speed
#define SCL 50000		//Setting Serial Clock speed
void Master_init();		//initialize Master
void Master_start();		//Sending start bit
void TWI_init_slave(unsigned char  address); // Function to initialize slave
void slave_receive()	;	//Receiving data by the slave
void Send_add(unsigned char addr);		//Sending slave address and read/write bit
void Send_data(unsigned char data)	;	//Sending data
void Send(unsigned char master, unsigned char data, unsigned int address ) ; //Function to be called. For master, master=1 else 0.
#endif
