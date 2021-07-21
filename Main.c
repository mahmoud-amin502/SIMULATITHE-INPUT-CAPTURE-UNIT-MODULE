/*
 * Main.c
 *
 *  Created on: Nov 22, 2020
 *      Author: MRM
 */



#include "LCD.h"
#include "interrupt.h"

uint8 edgeCount = 0;
uint16 T10 = 0;
uint16 T11 = 0;

uint16 T20 = 0;
uint16 T21 = 0;

uint16 T1 ;
uint16 T2 ;
uint16 T3 ;

void APP_edgeProcessing()
{
	edgeCount ++;
	if(edgeCount == 1)
	{
		T10 = counter1_Value();
		change_edge(FALLING);
	}

	else if(edgeCount == 2)
	{
		T11 = counter1_Value();
		change_edge(RISING);
	}

	else if(edgeCount == 3)
	{
		T20 = counter1_Value();
		change_edge(FALLING);
	}

	else if(edgeCount == 4)
	{
		T21 = counter1_Value();
		interrupt_Stop();
	}
}


int main(void)
{
	uint16 duty = 0;
	set_CallBack(APP_edgeProcessing);

	LCD_Init();
	LCD_clearScreen();

	timer1_intiNormal();
	INT0_INITIAL();




	while(1)
	{
		if(edgeCount == 4)
		{
			interrupt_Stop();

			T1 = T11 -T10;
			T2 = T20 - T10;
			T3 = T21 - T10;


			edgeCount = 0;

			LCD_displayString("Duty = ");

			duty = (((float)(T3 - T2)/(float)(T3 - T1))) * 100;

			LCD_integerToString(duty);

			LCD_displayString("%");
		}

	}
}
