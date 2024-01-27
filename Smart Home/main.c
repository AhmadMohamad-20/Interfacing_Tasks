/*
 * Author   : Ahmed Mohamed Aboud
 * Linkedin :https://www.linkedin.com/in/ahmed-mohamed-aboud-33b2471b1/
 * File Name: main.c
 * Date: 28 Dec 2023
 */

#include <util/delay.h>

#include "DIO/STD_Types.h"
#include "DIO/bitmath.h"

#include "DIO/DIO_Interface.h"
#include "LED/LED_Interface.h"
#include "LCD/LCD_Interface.h"
#include "KEYPAD/KEYPAD_Interfacing.h"
#include "ADC/ADC_Interface.h"

#include "main.h"

#define ORIGNAL_PASSWORD  "1234"
uint8 flag = 0;
uint8 reset_flag = 0;
char password[4];
char og_pass[4] = ORIGNAL_PASSWORD;
char str[3];

static void *numToString(uint32 num);
static void reverseString(char *str);
static void swapChar(char *char1, char *char2);

int main(void)
{
	DIO_setPortDirection(DIO_PORTC,PORT_OUTPUT);

	//DIO_setPinDirection(DIO_PORTA,PIN0,INPUT);
	/* setting pins for keypad*/
	DIO_setPinDirection(DIO_PORTD,PIN0,OUTPUT);
	DIO_setPinDirection(DIO_PORTD,PIN1,OUTPUT);
	DIO_setPinDirection(DIO_PORTD,PIN2,OUTPUT);
	DIO_setPinDirection(DIO_PORTD,PIN3,INPUT);

	DIO_setPinDirection(DIO_PORTD,PIN4,INPUT);
	DIO_setPinDirection(DIO_PORTD,PIN5,INPUT);
	DIO_setPinDirection(DIO_PORTD,PIN6,INPUT);
	DIO_setPinDirection(DIO_PORTD,PIN7,OUTPUT);

	DIO_setIntPullUpRes(DIO_PORTD,PIN3);
	DIO_setIntPullUpRes(DIO_PORTD,PIN4);
	DIO_setIntPullUpRes(DIO_PORTD,PIN5);
	DIO_setIntPullUpRes(DIO_PORTD,PIN6);

	DIO_setPinValue(DIO_PORTD,PIN0,HIGH);
	DIO_setPinValue(DIO_PORTD,PIN1,HIGH);
	DIO_setPinValue(DIO_PORTD,PIN2,HIGH);

	ADC_init();
	LCD_init_4bit();

	while(1)
	{
		if (flag == 0)
		{
			LCD_PrintWelcome();
			LCD_Password();
			flag = 1;
		}
		if (reset_flag == 1)
		{
			break;
		}
		smartHome_Options();


	}
}


void LCD_PrintWelcome()
{
	LCD_sendStringAtAddress_4bit(LCD_DATA_PORT,1,1,"Welcome !!");
	_delay_ms(3000);
	LCD_sendCommand_4bit(LCD_DATA_PORT,0x01); // clear screen
	LCD_sendCommand_4bit(LCD_DATA_PORT,0x02);
}

void LCD_Password()
{

	uint8 counter = 0;
	uint8 CharIndex = 0;
	uint8 strike = 0;
	uint8 max_trials = 3;
	while (max_trials)
	{
		/* entering password*/
		LCD_sendCommand_4bit(LCD_DATA_PORT,0x01); // clear screen
		LCD_sendCommand_4bit(LCD_DATA_PORT,0x02);
		LCD_sendString_4bit(LCD_DATA_PORT,"Password : ");
		for (counter = 0; counter < 4; counter++)
		{
			CharIndex = KEYPAD_getValue();
			while (CharIndex == 0x01)
			{
				CharIndex = KEYPAD_getValue();
			}
			password[counter] = CharIndex;
			LCD_sendData_4bit(LCD_DATA_PORT,'*');
		}

		/*compare passwords*/
		counter = 0;
		for (counter = 0; counter < 4; counter++)
		{
			if (password[counter] != og_pass[counter])
			{
				strike = 1;
				break;
			}
			else
			{
				strike = 0;
				continue;
			}
		}
		if (strike == 1)
		{
			max_trials--;
			LCD_sendCommand_4bit(LCD_DATA_PORT,0x01);
			LCD_sendCommand_4bit(LCD_DATA_PORT,0x02);
			LCD_sendString_4bit(LCD_DATA_PORT,"Incorrect !!");
			_delay_ms(1500);
			password[0] = 0;
			password[1] = 0;
			password[2] = 0;
			password[3] = 0;
		}
		else
		{
			LCD_sendCommand_4bit(LCD_DATA_PORT,0x01);
			LCD_sendCommand_4bit(LCD_DATA_PORT,0x02);
			LCD_sendString_4bit(LCD_DATA_PORT,"Welcome User");
			_delay_ms(3000);
			max_trials = 3;
			strike = 0;
			break;
		}
	}
	if (strike == 1)
	{
		reset_flag = 1;
	}
}

