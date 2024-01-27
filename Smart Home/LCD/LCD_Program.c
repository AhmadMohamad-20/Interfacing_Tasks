/*
 * LCD_Program.c
 *
 *  Created on: 10 Dec 2023
 *      Author: user
 */
#include <util/delay.h>
#include "../DIO/STD_Types.h"
#include "../DIO/bitmath.h"
#include "../DIO/DIO_Interface.h"

#include "LCD_cfg.h"
#include "LCD_Reg.h"
#include "LCD_Private.h"
#include "LCD_Interface.h"

static uint8 DIO_set4bitsValue(uint8 copy_DIO_PORT, uint8 copy_DIO_value);

uint8 LCD_sendCommand_8bit(uint8 copy_LCD_port, uint8 copy_LCD_command)
{
	uint8 local_errorSignal = OK_STAT;
	local_errorSignal = DIO_setPinValue(LCD_CONTROL_PORT,LCD_RS_PIN,LOW);
	local_errorSignal = DIO_setPinValue(LCD_CONTROL_PORT,LCD_RW_PIN,LOW);
	local_errorSignal = DIO_setPortValue(copy_LCD_port,copy_LCD_command);
	local_errorSignal = DIO_setPinValue(LCD_CONTROL_PORT,LCD_ENABLE_PIN,HIGH);
	_delay_ms(2);
	local_errorSignal = DIO_setPinValue(LCD_CONTROL_PORT,LCD_ENABLE_PIN,LOW);
	return local_errorSignal;
}

uint8 LCD_sendData_8bit(uint8 copy_LCD_port, uint8 copy_LCD_data)
{
	uint8 local_errorSignal = OK_STAT;
	local_errorSignal = DIO_setPinValue(LCD_CONTROL_PORT,LCD_RS_PIN,HIGH);
	local_errorSignal = DIO_setPinValue(LCD_CONTROL_PORT,LCD_RW_PIN,LOW);
	local_errorSignal = DIO_setPortValue(copy_LCD_port,copy_LCD_data);
	local_errorSignal = DIO_setPinValue(LCD_CONTROL_PORT,LCD_ENABLE_PIN,HIGH);
	_delay_ms(2);
	local_errorSignal = DIO_setPinValue(LCD_CONTROL_PORT,LCD_ENABLE_PIN,LOW);
	return local_errorSignal;
}

uint8 LCD_init_8bit(void)
{
	uint8 local_errorSignal = OK_STAT;

	local_errorSignal = DIO_setPortDirection(LCD_DATA_PORT,PORT_OUTPUT);
	local_errorSignal = DIO_setPortValue(LCD_DATA_PORT,PORT_LOW);
	local_errorSignal = DIO_setPinDirection(LCD_CONTROL_PORT,LCD_RS_PIN,OUTPUT);
	local_errorSignal = DIO_setPinDirection(LCD_CONTROL_PORT,LCD_RW_PIN,OUTPUT);
	local_errorSignal = DIO_setPinDirection(LCD_CONTROL_PORT,LCD_ENABLE_PIN,OUTPUT);
	_delay_ms(35);
	local_errorSignal = LCD_sendCommand_8bit(LCD_DATA_PORT,FUNCTION_SET_8BIT);
	local_errorSignal = LCD_sendCommand_8bit(LCD_DATA_PORT,DISPLAY_CURSOR_BLINKING);
	local_errorSignal = LCD_sendCommand_8bit(LCD_DATA_PORT,DISPLAY_CLEAR);
	local_errorSignal = LCD_sendCommand_8bit(LCD_DATA_PORT,ENTRY_MODE);
	local_errorSignal = LCD_sendCommand_8bit(LCD_DATA_PORT,PORT_LOW);
	return local_errorSignal;
}

/*reminder : we need to solve problem of having exceeded the column number*/
uint8 LCD_sendDataAtAddress_8bit(uint8 copy_LCD_port, uint8 copy_LCD_row, uint8 copy_LCD_column,uint8 copy_LCD_data)
{
	uint8 local_errorSignal = OK_STAT;

	if (copy_LCD_column <= 16)
	{
		copy_LCD_column--;
		switch (copy_LCD_row)
		{
			case 1:
				local_errorSignal = LCD_sendCommand_8bit(copy_LCD_port,(0x80 + copy_LCD_column));
				break;
			case 2:
				local_errorSignal = LCD_sendCommand_8bit(copy_LCD_port,(0xc0 + copy_LCD_column));
				break;
			default:
				local_errorSignal = NOT_OK_STAT;
				break;
		}
		local_errorSignal = LCD_sendData_8bit(copy_LCD_port,copy_LCD_data);
	}
	else
	{
		local_errorSignal = NOT_OK_STAT;
	}

	return local_errorSignal;
}

