/*
 * LED_Program.c
 *
 *  Created on: 9 Dec 2023
 *      Author: user
 */

#include "../DIO/STD_Types.h"
#include "../DIO/bitmath.h"

#include "../DIO/DIO_Interface.h"

#include "LED_cfg.h"
#include "LED_Private.h"
#include "LED_Reg.h"
#include "LED_Interface.h"

uint8 LED_turnOn(uint8 copy_LED_port,uint8 copy_LED_pin)
{
	uint8 local_errorSignal = OK_STAT;
	local_errorSignal = DIO_setPinValue(copy_LED_port,copy_LED_pin,HIGH);
	return local_errorSignal;
}

uint8 LED_turnOff(uint8 copy_LED_port,uint8 copy_LED_pin)
{
	uint8 local_errorSignal = OK_STAT;
	local_errorSignal = DIO_setPinValue(copy_LED_port,copy_LED_pin,LOW);
	return local_errorSignal;
}

uint8 LED_toggle(uint8 copy_LED_port,uint8 copy_LED_pin)
{
	uint8 local_errorSignal = OK_STAT;
	local_errorSignal = DIO_togglePin(copy_LED_port,copy_LED_pin);
	return local_errorSignal;
}
