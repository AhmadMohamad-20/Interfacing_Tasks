################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../DIO_autosar/DIO_Program.c 

OBJS += \
./DIO_autosar/DIO_Program.o 

C_DEPS += \
./DIO_autosar/DIO_Program.d 


# Each subdirectory must supply rules for building sources it contributes
DIO_autosar/%.o: ../DIO_autosar/%.c DIO_autosar/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g3 -gdwarf-2 -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


