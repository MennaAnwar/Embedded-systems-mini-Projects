/*
 * MC2.c
 *
 * Created: 7/17/2022 3:46:57 PM
 * Author : Dell
 */ 

#include "uart.h"

int main(void)
{
	uint8 key_num;
	
	DDRC  = 0xFF; //configure PORTC as output port
	PORTC = 0; // All leds are off
	
	UART_init();
	
	while(1)
	{
		key_num = UART_recieveByte(); //Receive LED number that required to be ON
		PORTC = (1<<key_num);
	}
}