uint8 LCD_sendString_8bit(uint8 copy_LCD_port,const char *copy_LCD_str)
{
	uint8 local_errorString = OK_STAT;
	for (;*copy_LCD_str;copy_LCD_str++)
	{
		local_errorString = LCD_sendData_8bit(copy_LCD_port,*copy_LCD_str);
	}
	return local_errorString;
}

uint8 LCD_sendStringAtAddress_8bit(uint8 copy_LCD_port, uint8 copy_LCD_row, uint8 copy_LCD_column,const char *copy_LCD_string)
{
	uint8 local_errorSignal = OK_STAT;

		if (copy_LCD_column <= 16)
		{
			copy_LCD_column--;
			switch (copy_LCD_row)
			{
				case LCD_ROW1:
					local_errorSignal = LCD_sendCommand_8bit(copy_LCD_port,(LCD_DDRAM_ROW1 + copy_LCD_column));
					break;
				case LCD_ROW2:
					local_errorSignal = LCD_sendCommand_8bit(copy_LCD_port,(LCD_DDRAM_ROW2 + copy_LCD_column));
					break;
				default:
					local_errorSignal = NOT_OK_STAT;
					break;
			}
			local_errorSignal = LCD_sendString_8bit(copy_LCD_port,copy_LCD_string);
		}
		else
		{
			local_errorSignal = NOT_OK_STAT;
		}

		return local_errorSignal;
}
uint8 LCD_sendCommand_4bit(uint8 copy_LCD_port, uint8 copy_LCD_command)
{
	uint8 local_errorSignal = OK_STAT;
	local_errorSignal = DIO_setPinValue(LCD_CONTROL_PORT,LCD_RS_PIN,LOW);
	local_errorSignal = DIO_setPinValue(LCD_CONTROL_PORT,LCD_RW_PIN,LOW);
	local_errorSignal = DIO_set4bitsValue(copy_LCD_port,(copy_LCD_command >> 4));

	local_errorSignal = DIO_setPinValue(LCD_CONTROL_PORT,LCD_ENABLE_PIN,HIGH);
	_delay_ms(2);
	local_errorSignal = DIO_setPinValue(LCD_CONTROL_PORT,LCD_ENABLE_PIN,LOW);

	local_errorSignal = DIO_set4bitsValue(copy_LCD_port,copy_LCD_command);
	local_errorSignal = DIO_setPinValue(LCD_CONTROL_PORT,LCD_ENABLE_PIN,HIGH);
	_delay_ms(2);
	local_errorSignal = DIO_setPinValue(LCD_CONTROL_PORT,LCD_ENABLE_PIN,LOW);

	return local_errorSignal;
}

uint8 LCD_sendData_4bit(uint8 copy_LCD_port, uint8 copy_LCD_data)
{
	uint8 local_errorSignal = OK_STAT;
	local_errorSignal = DIO_setPinValue(LCD_CONTROL_PORT,LCD_RS_PIN,HIGH);
	local_errorSignal = DIO_setPinValue(LCD_CONTROL_PORT,LCD_RW_PIN,LOW);
	local_errorSignal = DIO_set4bitsValue(copy_LCD_port,(copy_LCD_data >> 4));

	local_errorSignal = DIO_setPinValue(LCD_CONTROL_PORT,LCD_ENABLE_PIN,HIGH);
	_delay_ms(2);
	local_errorSignal = DIO_setPinValue(LCD_CONTROL_PORT,LCD_ENABLE_PIN,LOW);

	local_errorSignal = DIO_set4bitsValue(copy_LCD_port,copy_LCD_data);
	local_errorSignal = DIO_setPinValue(LCD_CONTROL_PORT,LCD_ENABLE_PIN,HIGH);
	_delay_ms(2);
	local_errorSignal = DIO_setPinValue(LCD_CONTROL_PORT,LCD_ENABLE_PIN,LOW);
	return local_errorSignal;

}

