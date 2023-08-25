/*
 * pwm.h
 *
 *  Created on: Jun 27, 2023
 *      Author: Dell
 */
#include "common_macros.h"
#include "gpio.h"
#include "avr/io.h"
#ifndef PWM_H_
#define PWM_H_

void PWM_Timer0_Start(uint8 duty_cycle);

#endif /* PWM_H_ */
