/*
 * LCD.c
 *
 *  Created on: Nov 4, 2020
 *      Author: MRM
 */

#include "LCD.h"


void LCD_sendCommand(uint8 command)
{
	CLEAR_BIT(PORTD,RS);  //RS pin
	CLEAR_BIT(PORTD,RW);  //R/W pin

	_delay_ms(1);

	SET_BIT(PORTD,E);   //Enable pin
	_delay_ms(1);

	PORTC = command;
	_delay_ms(1);

	CLEAR_BIT(PORTD,E);
	_delay_ms(1);

}

void LCD_Init(void)
{
	DDRD |= (1<<RS) | (1<<RW) | (1<<E);
	DDRC = 0xff;   // PORTC direction is output

	LCD_sendCommand(0x38);     //2 lines and 8 bit connection mode
	LCD_sendCommand(0x0c);     //display on cursor off
	LCD_sendCommand(0x01);     //clear display screen

}


void LCD_displayChar(uint8 data)
{
	SET_BIT(PORTD,RS);  //RS pin
	CLEAR_BIT(PORTD,RW);  //R/W pin

	_delay_ms(1);

	SET_BIT(PORTD,E);   //Enable pin
	_delay_ms(1);

	PORTC = data;
	_delay_ms(1);

	CLEAR_BIT(PORTD,E);
	_delay_ms(1);

}




void LCD_displayString(char * str)
{
	uint8 i=0;
	while(*str != '\0')
	{
		if(i<16)
		{
			LCD_displayChar(*str);
			str++;
			++i;
		}

		else
		{
			LCD_goToRowColumn(2,((i-16)+1));
			LCD_displayChar(*str);
			str++;
			i++;

		}

	}
}



void LCD_goToRowColumn(uint8 row, uint8 col)
{

	uint8 address;

	row-=1;
	col-=1;


	switch (row)
	{
	case 0:
		address = col;
		break;

	case 1:
		address = 0x40 + col;
		break;

	case 2:
		address = 0x10 + col;
		break;

	case 3:
		address = 0x50 + col;
		break;
	}


	LCD_sendCommand((address | 0x80));
}


void LCD_displayStringRowColumn(uint8 row,uint8 col, char *Str)
{
	LCD_goToRowColumn(row, col);
	LCD_displayString(Str);
}



void LCD_clearScreen()
{
	LCD_sendCommand(0x01);
}


void LCD_integerToString(int num)
{
	char *buffer[16];
	itoa(num,buffer,10);
	LCD_displayString(buffer);
}
