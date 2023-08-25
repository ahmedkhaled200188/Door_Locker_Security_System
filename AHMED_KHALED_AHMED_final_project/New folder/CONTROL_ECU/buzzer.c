/*
 * buzzer.c
 *
 *  Created on: Aug 19, 2023
 *      Author: AHMED KHALED
 */
#include "buzzer.h"
void Buzzer_init(void)
{
	GPIO_setupPinDirection(PORTC_ID, PIN5_ID, PIN_OUTPUT);
	GPIO_writePin(PORTC_ID, PIN5_ID, LOGIC_LOW);
}
void Buzzer_on(void)
{
	GPIO_writePin(PORTC_ID, PIN5_ID, LOGIC_HIGH);

}
void Buzzer_off(void)
{
	GPIO_writePin(PORTC_ID, PIN5_ID, LOGIC_LOW);
}
