/*
 * control.c
 *
 * Created on: Aug 24, 2023
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

/* Global variables */
uint8 Tick = 0;
uint8 resivedpass[6];

/* Function to change the password */
void changePassword(void) {
    uint8 pass[6] = {0, 0, 0, 0, 0};
    uint8 pass2[6] = {0, 0, 0, 0, 0};

    /* Send "ready" signal to start receiving password */
    UART_sendByte(ready);
    UART_receiveString(pass);

    /* Send "ready" signal to start receiving the second password */
    UART_sendByte(ready);
    UART_receiveString(pass2);

    int i = 0;
    for (i = 1; i < 5; i++) {
        if (pass[i] != pass2[i])
            UART_sendByte(not_match);
    }
    for (i = 0; i < 5; i++) {
        /* Write the new password to EEPROM */
        EEPROM_writeByte((100 + i), pass[i]);
        _delay_ms(10);
    }

    /* Send success match signal */
    UART_sendByte(match);
}

/* Function to compare the entered password with the stored password */
void ComparePassword(void) {
    uint8 EEPROM_pass[6] = {1, 2, 3, 4, 5};

    /* Send Compare_Password command */
    UART_sendByte(Compare_Password);

    /* Receive the entered password */
    UART_receiveString(resivedpass);

    int i = 0;
    for (i = 1; i < 5; i++) {
        /* Read the stored password from EEPROM */
        EEPROM_readByte((100 + i), &EEPROM_pass[i]);
        _delay_ms(10);
    }

    for (i = 1; i < 5; i++) {
        if (EEPROM_pass[i] != resivedpass[i]) {
            /* Send not match signal */
            UART_sendByte(not_match);
        }
    }

    /* Send match signal */
    UART_sendByte(match);
}

/* Function to control the door opening process */
void OpenDoor(void) {
    if (Tick == 0) {
        /* Rotate the motor in clockwise direction */
        DcMotor_Rotate(CW, 100);
    } else if (Tick == 5) {
        /* Stop the motor */
        DcMotor_Rotate(STOP, 0);
    } else if (Tick == 6) {
        /* Rotate the motor in anti-clockwise direction */
        DcMotor_Rotate(A_CW, 100);
    } else if (Tick == 11) {
        /* Stop the motor and deinitialize Timer1 */
        DcMotor_Rotate(STOP, 0);
        Timer1_deInit();
        Tick = -1;
    }
    Tick++;
}
