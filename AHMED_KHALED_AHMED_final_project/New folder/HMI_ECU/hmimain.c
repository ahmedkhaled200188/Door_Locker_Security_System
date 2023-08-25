/*
 * hmimain.c
 *
 * Created on: Aug 19, 2023
 * Author: AHMED KHALED
 */

#include "hmi.h"

/* Enumeration for command comparison results */
typedef enum {
    not_match,
    match
} tfCommands;

/* Enumeration for application commands */
typedef enum {
    NO_COMMAND,
    OPEN_DOOR_COMMAND = 0x10,
    CHANGE_PASSWORD_COMMAND = 0x11,
    ALARM_COMMAND = 0x12,
    Compare_Password = 0xaa
} APP_Commands;

/* Global variables */
extern uint8 comm = 0, Tick;
UART_ConfigType UART_ptr;
Timer1_ConfigType TIMER_ptr;

int main(void) {
    /* Timer1 configuration */
    TIMER_ptr.mode = compare;
    TIMER_ptr.compare_value = 23440; // 3 seconds
    TIMER_ptr.initial_value = 0;
    TIMER_ptr.prescaler = F_CPU_1024;
    Timer1_setCallBack(step3);

    /* UART configuration */
    UART_ptr.baud_rate = UART_BAUD_9600;
    UART_ptr.bit_data = UART_8_BITS;
    UART_ptr.parity = UART_PARITY_NONE;
    UART_ptr.stop_bit = UART_STOP_1_BIT;
    UART_init(&UART_ptr);

    /* Initialize LCD and execute Step1 */
    LCD_init();
    Step1();

    while (1) {
        LCD_clearScreen();
        LCD_displayString("+ : Open Door");
        LCD_displayStringRowColumn(1, 0, "- : change pass ");

        /* Get user's command from the keypad */
        comm = KEYPAD_getPressedKey();

        if (comm == '+') {
            if (step2() == match) {
                /* Send OPEN_DOOR_COMMAND to control ECU */
                UART_sendByte(OPEN_DOOR_COMMAND);
                Timer1_init(&TIMER_ptr);
                step3();

                /* Wait until Tick is reset */
                while (Tick != 0);
            }
        } else if (comm == '-') {
            if (step2() == match) {
                LCD_clearScreen();
                LCD_displayString("change pass");
                _delay_ms(1000);
                Step1();
            }
        } else {
            /* Do nothing for other keys */
        }
    }
}
