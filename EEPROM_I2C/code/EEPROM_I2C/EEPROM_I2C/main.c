/*
 * EEPROM_I2C.c
 *
 * Created: 7/11/2022 7:24:05 PM
 * Author : Dell
 */ 

#include "micro_config.h"
#include "external_eeprom.h"
#include "lcd.h"
#include "keypad.h"

int main(void)
{

	unsigned char key;
	uint8 val = 1;
	/*Init LCD*/
	LCD_init();
	LCD_displayStringRowColumn(0,0,"Hello ^^");
	
	/* Init EEPROM */
	EEPROM_init();

	while(1){
		/* if any switch pressed for more than 500 ms it counts more than one press */
		key = KeyPad_getPressedKey(); /* get the pressed key number */
		if((key <= 9) && (key >= 0))
		{
			EEPROM_writeByte(0x0311, key); /* Write 0x0F in the external EEPROM */
			LCD_intgerToString(	EEPROM_readByte(0x0311, &key) /* Read 0x0F from the external EEPROM */); /* display the pressed keypad switch */
		}
		else if(key == 13){
			LCD_clearScreen();
			_delay_ms(500);
		    LCD_intgerToString(	EEPROM_readByte(0x0311, &val));

		}
		else
		{
			EEPROM_writeByte(0x0311, key); /* Write 0x0F in the external EEPROM */
			LCD_intgerToString(	EEPROM_readByte(0x0311, &key) /* Read 0x0F from the external EEPROM */); /* display the pressed keypad switch */
		}
		_delay_ms(500); /* Press time */
	}
	return 0;
}