uint8 LCD_init_4bit(void)
{
	uint8 local_errorSignal = OK_STAT;
	local_errorSignal = DIO_setPinDirection(LCD_DATA_PORT,LCD_DATA_4BIT_PIN0,OUTPUT);
	local_errorSignal = DIO_setPinDirection(LCD_DATA_PORT,LCD_DATA_4BIT_PIN1,OUTPUT);
	local_errorSignal = DIO_setPinDirection(LCD_DATA_PORT,LCD_DATA_4BIT_PIN2,OUTPUT);
	local_errorSignal = DIO_setPinDirection(LCD_DATA_PORT,LCD_DATA_4BIT_PIN3,OUTPUT);

	local_errorSignal = DIO_setPinDirection(LCD_CONTROL_PORT,LCD_RS_PIN,OUTPUT);
	local_errorSignal = DIO_setPinDirection(LCD_CONTROL_PORT,LCD_RW_PIN,OUTPUT);
	local_errorSignal = DIO_setPinDirection(LCD_CONTROL_PORT,LCD_ENABLE_PIN,OUTPUT);
	_delay_ms(35);
	local_errorSignal = LCD_sendCommand_4bit(LCD_DATA_PORT,(FUNCTION_SET_4BIT >> 4));
	local_errorSignal = LCD_sendCommand_4bit(LCD_DATA_PORT,FUNCTION_SET_4BIT);
	local_errorSignal = LCD_sendCommand_4bit(LCD_DATA_PORT,DISPLAY_CURSOR_BLINKING);
	local_errorSignal = LCD_sendCommand_4bit(LCD_DATA_PORT,DISPLAY_CLEAR);
	local_errorSignal = LCD_sendCommand_4bit(LCD_DATA_PORT,ENTRY_MODE);
	local_errorSignal = LCD_sendCommand_4bit(LCD_DATA_PORT,PORT_LOW);

	return local_errorSignal;

}

uint8 LCD_sendDataAtAddress_4bit(uint8 copy_LCD_port, uint8 copy_LCD_row, uint8 copy_LCD_column,uint8 copy_LCD_data)
{
		uint8 local_errorSignal = OK_STAT;

		if (copy_LCD_column <= 16)
		{
			copy_LCD_column--;
			switch (copy_LCD_row)
			{
				case 1:
					local_errorSignal = LCD_sendCommand_4bit(copy_LCD_port,(0x80 + copy_LCD_column));
					break;
				case 2:
					local_errorSignal = LCD_sendCommand_4bit(copy_LCD_port,(0xc0 + copy_LCD_column));
					break;
				default:
					local_errorSignal = NOT_OK_STAT;
					break;
			}
			local_errorSignal = LCD_sendData_4bit(copy_LCD_port,copy_LCD_data);
		}
		else
		{
			local_errorSignal = NOT_OK_STAT;
		}

		return local_errorSignal;
}

uint8 LCD_sendString_4bit(uint8 copy_LCD_port,const char *copy_LCD_str)
{
	uint8 local_errorString = OK_STAT;
	for (;*copy_LCD_str;copy_LCD_str++)
	{
		local_errorString = LCD_sendData_4bit(copy_LCD_port,*copy_LCD_str);
	}
	return local_errorString;
}

uint8 LCD_sendStringAtAddress_4bit(uint8 copy_LCD_port, uint8 copy_LCD_row, uint8 copy_LCD_column,const char *copy_LCD_string)
{
	uint8 local_errorSignal = OK_STAT;

			if (copy_LCD_column <= 16)
			{
				copy_LCD_column--;
				switch (copy_LCD_row)
				{
					case 1:
						local_errorSignal = LCD_sendCommand_4bit(copy_LCD_port,(0x80 + copy_LCD_column));
						break;
					case 2:
						local_errorSignal = LCD_sendCommand_4bit(copy_LCD_port,(0xc0 + copy_LCD_column));
						break;
					default:
						local_errorSignal = NOT_OK_STAT;
						break;
				}
				local_errorSignal = LCD_sendString_4bit(copy_LCD_port,copy_LCD_string);
			}
			else
			{
				local_errorSignal = NOT_OK_STAT;
			}

			return local_errorSignal;
}

static uint8 DIO_set4bitsValue(uint8 copy_DIO_PORT, uint8 copy_DIO_value)
{
	uint8 local_errorSignal = OK_STAT;
	local_errorSignal = DIO_setPinValue(copy_DIO_PORT,LCD_DATA_4BIT_PIN0,GET_BIT(copy_DIO_value,0));
	local_errorSignal = DIO_setPinValue(copy_DIO_PORT,LCD_DATA_4BIT_PIN1,GET_BIT(copy_DIO_value,1));
	local_errorSignal = DIO_setPinValue(copy_DIO_PORT,LCD_DATA_4BIT_PIN2,GET_BIT(copy_DIO_value,2));
	local_errorSignal = DIO_setPinValue(copy_DIO_PORT,LCD_DATA_4BIT_PIN3,GET_BIT(copy_DIO_value,3));
	return local_errorSignal;
}


