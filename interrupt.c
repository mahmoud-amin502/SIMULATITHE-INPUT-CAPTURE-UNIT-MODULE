/*
 * interrupt.c
 *
 *  Created on: Nov 28, 2020
 *      Author: MRM
 */


#include "interrupt.h"
static volatile void (*g_callback)(void) = NULL_PTR;


ISR(INT0_vect)
{
	if(g_callback != NULL_PTR)
	{
		(*g_callback)();
	}
}


void timer1_intiNormal()
{
	TCNT1 = 0;
	TCCR1A = (1<<FOC1A) | (1<<FOC1B);
	TCCR1B = (1<<CS10) | (1<<CS11);
}


void INT0_INITIAL()
{
	SREG |= (1<<7);
	DDRD &= (~(1<<PD2));
	GICR |= (1<<6);
	MCUCR |= (1<<ISC00) | (1<<ISC01);
}


void set_CallBack(void (*ptr)(void))
{

	g_callback = ptr;

}

void change_edge(INT_EdgeType edge)
{
	MCUCR = 0;
	MCUCR |= (edge<<ISC00) | (1<<ISC01);
}

uint16 counter1_Value()
{
	return TCNT1 ;
}

void interrupt_Stop()
{
	SREG &= (~(1<<7));
	TCCR1B = 0;
}
