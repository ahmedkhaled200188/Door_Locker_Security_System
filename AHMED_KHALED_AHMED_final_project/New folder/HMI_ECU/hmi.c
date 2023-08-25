/*
 * hmi.c
 *
 * Created on: Aug 25, 2023
 * Author: AHMED KHALED
 */

#include "hmi.h"

/* Enumeration for command comparison results */
typedef enum {
    not_match,
    match
} tfCommands;

/* Enumeration for different application commands */
typedef enum {
    NO_COMMAND,
    OPEN_DOOR_COMMAND = 0x10,
    CHANGE_PASSWORD_COMMAND = 0x11,
    ALARM_COMMAND = 0x12,
    Compare_Password = 0xaa
} APP_Commands;

/* Global variable to track time intervals */
extern uint8 Tick = 0;
uint8 pass[6];
uint8 pass2[6];
uint8 pass3[6];

/* Function to handle Changing the password */
void Step1(void) {
    /* Send CHANGE_PASSWORD_COMMAND to initiate password change */
    UART_sendByte(CHANGE_PASSWORD_COMMAND);

    /* Clear the LCD screen */
    LCD_clearScreen();

    /* Display message for user to enter the new password */
    LCD_displayString("plz enter pass:");

    /* Wait until a valid key is pressed (not '=' or 17) */
    while (KEYPAD_getPressedKey() == '=' | KEYPAD_getPressedKey() == 17);

    int i = 0;
    pass[5] = '\0';

    /* Read and display the password with '*' masking */
    for (i = 0; i < 5; i++) {
        pass[i] = KEYPAD_getPressedKey();
        LCD_displayStringRowColumn(1, i, "*");
        _delay_ms(500);
    }
    pass[5] = '#';

    /* Wait until the '=' key is pressed */
    while (KEYPAD_getPressedKey() != '=');

    /* Clear the LCD screen */
    LCD_clearScreen();

    /* Display message for user to re-enter the same password */
    LCD_displayString("Please re-enter the same Pass");
    _delay_ms(500);

    /* Read and display the second password entry with '*' masking */
    for (i = 0; i < 5; i++) {
        pass2[i] = KEYPAD_getPressedKey();
        LCD_displayStringRowColumn(1, i, "*");
        _delay_ms(500);
    }
    pass2[5] = '#';

    /* Wait until the '=' key is pressed */
    while (KEYPAD_getPressedKey() != '=');

    /* Send the first password to the receiver (CONTROL ECU) */
    sendPassword1();
}

/* Function to send the first password to the receiver */
void sendPassword1(void) {
    /* Send CHANGE_PASSWORD_COMMAND to receiver */
    UART_sendByte(CHANGE_PASSWORD_COMMAND);

    /* Wait until the receiver is ready */
    while (UART_recieveByte() != ready);

    /* Send the second password to receiver */
    UART_sendString(pass2);

    /* Proceed to send the second part of the password */
    sendPassword2();
}

/* Function to send the second part of the password and compare */
void sendPassword2(void) {
    uint8 received_compare_result;

    /* Wait until the receiver is ready */
    while (UART_recieveByte() != ready);

    /* Send the first password to compare */
    UART_sendString(pass);

    /* Get the received password compare result from UART */
    received_compare_result = UART_recieveByte();

    /* If the two entered passwords do not match */
    if (received_compare_result == not_match) {
        /* Display error message and retry Step1 */
        LCD_clearScreen();
        LCD_displayString("not match");
        _delay_ms(1000);
        Step1();
    } else if (received_compare_result == match) {
        /* Display success message */
        LCD_clearScreen();
        LCD_displayString("match");
        _delay_ms(1000);
        return;
    }
}

/* Function to compare the entered password with the stored password */
void comparepassword(void) {
    /* Send Compare_Password command to initiate password comparison */
    UART_sendByte(Compare_Password);

    /* Wait until the receiver is ready for password comparison */
    while (UART_recieveByte() != Compare_Password);

    /* Send the third password to compare */
    UART_sendString(pass3);
}

/* Function to perform matching the password with the saved one */
uint8 step2(void) {
    uint8 count = 0;
    uint8 compare_value;

    /* Loop for a maximum of 3 attempts */
    while (count < 3) {
        LCD_clearScreen();
        LCD_displayString("plz enter pass:");
        int i = 0;

        /* Wait until valid key is pressed (not '+', '-', '=' or 17) */
        while (KEYPAD_getPressedKey() == '+' | KEYPAD_getPressedKey() == '-' | KEYPAD_getPressedKey() == '=' | KEYPAD_getPressedKey() == 17);

        /* Read and display the third password entry with '*' masking */
        for (i = 0; i < 5; i++) {
            pass3[i] = KEYPAD_getPressedKey();
            LCD_displayStringRowColumn(1, i, "*");
            _delay_ms(500);
        }
        pass3[5] = '#';

        /* Wait until the '=' key is pressed */
        while (KEYPAD_getPressedKey() != '=');

        /* Compare the entered password with the stored one */
        comparepassword();

        /* Receive the comparison result from UART */
        compare_value = UART_recieveByte();

        /* If the entered password matches */
        if (compare_value == match) {
            return match;
        }
        count++;
    }

    /* If the password entries exceeded the limit, send an ALARM_COMMAND */
    UART_sendByte(ALARM_COMMAND);
    LCD_clearScreen();
    LCD_displayString("error");
    /* Delay one min error */
    uint8 i = 0;
    for (i = 0; i < 60; i++) {
        _delay_ms(1000);
    }
    return not_match;
}

/* Function to Handle the motor open and close state */
void step3(void) {

    if (Tick == 0) {
        LCD_clearScreen();
        LCD_displayString("Door is Unlocking");
    } else if (Tick == 5) {
        LCD_clearScreen();
        LCD_displayString("Door is Unlocked");
    } else if (Tick == 6) {
        LCD_clearScreen();
        LCD_displayString("Door is locking");
    } else if (Tick == 11) {
        /* Deinitialize Timer1 and reset Tick */
        Timer1_deInit();
        Tick = -1;
    }
    Tick++;
}
