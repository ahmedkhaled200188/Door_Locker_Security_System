/*
 * TIMER1.c
 *
 *  Created on: Aug 5, 2023
 *      Author: ahmed khaled ahmed
 */
#include "TIMER1.h"
#include <avr/io.h>
#include <avr/interrupt.h>
void (*call_back)(void);
Timer1_ConfigType * Timer1_Config_Ptr;
void Timer1_init(const Timer1_ConfigType * Config_Ptr)
{
	SREG|=(1<<7);
	Timer1_Config_Ptr=Config_Ptr;
	TCCR1B|=(Config_Ptr->prescaler>>0);
	TCNT1=Config_Ptr->initial_value;
	if(Config_Ptr->mode==normal)
	{
		TCCR1B&=~(1<<WGM12);
		TIMSK|=(1<<TOIE1);//Overflow Interrupt Enable

	}
	else if(Config_Ptr->mode==compare)
	{
		TCCR1B|=(1<<WGM12);
		OCR1A = Config_Ptr->compare_value;
		TIMSK |= (1 << OCIE1A);//Output Compare A Match Interrupt Enable
	}

}
void Timer1_deInit(void)
{
	TCCR1B=0;
	TIMSK&=~(1<<TOIE1);
	TIMSK&=~(1<<OCIE1A);

}
void Timer1_setCallBack(void(*a_ptr)(void))
{
	call_back=a_ptr;
}
ISR(TIMER1_COMPA_vect)
{
	call_back();
	TCNT1=Timer1_Config_Ptr->initial_value;

}
ISR(TIMER1_OVF_vect)
{
	call_back();
	TCNT1=Timer1_Config_Ptr->initial_value;
}


