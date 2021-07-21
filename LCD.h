/*
 * LCD.h
 *
 *  Created on: Nov 4, 2020
 *      Author: MRM
 */

#ifndef LCD_H_
#define LCD_H_


#include "micro_config.h"
#include "std_types.h"
#include "common_macros.h"


#define RS PD4
#define RW PD5
#define E  PD7



void LCD_sendCommand(uint8 command);
void LCD_Init(void);
void LCD_displayChar(uint8 data);

void LCD_displayString(char * str);
void LCD_goToRowColumn(uint8 row, uint8 col);
void LCD_displayStringRowColumn(uint8 row,uint8 col, char *Str);
void LCD_clearScreen();
void LCD_integerToString(int num);


#endif /* LCD_H_ */
