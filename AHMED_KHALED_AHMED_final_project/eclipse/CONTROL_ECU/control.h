/*
 * control.h
 *
 * Created on: Aug 24, 2023
 * Author: AHMED KHALED
 */

#ifndef CONTROL_H_
#define CONTROL_H_

#define ready 0xaa   /* Define a constant for "ready" status */

#include "avr/delay.h"          /* Include AVR delay header */
#include "buzzer.h"             /* Include the buzzer library */
#include "TIMER1.h"             /* Include the TIMER1 library */
#include "uart.h"               /* Include the UART library */
#include "external_eeprom.h"    /* Include the external EEPROM library */
#include "dc.h"                 /* Include the DC motor library */
#include "twi.h"                /* Include the TWI (I2C) library */

/* Function declarations */
void changePassword(void);     /* Function to change the password */
void ComparePassword(void);    /* Function to compare the entered password */
void OpenDoor(void);           /* Function to open the door */

#endif /* CONTROL_H_ */
