/*
 * KEYPAD_Program.c
 *
 *  Created on: 15 Dec 2023
 *      Author: user
 */
#include <util/delay.h>

#include "../DIO/STD_Types.h"
#include "../DIO/bitmath.h"

#include "../DIO/DIO_Interface.h"


#include "KEYPAD_CFG.h"
#include "KEYPAD_Reg.h"
#include "KEYPAD_Private.h"
#include "KEYPAD_Interfacing.h"

static uint8 buttonsArray[KEYPAD_ROW_NUM][KEYPAD_COL_NUM] = KEYPAD_BUTTONS;
static uint8 rowPins[KEYPAD_ROW_NUM] = KEYPAD_ROW_PINS;
static uint8 colPins[KEYPAD_COL_NUM] = KEYPAD_COL_PINS;

uint8 KEYPAD_getValue(void)
{
	uint8 local_pressed_button = BUTTON_NOT_PRESSED;
	uint8 local_row_counter = 0;
	uint8 local_col_counter = 0;
	for (local_col_counter = 0; local_col_counter < KEYPAD_COL_NUM; local_col_counter++)
	{
		DIO_setPinValue(KEYPAD_COL_PORT,colPins[local_col_counter],LOW);
		for (local_row_counter = 0; local_row_counter < KEYPAD_ROW_NUM; local_row_counter++)
		{
			DIO_ReadPinValue(KEYPAD_ROW_PORT,rowPins[local_row_counter],&local_pressed_button);
			if (local_pressed_button == LOW)
			{
				while (local_pressed_button == LOW)
				{
					DIO_ReadPinValue(KEYPAD_ROW_PORT,rowPins[local_row_counter],&local_pressed_button);
				}
				local_pressed_button = buttonsArray[local_row_counter][local_col_counter];
				return local_pressed_button;
			}
		}
		DIO_setPinValue(KEYPAD_COL_PORT,colPins[local_col_counter],HIGH);
	}
	return local_pressed_button;
}
