/*
 * LCD_Interface.h
 *
 *  Created on: 10 Dec 2023
 *      Author: user
 */

#ifndef LCD_INTERFACE_H_
#define LCD_INTERFACE_H_

#define	LCD_DATA_PORT		DIO_PORTA
#define LCD_CONTROL_PORT	DIO_PORTB
#define LCD_RS_PIN			PIN1
#define LCD_RW_PIN			PIN2
#define LCD_ENABLE_PIN		PIN3

#define LCD_DATA_4BIT_PIN0	PIN4
#define LCD_DATA_4BIT_PIN1	PIN5
#define LCD_DATA_4BIT_PIN2	PIN6
#define LCD_DATA_4BIT_PIN3	PIN7

#define FUNCTION_SET_8BIT				0b00111000  /* 2 rows , 8-bit , 5*8 character size*/
#define FUNCTION_SET_4BIT				0b00101000  /* 2 rows , 4-bit , 5*8 character size*/
#define DISPLAY_CURSOR_BLINKING		0b00001100 	/*Display on , cursor off , blinking off*/
#define DISPLAY_CLEAR				0x01
#define ENTRY_MODE					0b00000110 	/*increasing cursor, no shifting*/

#define LCD_ROW1	1
#define LCD_ROW2	2

uint8 LCD_sendCommand_8bit(uint8 copy_LCD_port, uint8 copy_LCD_command);
uint8 LCD_sendData_8bit(uint8 copy_LCD_port, uint8 copy_LCD_data);
uint8 LCD_init_8bit(void);
uint8 LCD_sendDataAtAddress_8bit(uint8 copy_LCD_port, uint8 copy_LCD_row, uint8 copy_LCD_column,uint8 copy_LCD_data);
uint8 LCD_sendString_8bit(uint8 copy_LCD_port,const char *copy_LCD_str);
uint8 LCD_sendStringAtAddress_8bit(uint8 copy_LCD_port, uint8 copy_LCD_row, uint8 copy_LCD_column,const char *copy_LCD_string);

uint8 LCD_sendCommand_4bit(uint8 copy_LCD_port, uint8 copy_LCD_command);
uint8 LCD_sendData_4bit(uint8 copy_LCD_port, uint8 copy_LCD_data);
uint8 LCD_init_4bit(void);
uint8 LCD_sendDataAtAddress_4bit(uint8 copy_LCD_port, uint8 copy_LCD_row, uint8 copy_LCD_column,uint8 copy_LCD_data);
uint8 LCD_sendString_4bit(uint8 copy_LCD_port,const char *copy_LCD_str);
uint8 LCD_sendStringAtAddress_4bit(uint8 copy_LCD_port, uint8 copy_LCD_row, uint8 copy_LCD_column,const char *copy_LCD_string);
#endif /* LCD_INTERFACE_H_ */
