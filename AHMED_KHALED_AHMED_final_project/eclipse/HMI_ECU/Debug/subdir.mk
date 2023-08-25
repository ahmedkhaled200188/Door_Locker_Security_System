################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../TIMER1.c \
../gpio.c \
../hmi.c \
../hmimain.c \
../keypad.c \
../lcd.c \
../uart.c 

OBJS += \
./TIMER1.o \
./gpio.o \
./hmi.o \
./hmimain.o \
./keypad.o \
./lcd.o \
./uart.o 

C_DEPS += \
./TIMER1.d \
./gpio.d \
./hmi.d \
./hmimain.d \
./keypad.d \
./lcd.d \
./uart.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


