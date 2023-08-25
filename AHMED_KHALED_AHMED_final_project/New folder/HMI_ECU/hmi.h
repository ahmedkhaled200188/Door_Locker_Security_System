/*
 * hmi.h
 *
 * Created on: Aug 25, 2023
 * Author: AHMED KHALED
 */

#ifndef HMI_H_
#define HMI_H_

#include "keypad.h"   /* Include the keypad library */
#include "lcd.h"      /* Include the LCD library */
#include "TIMER1.h"   /* Include the TIMER1 library */
#include "uart.h"     /* Include the UART library */
#include <avr/delay.h>

#define ready 0xaa    /* Define a constant for "ready" command */

/* Declare global variables */
uint8 comm, Tick;

/* Function declarations */
void Step1(void);            /* Function to handle Step 1 of the password change process */
uint8 step2(void);           /* Function to get a password from user and
								perform matching the password with the saved one */
void step3(void);            /* Function to Handle the motor open and close state */
void sendPassword1(void);    /* Function to send the first password to the receiver */
void sendPassword2(void);    /* Function to send the second part of the password and compare */
void comparepassword(void);  /* Function to compare the entered password with the stored password */

#endif /* HMI_H_ */
