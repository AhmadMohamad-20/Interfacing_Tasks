/*
 * BUTTON_Program.c
 *
 *  Created on: 9 Dec 2023
 *      Author: user
 */


#include "STD_Types.h"
#include "bitmath.h"
#include "BTN_cfg.h"
#include "BTN_Reg.h"
#include "BTN_Private.h"
#include "BTN_Interface.h"

#include "../DIO/DIO_Interface.h"


uint8 BTN_readButtonState(uint8 copy_BTN_port,uint8 copy_BTN_pin, uint8 *copy_BTN_state)
{
	uint8 local_errorStat = OK_STAT;
	local_errorStat = DIO_ReadPinValue(copy_BTN_port,copy_BTN_pin,copy_BTN_state);
	return local_errorStat;
}