void smartHome_Options()
{
	static uint8 option = 0;
	static uint8 flag_show = 0;

	if (flag_show == 0)
	{
		LCD_sendCommand_4bit(LCD_DATA_PORT,0x01);
		LCD_sendCommand_4bit(LCD_DATA_PORT,0x02);
		LCD_sendStringAtAddress_4bit(LCD_DATA_PORT,1,1,"1-turn LED ON");
		LCD_sendStringAtAddress_4bit(LCD_DATA_PORT,2,1,"2-turn LED OFF");
		_delay_ms(500);
		LCD_sendCommand_4bit(LCD_DATA_PORT,0x01);
		LCD_sendCommand_4bit(LCD_DATA_PORT,0x02);
		LCD_sendStringAtAddress_4bit(LCD_DATA_PORT,1,1,"3-turn Fan ON");
		LCD_sendStringAtAddress_4bit(LCD_DATA_PORT,2,1,"4-turn Fan OFF");
		_delay_ms(500);
		LCD_sendCommand_4bit(LCD_DATA_PORT,0x01);
		LCD_sendCommand_4bit(LCD_DATA_PORT,0x02);
		flag_show = 1;
	}

	option = KEYPAD_getValue();
	if (option != 1)
	{
		LCD_sendCommand_4bit(LCD_DATA_PORT,0x01);
		LCD_sendCommand_4bit(LCD_DATA_PORT,0x02);
		LCD_sendString_4bit(LCD_DATA_PORT,"Option : ");
		LCD_sendData_4bit(LCD_DATA_PORT,option);

		switch (option)
		{
		case '1':
			LED_ON();
			break;
		case '2':
			LED_OFF();
			break;
		case '3':
			FAN_ON();
			break;
		case '4':
			FAN_OFF();
			break;
		default:;
		}
	}

}


void LED_ON(void)
{
	LCD_sendCommand_4bit(LCD_DATA_PORT,0x01);
	LCD_sendCommand_4bit(LCD_DATA_PORT,0x02);
	LCD_sendString_4bit(LCD_DATA_PORT,"LED ON");

	uint8 optionsChar = 1;
	uint8 readData = 0;
	uint32 speed = 0;
	uint8 try = 10;
	static uint8 prevValue = 0;

	while ((optionsChar == 1) || (optionsChar == '1'))
	{
		ADC_startConversionSync(0x01,&readData);
		TIMER0_fastPWM(readData);
		speed = (uint32)(readData * 100) / 256UL;
		numToString(speed);
		if (prevValue != readData)
		{
			LCD_sendStringAtAddress_4bit(LCD_DATA_PORT,2,1,"LIGHT : ");
			LCD_sendString_4bit(LCD_DATA_PORT,str);
			prevValue = readData;
		}
		optionsChar = KEYPAD_getValue();
	}
}

void LED_OFF(void)
{
	uint8 optionsChar = 1;
	LCD_sendCommand_4bit(LCD_DATA_PORT,0x01);
	LCD_sendCommand_4bit(LCD_DATA_PORT,0x02);
	LCD_sendString_4bit(LCD_DATA_PORT,"LED OFF");
	while ((optionsChar == 1) || (optionsChar == '2'))
	{

		TIMER0_turnOFF();
		DIO_setPinValue(DIO_PORTB,PIN3,LOW);
		optionsChar = KEYPAD_getValue();
	}

}

void FAN_ON(void)
{
	LCD_sendCommand_4bit(LCD_DATA_PORT,0x01);
	LCD_sendCommand_4bit(LCD_DATA_PORT,0x02);
	LCD_sendString_4bit(LCD_DATA_PORT,"FAN ON");

	uint8 optionsChar = 1;
	uint8 readData = 0;
	uint32 speed = 0;
	static uint8 prevValue = 0;

	while ((optionsChar == 1) || (optionsChar == '3'))
	{
		ADC_startConversionSync(0x00,&readData);
		TIMER2_fastPWM(readData);
		speed = (uint32)(readData * 100) / 256UL;
		numToString(speed);
		if (prevValue != readData)
		{
			LCD_sendStringAtAddress_4bit(LCD_DATA_PORT,2,1,"SPEED : ");
			LCD_sendString_4bit(LCD_DATA_PORT,str);
			prevValue = readData;
		}
		optionsChar = KEYPAD_getValue();
	}
}

void FAN_OFF(void)
{
	uint8 optionsChar = 1;
	LCD_sendCommand_4bit(LCD_DATA_PORT,0x01);
	LCD_sendCommand_4bit(LCD_DATA_PORT,0x02);
	LCD_sendString_4bit(LCD_DATA_PORT,"FAN OFF");
	while ((optionsChar == 1) || (optionsChar == '4'))
	{

		TIMER2_turnOFF();
		DIO_setPinValue(DIO_PORTD,PIN7,LOW);
		optionsChar = KEYPAD_getValue();
	}
}

static void *numToString(uint32 num)
{
    if (num == 0)
    	str[0] = '0';
    else
    {
        uint8 counter = 0;
        for (; num != 0; num /= 10)
        {
        	str[counter++] = (num % 10) + '0';
        }
    }
    reverseString(str);
}

static void reverseString(char *str)
{
    uint8 length = 0;
    for (; str[length] != '\0'; length++)
        ;
    uint8 counter = 0;
    for (counter = 0; counter < length / 2; counter++)
    {
        swapChar(&str[counter], &str[length - counter - 1]);
    }
}

static void swapChar(char *char1, char *char2)
{
    char temp = '\0';
    temp = *char1;
    *char1 = *char2;
    *char2 = temp;
}
