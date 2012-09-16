################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../includes/lib/leds.c \
../includes/lib/switches.c 

OBJS += \
./includes/lib/leds.o \
./includes/lib/switches.o 

C_DEPS += \
./includes/lib/leds.d \
./includes/lib/switches.d 


# Each subdirectory must supply rules for building sources it contributes
includes/lib/%.o: ../includes/lib/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega8515 -DF_CPU=1000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


