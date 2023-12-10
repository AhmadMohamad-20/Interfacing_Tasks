/*
 * LED_Interface.h
 *
 *  Created on: 9 Dec 2023
 *      Author: user
 */

#ifndef LED_INTERFACE_H_
#define LED_INTERFACE_H_

#define LED_PORT	DIO_PORTA
#define LED_PIN		PIN2

uint8 LED_turnOn(uint8 copy_LED_port,uint8 copy_LED_pin);
uint8 LED_turnOff(uint8 copy_LED_port,uint8 copy_LED_pin);
uint8 LED_toggle(uint8 copy_LED_port,uint8 copy_LED_pin);

#endif /* LED_INTERFACE_H_ */
