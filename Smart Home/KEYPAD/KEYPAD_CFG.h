/*
 * KEYPAD_CFG.h
 *
 *  Created on: 15 Dec 2023
 *      Author: user
 */

#ifndef KEYPAD_CFG_H_
#define KEYPAD_CFG_H_

#define KEYPAD_ROW_NUM	4
#define KEYPAD_COL_NUM	3

#define KEYPAD_ROW_PORT	DIO_PORTD
#define KEYPAD_COL_PORT	DIO_PORTD

#define KEYPAD_ROW_PIN0	PIN3
#define KEYPAD_ROW_PIN1	PIN4
#define KEYPAD_ROW_PIN2	PIN5
#define KEYPAD_ROW_PIN3	PIN6

#define KEYPAD_COL_PIN0	PIN0
#define KEYPAD_COL_PIN1	PIN1
#define KEYPAD_COL_PIN2	PIN2


#define KEYPAD_BUTTONS	{{'1' , '2' , '3'} , {'4' , '5' , '6'} , {'7' ,'8' , '9'} , {'*' , '0' , '#'}}
#define KEYPAD_ROW_PINS	{KEYPAD_ROW_PIN0 , KEYPAD_ROW_PIN1 , KEYPAD_ROW_PIN2 , KEYPAD_ROW_PIN3}
#define KEYPAD_COL_PINS {KEYPAD_COL_PIN0 , KEYPAD_COL_PIN1 , KEYPAD_COL_PIN2}

#define BUTTON_NOT_PRESSED	0xFF
#endif /* KEYPAD_CFG_H_ */
