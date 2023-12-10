/*
 * main.c
 *
 *  Created on: 9 Dec 2023
 *      Author: user
 */

#include <util/delay.h>
#include "DIO/STD_Types.h"
#include "DIO/bitmath.h"
#include "DIO/DIO_Interface.h"
#include "BUTTON/BTN_Interface.h"
#include "LED/LED_Interface.h"
#include "BUZZER/BUZZER_Interface.h"

#include "main.h"
int main(void)
{
	uint8 btnState1 = 0;
	uint8 btnState2 = 0;
	uint8 btnState3 = 0;
	Initialize();
	while (1)
	{
		BTN_readButtonState(DIO_PORTB,PIN0,&btnState1);
		BTN_readButtonState(DIO_PORTD,PIN6,&btnState2);
		BTN_readButtonState(DIO_PORTD,PIN2,&btnState3);
		_delay_us(50);
		if (btnState1 == HIGH)
		{
			btnState2 = LOW;
			btnState3 = LOW;
			ProgramOne();
		}
		else if (btnState2 == HIGH)
		{
			btnState1 = LOW;
			btnState3 = LOW;
			ProgramTwo();
		}
		else if (btnState3 == HIGH)
		{
			btnState2 = LOW;
			btnState1 = LOW;
			ProgramThree();
		}
	}
}

void Initialize(void)
{
	DIO_setPinDirection(DIO_PORTB,PIN0,INPUT);
	DIO_setPinDirection(DIO_PORTD,PIN6,INPUT);
	DIO_setPinDirection(DIO_PORTD,PIN2,INPUT);

	DIO_setPinDirection(DIO_PORTC,PIN2,OUTPUT);
	DIO_setPinDirection(DIO_PORTC,PIN7,OUTPUT);
	DIO_setPinDirection(DIO_PORTD,PIN3,OUTPUT);

	DIO_setPinDirection(DIO_PORTA,PIN3,OUTPUT);
}

void ProgramOne(void)
{
	 LED_turnOn(DIO_PORTC,PIN2);
	 BUZZER_turnOn(DIO_PORTA,PIN3);
	 _delay_ms(10000);
	 LED_turnOff(DIO_PORTC,PIN2);
	 BUZZER_turnOff(DIO_PORTA,PIN3);
	 _delay_ms(5000);

	 LED_turnOn(DIO_PORTC,PIN7);
	 BUZZER_turnOn(DIO_PORTA,PIN3);
	 _delay_ms(10000);
	 LED_turnOff(DIO_PORTC,PIN7);
	 BUZZER_turnOff(DIO_PORTA,PIN3);
	 _delay_ms(5000);

	 LED_turnOn(DIO_PORTD,PIN3);
	 BUZZER_turnOn(DIO_PORTA,PIN3);
	 _delay_ms(10000);
	 LED_turnOff(DIO_PORTD,PIN3);
	 BUZZER_turnOff(DIO_PORTA,PIN3);
	 _delay_ms(5000);

}

void ProgramTwo(void)
{

	LED_turnOn(DIO_PORTC,PIN2);
	LED_turnOff(DIO_PORTC,PIN7);
	LED_turnOff(DIO_PORTD,PIN3);
	_delay_ms(10000);

	LED_turnOff(DIO_PORTC,PIN2);
	LED_turnOn(DIO_PORTC,PIN7);
	LED_turnOff(DIO_PORTD,PIN3);
	_delay_ms(10000);

	LED_turnOn(DIO_PORTC,PIN2);
	LED_turnOn(DIO_PORTC,PIN7);
	LED_turnOff(DIO_PORTD,PIN3);
	_delay_ms(10000);

	LED_turnOff(DIO_PORTC,PIN2);
	LED_turnOff(DIO_PORTC,PIN7);
	LED_turnOn(DIO_PORTD,PIN3);
	_delay_ms(10000);

	LED_turnOn(DIO_PORTC,PIN2);
	LED_turnOff(DIO_PORTC,PIN7);
	LED_turnOn(DIO_PORTD,PIN3);
	_delay_ms(10000);

	LED_turnOff(DIO_PORTC,PIN2);
	LED_turnOn(DIO_PORTC,PIN7);
	LED_turnOn(DIO_PORTD,PIN3);
	_delay_ms(10000);

	LED_turnOn(DIO_PORTC,PIN2);
	LED_turnOn(DIO_PORTC,PIN7);
	LED_turnOn(DIO_PORTD,PIN3);
	_delay_ms(10000);

	LED_turnOff(DIO_PORTC,PIN2);
	LED_turnOff(DIO_PORTC,PIN7);
	LED_turnOff(DIO_PORTD,PIN3);
}

void ProgramThree(void)
{
	 LED_turnOn(DIO_PORTC,PIN2);
	_delay_ms(10000);
	LED_turnOn(DIO_PORTC,PIN7);
	_delay_ms(10000);
	LED_turnOn(DIO_PORTD,PIN3);
	_delay_ms(10000);
	LED_turnOff(DIO_PORTC,PIN2);
	_delay_ms(10000);
	LED_turnOff(DIO_PORTC,PIN7);
	_delay_ms(10000);
	LED_turnOff(DIO_PORTD,PIN3);
	_delay_ms(10000);


	LED_turnOn(DIO_PORTD,PIN3);
	_delay_ms(10000);
	LED_turnOn(DIO_PORTC,PIN7);
	_delay_ms(10000);
	LED_turnOn(DIO_PORTC,PIN2);
	_delay_ms(10000);

	LED_turnOff(DIO_PORTD,PIN3);
	_delay_ms(10000);
	LED_turnOff(DIO_PORTC,PIN7);
	_delay_ms(10000);
	LED_turnOff(DIO_PORTC,PIN2);
	_delay_ms(10000);

}
