/*
 * keypad_lcd.c
 *
 * Created: 7/11/2022 10:41:25 AM
 * Author : Dell
 */ 

#include "lcd.h"
#include "keypad.h"

int main(void)
{
	unsigned char key;
	LCD_init();
	LCD_displayStringRowColumn(0,0,"Hello ^^");
	LCD_goToRowColumn(2,0);
    while (1) 
    {
		/* if any switch pressed for more than 500 ms it counts more than one press */
		key = KeyPad_getPressedKey(); /* get the pressed key number */
		if((key <= 9) && (key >= 0))
		{
			LCD_intgerToString(key); /* display the pressed keypad switch */
		}
		else if(key == 13){
			LCD_clearScreen();
		}
		else
		{
			LCD_displayCharacter(key); /* display the pressed keypad switch */
		}
		_delay_ms(500); /* Press time */
    }
}

