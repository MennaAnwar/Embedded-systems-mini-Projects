/*
 * main.c
 *
 * Created: 7/15/2022 11:00:18 AM
 * Author : Dell
 */ 

/*
 * Requirements:
 * Configure the µC control with internal 1Mhz Clock.
 * The led is connected to pin 0 in PORTC.
 * Connect the Led using Positive Logic configuration. Configure the timer clock to F_CPU/1024.
 * Timing should be count using Timer0 in Normal Mode.
 * Toggle the led every half second.
 */

/*
 * Steps:
 * timer freq = 1Mhz/1024 = 976.5625 hz
 * Ttimer = 1/976.5625 = 1.024 msec per overflow
 * to get 0.5 sec -->  1.024m / 0.5  = 2 overflows 
 *
 * therefore, we need 2 overflows to get 0.5 sec
 */

#include <avr/io.h>
#include <avr/interrupt.h>

#define NUMBER_OF_OVERFLOWS_PER_HALF_SECOND 2

unsigned char g_tick = 0;

ISR(TIMER0_OVF_vect)
{
	g_tick++;
	if(g_tick == NUMBER_OF_OVERFLOWS_PER_HALF_SECOND)
	{
		PORTC = PORTC ^ (1<<PC0); //toggle led every 0.5 second
		g_tick = 0; //clear the tick counter again to count a new 0.5 second
	}

	TIFR |= (1<<0);
}

void timer0_init_normal_mode(void)
{
	TCNT0 = 0; //timer initial value
	TIMSK |= (1<<TOIE0); //enable overflow interrupt
	/* Configure the timer control register
	 * 1. Non PWM mode FOC0=1
	 * 2. Normal Mode WGM01=0 & WGM00=0
	 * 3. Normal Mode COM00=0 & COM01=0 
	 * 4. clock = F_CPU/1024 CS00=1 CS01=0 CS02=1
	 */
	TCCR0 = (1<<FOC0) | (1<<CS02) | (1<<CS00);
}

int main(void)
{
	DDRC  |= (1<<PC0); //configure the led pin to be output pin.
	PORTC &= ~(1<<PC0); //LED is off at the beginning(Positive Logic).
	SREG  |= (1<<7); //enable global interrupts in MC by setting the I-Bit.
	timer0_init_normal_mode(); //start the timer.
	while(1)
	{

	}
}

