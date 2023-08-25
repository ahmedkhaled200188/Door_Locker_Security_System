/*
 * controlmain.c
 *
 * Created on: Aug 19, 2023
 * Author: AHMED KHALED
 */

#include "control.h"

/* Enumeration for application commands */
typedef enum {
    NO_COMMAND,
    OPEN_DOOR_COMMAND = 0x10,
    CHANGE_PASSWORD_COMMAND = 0x11,
    ALARM_COMMAND = 0x12,
    Compare_Password = 0xaa
} APP_Commands;

/* Enumeration for command comparison results */
typedef enum {
    not_match,
    match
} tfCommands;

/* Configuration structures */
UART_ConfigType UART_ptr;
Timer1_ConfigType TIMER_ptr;
TWI_ConfigType twi_ptr;

/* Global variable for command */
uint8 command;

int main(void) {
    /* UART configuration */
    UART_ptr.baud_rate = UART_BAUD_9600;
    UART_ptr.bit_data = UART_8_BITS;
    UART_ptr.parity = UART_PARITY_NONE;
    UART_ptr.stop_bit = UART_STOP_1_BIT;
    UART_init(&UART_ptr);

    /* Timer1 configuration */
    TIMER_ptr.mode = compare;
    TIMER_ptr.compare_value = 23440; // 3 seconds
    TIMER_ptr.initial_value = 0;
    TIMER_ptr.prescaler = F_CPU_1024;
    Timer1_setCallBack(OpenDoor);

    /* TWI (I2C) configuration */
    twi_ptr.address = 0x01;
    twi_ptr.bit_rate = 400000;
    TWI_init(&twi_ptr);

    /* Initialize DC motor and buzzer */
    DcMotor_Init();
    Buzzer_init();

    while (1) {
        /* Receive command from HMI ECU */
        command = UART_recieveByte();

        /* Execute the received command from HMI ECU */
        switch (command) {
            case Compare_Password:
                ComparePassword();
                break;
            case OPEN_DOOR_COMMAND:
                Timer1_init(&TIMER_ptr);
                OpenDoor(); // to open the door for the first time
                break;
            case CHANGE_PASSWORD_COMMAND:
                changePassword();
                break;
            case ALARM_COMMAND: {
                Buzzer_on();
                uint8 i = 0;
                for (i = 0; i < 60; i++) {
                    _delay_ms(1000);
                }
                Buzzer_off();
            }
            break;
            case NO_COMMAND:
                break;
            default:
                ; /* do nothing */
        }
    }
}
