/*
 * BUZZER_Program.c
 *
 *  Created on: 9 Dec 2023
 *      Author: user
 */


#include "../DIO/STD_Types.h"
#include "../DIO/bitmath.h"

#include "../DIO/DIO_Interface.h"
#include "BUZZER_Reg.h"
#include "BUZZER_Private.h"
#include "BUZZER_cfg.h"
#include "BUZZER_Interface.h"

uint8 BUZZER_turnOn(uint8 BUZZER_port, uint8 BUZZER_pin)
{
	uint8 local_errorSignal = OK_STAT;
	local_errorSignal = DIO_setPinValue(BUZZER_port,BUZZER_pin,HIGH);
	return local_errorSignal;
}

uint8 BUZZER_turnOff(uint8 BUZZER_port, uint8 BUZZER_pin)
{
	uint8 local_errorSignal = OK_STAT;
	local_errorSignal = DIO_setPinValue(BUZZER_port,BUZZER_pin,LOW);
	return local_errorSignal;
}




