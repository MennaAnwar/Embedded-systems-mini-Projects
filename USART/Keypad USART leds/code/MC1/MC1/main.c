/*
 * MC1.c
 *
 * Created: 7/17/2022 3:42:46 PM
 * Author : Dell
 */ 

#include "uart.h"
#include "keypad.h"

int main(void)
{
	uint8 key_num;
	UART_init();
	while(1)
	{
		key_num = KeyPad_getPressedKey();
		if((key_num >= 0) && (key_num <= 7))
		{
			UART_sendByte(key_num);
		}
		_delay_ms(500); //new button every 500ms
	}
}

