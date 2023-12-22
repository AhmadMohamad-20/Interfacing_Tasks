/*
 * DIO_Program.c
 *
 *  Created on: 10 Dec 2023
 *      Author: user
 */

#include "STD_Types.h"
#include "bitmath.h"

#include "DIO_Reg.h"
#include "DIO_cfg.h"
#include "DIO_Private.h"
#include "DIO_interface.h"

void DIO_initalizePorts()
{
	DDRA = PORTA_DIR;
	DDRB = PORTB_DIR;
	DDRC = PORTC_DIR;
	DDRD = PORTD_DIR;
	PORTA = PORTA_VALUE;
	PORTB = PORTB_VALUE;
	PORTC = PORTC_VALUE;
	PORTD = PORTD_VALUE;
}
