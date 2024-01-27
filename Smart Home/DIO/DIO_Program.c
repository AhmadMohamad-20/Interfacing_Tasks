/*
 * DIO_program.c
 *
 *  Created on: 8 Dec 2023
 *      Author: user
 */

#include "STD_Types.h"
#include "bitmath.h"

#include "DIO_cfg.h"
#include "DIO_Private.h"
#include "DIO_Reg.h"
#include "DIO_Interface.h"

uint8 DIO_setPinDirection(uint8 copy_DIO_port, uint8 copy_DIO_pin, uint8 copy_DIO_direction)
{
	uint8 local_errorState = OK_STAT;
	if (copy_DIO_pin <= PIN7)
	{
		if (copy_DIO_direction == OUTPUT)
		{
			switch (copy_DIO_port)
			{
				case DIO_PORTA:
					SET_BIT(DDRA,copy_DIO_pin);
					break;
				case DIO_PORTB:
					SET_BIT(DDRB,copy_DIO_pin);
					break;
				case DIO_PORTC:
					SET_BIT(DDRC,copy_DIO_pin);
					break;
				case DIO_PORTD:
					SET_BIT(DDRD,copy_DIO_pin);
					break;
				default:
					local_errorState = NOT_OK_STAT;
			}
		}
		else if (copy_DIO_direction == INPUT)
		{
			switch (copy_DIO_port)
			{
				case DIO_PORTA:
					CLEAR_BIT(DDRA,copy_DIO_pin);
					break;
				case DIO_PORTB:
					CLEAR_BIT(DDRB,copy_DIO_pin);
					break;
				case DIO_PORTC:
					CLEAR_BIT(DDRC,copy_DIO_pin);
					break;
				case DIO_PORTD:
					CLEAR_BIT(DDRD,copy_DIO_pin);
					break;
				default:
					local_errorState = NOT_OK_STAT;
			}
		}
		else
		{
			local_errorState = NOT_OK_STAT;
		}
	}
	else
	{
		local_errorState = NOT_OK_STAT;
	}

	return local_errorState;
}

uint8 DIO_setPinValue(uint8 copy_DIO_port, uint8 copy_DIO_pin, uint8 copy_DIO_value)
{
	uint8 local_errorSignal = OK_STAT;
	if (copy_DIO_pin <= PIN7)
	{
		if (copy_DIO_value == HIGH)
		{
			switch(copy_DIO_port)
			{
				case DIO_PORTA:
					SET_BIT(PORTA,copy_DIO_pin);
					break;
				case DIO_PORTB:
					SET_BIT(PORTB,copy_DIO_pin);
					break;
				case DIO_PORTC:
					SET_BIT(PORTC,copy_DIO_pin);
					break;
				case DIO_PORTD:
					SET_BIT(PORTD,copy_DIO_pin);
					break;
				default:
					local_errorSignal = NOT_OK_STAT;
					break;
			}
		}
		else if(copy_DIO_value == LOW)
		{
			switch(copy_DIO_port)
			{
				case DIO_PORTA:
					CLEAR_BIT(PORTA,copy_DIO_pin);
					break;
				case DIO_PORTB:
					CLEAR_BIT(PORTB,copy_DIO_pin);
					break;
				case DIO_PORTC:
					CLEAR_BIT(PORTC,copy_DIO_pin);
					break;
				case DIO_PORTD:
					CLEAR_BIT(PORTD,copy_DIO_pin);
					break;
				default:
					local_errorSignal = NOT_OK_STAT;
					break;
			}
		}
		else
		{
			local_errorSignal = NOT_OK_STAT;
		}
	}
	else
	{
		local_errorSignal = NOT_OK_STAT;
	}
	return local_errorSignal;
}

uint8 DIO_ReadPinValue(uint8 copy_DIO_port, uint8 copy_DIO_pin,  uint8 *copy_DIO_pValue)
{
	uint8 local_errorState = OK_STAT;
	if ((copy_DIO_pin <= PIN7) && (copy_DIO_pValue != NULL))
	{
		switch (copy_DIO_port)
		{
			case DIO_PORTA:
				*copy_DIO_pValue = GET_BIT(PINA,copy_DIO_pin);
				break;
			case DIO_PORTB:
				*copy_DIO_pValue = GET_BIT(PINB,copy_DIO_pin);
				break;
			case DIO_PORTC:
				*copy_DIO_pValue = GET_BIT(PINC,copy_DIO_pin);
				break;
			case DIO_PORTD:
				*copy_DIO_pValue = GET_BIT(PIND,copy_DIO_pin);
				break;
			default:
				local_errorState = NOT_OK_STAT;
				break;
		}
	}
	else
	{
		local_errorState = NOT_OK_STAT;
	}
	return local_errorState;
}

uint8 DIO_setPortDirection(uint8 copy_DIO_port,  uint8 copy_DIO_direction)
{
	uint8 local_errorSignal = OK_STAT;
	if ((copy_DIO_direction == PORT_OUTPUT) || (copy_DIO_direction == PORT_INPUT))
		{
			switch (copy_DIO_port)
			{
				case DIO_PORTA:
					DDRA = copy_DIO_direction;
					break;
				case DIO_PORTB:
					DDRB = copy_DIO_direction;
					break;
				case DIO_PORTC:
					DDRC = copy_DIO_direction;
					break;
				case DIO_PORTD:
					DDRD = copy_DIO_direction;
					break;
				default:
					local_errorSignal = NOT_OK_STAT;
					break;
			}
		}
	return local_errorSignal;
}

uint8 DIO_setPortValue(uint8 copy_DIO_port, uint8 copy_DIO_value)
{
	uint8 local_errorSignal = OK_STAT;

	switch (copy_DIO_port)
	{
		case DIO_PORTA:
			PORTA = copy_DIO_value;
			break;
		case DIO_PORTB:
			PORTB = copy_DIO_value;
			break;
		case DIO_PORTC:
			PORTC = copy_DIO_value;
			break;
		case DIO_PORTD:
			PORTD = copy_DIO_value;
			break;
		default:
			local_errorSignal = NOT_OK_STAT;
	}
	return local_errorSignal;
}

uint8 DIO_ReadPortValue(uint8 copy_DIO_port,  uint8 *copy_DIO_pValue)
{
	uint8 local_errorSignal = OK_STAT;
	if ((copy_DIO_port <= DIO_PORTD) && (copy_DIO_pValue != NULL))
	{
		switch (copy_DIO_port)
		{
			case DIO_PORTA:
				*copy_DIO_pValue = PINA;
				break;
			case DIO_PORTB:
				*copy_DIO_pValue = PINB;
				break;
			case DIO_PORTC:
				*copy_DIO_pValue = PINC;
				break;
			case DIO_PORTD:
				*copy_DIO_pValue = PIND;
				break;
			default:
				local_errorSignal = NOT_OK_STAT;
				break;
		}
	}

	return local_errorSignal;
}

uint8 DIO_setIntPullUpRes(uint8 copy_DIO_port, uint8 copy_DIO_pin)
{
	uint8 local_errorSignal = OK_STAT;
	local_errorSignal = DIO_setPinDirection(copy_DIO_port,copy_DIO_pin,INPUT);
	if (local_errorSignal == OK_STAT)
	{
		local_errorSignal = DIO_setPinValue(copy_DIO_port,copy_DIO_pin,HIGH);
	}
	return local_errorSignal;
}
