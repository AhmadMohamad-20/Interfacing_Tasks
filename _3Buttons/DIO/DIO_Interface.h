/*
 * DIO_Interface.h
 *
 *  Created on: 8 Dec 2023
 *      Author: user
 */

#ifndef DIO_INTERFACE_H_
#define DIO_INTERFACE_H_




/*Macros Definitions*/
#define DIO_PORTA	0
#define DIO_PORTB	1
#define DIO_PORTC	2
#define DIO_PORTD	3


#define PIN0	0
#define PIN1	1
#define PIN2	2
#define PIN3	3
#define PIN4	4
#define PIN5	5
#define PIN6	6
#define PIN7	7

#define INPUT	0
#define OUTPUT	1

#define HIGH	1
#define LOW		0

#define PORT_OUTPUT 0xFF
#define PORT_INPUT 0

#define PORT_HIGH	0xFF
#define PORT_LOW	0

/*Function Prototypes for DIO Driver*/
/*
 * 1- set pin direction
 * 2 - set port direction
 *
 * */

uint8 DIO_setPinDirection(uint8 copy_DIO_port, uint8 copy_DIO_pin, uint8 copy_DIO_direction);
uint8 DIO_setPinValue(uint8 copy_DIO_port, uint8 copy_DIO_pin, uint8 copy_DIO_value);
uint8 DIO_ReadPinValue(uint8 copy_DIO_port, uint8 copy_DIO_pin, uint8 *copy_DIO_pValue);

uint8 DIO_setPortDirection(uint8 copy_DIO_port, uint8 copy_DIO_direction);
uint8 DIO_setPortValue(uint8 copy_DIO_port,  uint8 copy_DIO_value);
uint8 DIO_ReadPortValue(uint8 copy_DIO_port,  uint8 *copy_DIO_pValue);

uint8 DIO_setIntPullUpRes(uint8 copy_DIO_port, uint8 copy_DIO_pin);

uint8 DIO_togglePin(uint8 copy_DIO_port, uint8 copy_DIO_pin);
#endif /* DIO_INTERFACE_H_ */
