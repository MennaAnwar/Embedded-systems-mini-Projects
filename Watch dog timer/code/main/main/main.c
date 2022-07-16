/*
 * main.c
 *
 * Created: 7/16/2022 1:25:28 PM
 * Author : Dell
 */ 

/* Watchdog timer resets the main program after 2.1 sec timeout. LED turns ON and OFF after every 2.1
 * sec due Watchdog timer reset.
 */

#include <avr/io.h>
#include <util/delay.h>

//	function to enable Watchdog timer.
void WDT_ON(void)
{
	// Watchdog timer enables with timeout period 2.1 second.
	WDTCR = (1<<WDE)|(1<<WDP2)|(1<<WDP1)|(1<<WDP0);
}

// 	function to disable Watchdog timer.
void WDT_OFF(void)
{
	WDTCR = (1<<WDTOE)|(1<<WDE);
	WDTCR = 0x00;
}

int main(void)
{
	
	WDT_ON(); // Enable the Watchdog timer
	DDRD |= (1<<PD6); // Configure PD6 as output pin
	PORTD |= (1<<PD6); // Toggle the led every reset
	_delay_ms(1000);
	PORTD &= ~(1<<PD6);
	// Wait until the system reset itself
	while(1);
}

