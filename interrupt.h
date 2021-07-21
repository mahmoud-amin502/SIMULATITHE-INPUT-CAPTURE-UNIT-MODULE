/*
 * interrupt.h
 *
 *  Created on: Nov 28, 2020
 *      Author: MRM
 */

#ifndef INTERRUPT_H_
#define INTERRUPT_H_

#include "micro_config.h"
#include "std_types.h"
#include "common_macros.h"


typedef enum
{
	FALLING,RISING
}INT_EdgeType;


void timer1_intiNormal();
void INT0_INITIAL();


void change_edge(INT_EdgeType edge);
uint16 counter1_Value();

void interrupt_Stop();


#endif /* INTERRUPT_H_ */
