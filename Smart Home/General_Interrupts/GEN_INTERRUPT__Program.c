/*
 * Author   : Ahmed Mohamed Aboud
 * Linkedin :https://www.linkedin.com/in/ahmed-mohamed-aboud-33b2471b1/
 * File Name: GEN_INTERRUPT__Program.c
 * Date: 17 Dec 2023
 */

#include "../DIO/STD_Types.h"
#include "../DIO/bitmath.h"

#include "../DIO/DIO_Interface.h"

#include "GEN_INTERRUPT__CFG.h"
#include "GEN_INTERRUPT__Reg.h"
#include "GEN_INTERRUPT__Private.h"
#include "GEN_INTERRUPT__Interacing.h"

void GENERAL_INTERRUPT_enableInterrupt()
{
	SET_BIT(SREG,GENERAL_INTERRUPT_PIN);
}
void GENERAL_INTERRUPT_disableInterrupt()
{
	CLEAR_BIT(SREG,GENERAL_INTERRUPT_PIN);
}
