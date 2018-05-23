//USART
//TX and RX pin of transmitter should be connected to RX and TX pin of receiver. 
//send(char) to be called in test file. 
//#include "USART11.h"		call header file in test file
//Here BAUD Rate is taken as 4800 and 8 bits transfer..can be changed in the source file.
//Also, here data is displayed on PORTB, can be changed in source file.



#ifndef USART11_h
#define USART11_h
#include<avr/io.h>
#include<avr/interrupt.h>
#include<string.h>
#define F_CPU	1000000		//definin CPU speed
unsigned int myubrr;	//value to be stored in UBRR register.
void USARTinit(unsigned int);		//Initialize USART
void USARTtransmit(unsigned char);		//Transmission in USART
unsigned char USARTreceive(void);	//Receiving data
unsigned char data;		//defining a variable data 
void send(char str[]);		//Function to be called in test file with string to be sent.
void USART_send_string(char str[]);		//Send string function

#endif
