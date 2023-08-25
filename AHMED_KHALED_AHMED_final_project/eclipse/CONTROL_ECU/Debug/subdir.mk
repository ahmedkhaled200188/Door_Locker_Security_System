################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../TIMER1.c \
../buzzer.c \
../control.c \
../controlmain.c \
../dc.c \
../external_eeprom.c \
../gpio.c \
../pwm.c \
../twi.c \
../uart.c 

OBJS += \
./TIMER1.o \
./buzzer.o \
./control.o \
./controlmain.o \
./dc.o \
./external_eeprom.o \
./gpio.o \
./pwm.o \
./twi.o \
./uart.o 

C_DEPS += \
./TIMER1.d \
./buzzer.d \
./control.d \
./controlmain.d \
./dc.d \
./external_eeprom.d \
./gpio.d \
./pwm.d \
./twi.d \
./uart.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


