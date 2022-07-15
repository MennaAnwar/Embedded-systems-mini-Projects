/*
 * code.c
 *
 * Created: 7/15/2022 11:29:35 AM
 * Author : Dell
 */ 

/*
 * generate a square waveform having 10 ms high and 10 ms low time
 *
 */
/*
 * Steps:
 * F_CPU = 8 Mhz 
 * f_timer = 8M / 1024 = 7812.5 hz
 * Ttimer = 1 / 7812.5 = 128 ?s per overflow
 *  to get 10ms we need  about 78 overflows
 */

#include <avr/io.h>
#include <avr/interrupt.h>

void T0delay()
{
	TCCR0 = (1<<CS02) | (1<<CS00); /* Timer0, normal mode, /1024 prescalar */
	TCNT0 = 0xB2;  		/* Load TCNT0, count for 10ms */
	while((TIFR&0x01)==0);  /* Wait for TOV0 to roll over */
	TCCR0 = 0;
	TIFR = 0x1;  		/* Clear TOV0 flag */
}

int main(void)
{
	DDRC = 0xFF;		/* PORTB as output */
	PORTC=0;
	while(1)  		/* Repeat forever */
	{
		PORTC= ~ PORTC;
		T0delay();
	}
}

