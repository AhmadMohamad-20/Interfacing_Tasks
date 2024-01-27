################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../DIO_INTERRUPT/DIO_INTERRUPT_Program.c 

OBJS += \
./DIO_INTERRUPT/DIO_INTERRUPT_Program.o 

C_DEPS += \
./DIO_INTERRUPT/DIO_INTERRUPT_Program.d 


# Each subdirectory must supply rules for building sources it contributes
DIO_INTERRUPT/%.o: ../DIO_INTERRUPT/%.c DIO_INTERRUPT/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g3 -gdwarf-2 -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


