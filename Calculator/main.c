/*
 * main.c
 *
 *  Created on: 16 Dec 2023
 *      Author: user
 */

#include "DIO/STD_Types.h"
#include "DIO/bitmath.h"

#include "DIO/DIO_Interface.h"

#include "DIO_autosar/DIO_interface.h"

#include "KEYPAD/KEYPAD_Interfacing.h"
#include "LCD/LCD_Interface.h"

#include "main.h"

#define MAX_LIMIT	16

char firstNum[MAX_LIMIT];
char secondNum[MAX_LIMIT];
char operator;
char result[MAX_LIMIT];

static void stringInit(char *str);
static uint64 stringToNum(char *str);
static void *numToString(uint64 num);
static void *floatToString(float64 num);
static void swapChar(char *char1, char *char2);
static void reverseString(char *str);

int main(void)
{
	DIO_initalizePorts();
	uint8 local_counter = 0;
	uint8 local_data = 0;
	uint8 res_flag = 0;
	uint8 on_flag = 0;
	uint8 str[MAX_LIMIT];
	while (1)
	{
		if (local_counter < MAX_LIMIT)
		{
			local_data = KEYPAD_getValue();
			switch (local_data)
			{
			case '7':
				if (res_flag)
				{
					LCD_sendCommand_4bit(LCD_DATA_PORT,0x01);
					LCD_sendCommand_4bit(LCD_DATA_PORT,0x02);
					stringInit(result);
					res_flag = 0;
				}
				LCD_sendData_4bit(LCD_DATA_PORT,'7');
				str[local_counter] = '7';
				local_counter++;
				break;
			case '8':
				if (res_flag)
				{
					LCD_sendCommand_4bit(LCD_DATA_PORT,0x01);
					LCD_sendCommand_4bit(LCD_DATA_PORT,0x02);
					stringInit(result);
					res_flag = 0;
				}
				LCD_sendData_4bit(LCD_DATA_PORT,'8');
				str[local_counter] = '8';
				local_counter++;
				break;
			case '9':
				if (res_flag)
				{
					LCD_sendCommand_4bit(LCD_DATA_PORT,0x01);
					LCD_sendCommand_4bit(LCD_DATA_PORT,0x02);
					stringInit(result);
					res_flag = 0;
				}
				LCD_sendData_4bit(LCD_DATA_PORT,'9');
				str[local_counter] = '9';
				local_counter++;
				break;
			case '/':
				if (res_flag)
				{
					LCD_sendCommand_4bit(LCD_DATA_PORT,0x01);
					LCD_sendCommand_4bit(LCD_DATA_PORT,0x02);
					stringInit(result);
					res_flag = 0;
				}
				LCD_sendData_4bit(LCD_DATA_PORT,'/');
				str[local_counter] = '/';
				local_counter++;
				break;
			case '4':
				if (res_flag)
				{
					LCD_sendCommand_4bit(LCD_DATA_PORT,0x01);
					LCD_sendCommand_4bit(LCD_DATA_PORT,0x02);
					stringInit(result);
					res_flag = 0;
				}
				LCD_sendData_4bit(LCD_DATA_PORT,'4');
				str[local_counter] = '4';
				local_counter++;
				break;
			case '5':
				if (res_flag)
				{
					LCD_sendCommand_4bit(LCD_DATA_PORT,0x01);
					LCD_sendCommand_4bit(LCD_DATA_PORT,0x02);
					stringInit(result);
					res_flag = 0;
				}
				LCD_sendData_4bit(LCD_DATA_PORT,'5');
				str[local_counter] = '5';
				local_counter++;
				break;
			case '6':
				if (res_flag)
				{
					LCD_sendCommand_4bit(LCD_DATA_PORT,0x01);
					LCD_sendCommand_4bit(LCD_DATA_PORT,0x02);
					stringInit(result);
					res_flag = 0;
				}
				LCD_sendData_4bit(LCD_DATA_PORT,'6');
				str[local_counter] = '6';
				local_counter++;
				break;
			case '*':
				if (res_flag)
				{
					LCD_sendCommand_4bit(LCD_DATA_PORT,0x01);
					LCD_sendCommand_4bit(LCD_DATA_PORT,0x02);
					stringInit(result);
					res_flag = 0;
				}
				LCD_sendData_4bit(LCD_DATA_PORT,'*');
				str[local_counter] = '*';
				local_counter++;
				break;
			case '1':
				if (res_flag)
				{
					LCD_sendCommand_4bit(LCD_DATA_PORT,0x01);
					LCD_sendCommand_4bit(LCD_DATA_PORT,0x02);
					stringInit(result);
					res_flag = 0;
				}
				LCD_sendData_4bit(LCD_DATA_PORT,'1');
				str[local_counter] = '1';
				local_counter++;
				break;
			case '2':
				if (res_flag)
				{
					LCD_sendCommand_4bit(LCD_DATA_PORT,0x01);
					LCD_sendCommand_4bit(LCD_DATA_PORT,0x02);
					stringInit(result);
					res_flag = 0;
				}
				LCD_sendData_4bit(LCD_DATA_PORT,'2');
				str[local_counter] = '2';
				local_counter++;
				break;
			case '3':
				if (res_flag)
				{
					LCD_sendCommand_4bit(LCD_DATA_PORT,0x01);
					LCD_sendCommand_4bit(LCD_DATA_PORT,0x02);
					stringInit(result);
					res_flag = 0;
				}
				LCD_sendData_4bit(LCD_DATA_PORT,'3');
				str[local_counter] = '3';
				local_counter++;
				break;
			case '-':
				if (res_flag)
				{
					LCD_sendCommand_4bit(LCD_DATA_PORT,0x01);
					LCD_sendCommand_4bit(LCD_DATA_PORT,0x02);
					stringInit(result);
					res_flag = 0;
				}
				LCD_sendData_4bit(LCD_DATA_PORT,'-');
				str[local_counter] = '-';
				local_counter++;
				break;
			case '#':
				if (on_flag)
				{
					LCD_sendCommand_4bit(LCD_DATA_PORT,0x01);
					LCD_sendCommand_4bit(LCD_DATA_PORT,0x02);
					stringInit(result);
				}
				LCD_init_4bit();
				on_flag = 1;
				local_counter = 0;
				stringInit(str);
				break;
			case '0':
				if (res_flag)
					{
						LCD_sendCommand_4bit(LCD_DATA_PORT,0x01);
						LCD_sendCommand_4bit(LCD_DATA_PORT,0x02);
						stringInit(result);
					}
				LCD_sendData_4bit(LCD_DATA_PORT,'0');
				str[local_counter] = '0';
				local_counter++;
				break;
			case '=':
				calculatorFun(str);
				uint8 length = 0;
				for (;result[length] != 0; length++);
				LCD_sendStringAtAddress_4bit(LCD_DATA_PORT,2,17 - length,result);
				local_counter = 0;
				str[local_counter] = '\0';
				break;
			case '+':
				if (res_flag)	LCD_sendCommand_4bit(LCD_DATA_PORT,0x01);
				LCD_sendData_4bit(LCD_DATA_PORT,'+');
				str[local_counter] = '+';
				local_counter++;
				break;
			default:;
			}
		}

	}
}

void *calculatorFun(char *str)
{
    operator= '\0';
    stringInit(firstNum);
    stringInit(secondNum);
    stringInit(result);
    uint8 local_counter = 0;
    for (local_counter = 0; ((str[local_counter] >= '0') && (str[local_counter] <= '9')); local_counter++)
    {
        firstNum[local_counter] = str[local_counter];
    }
    operator= str[local_counter++];
    uint8 local_count = 0;
    for (local_count = 0; str[local_counter] != '\0'; local_count++)
    {
        secondNum[local_count] = str[local_counter++];
    }
    uint64 numOne = 0;
    uint64 numTwo = 0;
    numOne = stringToNum(firstNum);
    numTwo = stringToNum(secondNum);

    uint64 result = 0;
    float64 f_result = 0.0;
    switch (operator)
    {
    case '+':
        result = numOne + numTwo;
        break;
    case '-':
        result = numOne - numTwo;
        break;
    case '*':
        result = numOne * numTwo;
        break;
    case '/':
        f_result = (float64)numOne / (float64)numTwo;
        break;
    default:;
    }
    if (!f_result)
    {
        numToString(result);
    }
    else
    {
        floatToString(f_result);
    }
}

static void stringInit(char *str)
{
    uint8 counter = 0;
    for (; counter < MAX_LIMIT; counter++)
    {
        str[counter] = '\0';
    }
}

static uint64 stringToNum(char *str)
{
    uint8 length = 0;
    for (; str[length] != '\0'; length++)
        ;
    uint64 num = 0;

    uint8 counter = 0;
    for (counter = 0; counter < length; counter++)
    {
        num = (num * 10) + str[counter] - '0';
    }
    return num;
}

static void *numToString(uint64 num)
{
    if (num == 0)
        result[0] = '0';
    else
    {
        uint8 counter = 0;
        for (; num != 0; num /= 10)
        {
            result[counter++] = (num % 10) + '0';
        }
    }
    reverseString(result);
}

static void *floatToString(float64 num)
{
	int i = 0;
	    int integerPart = (int)num;
	    float decimalPart = num - integerPart;
	    int counter = 0;
	    // convert the integer part to string
	    while (integerPart != 0)
	    {
	        result[i++] = integerPart % 10 + '0';
	        integerPart /= 10;
	    }


	    // reverse the string

	    int j = i - 1;
	    i = 0;
	    while (i < j )
	    {
	        char temp = result[i];
	        result[i] = result[j];
	        result[j] = temp;
	        i++;
	        j--;
	    }

	    // add the decimal point
#if (i == 0)
	    result[++j] = '.';
#else
	    result[++i] = '.'
#endif
	    i++;
	    // convert the decimal part to string
	    while (decimalPart > 0.0)
	    {
	        decimalPart *= 10.0;
	        int digit = (int)decimalPart;
	        result[i++] = digit + '0';
	        decimalPart -= digit;
	    }

	    // terminate the string
	    result[i] = '\0';
}

static void swapChar(char *char1, char *char2)
{
    char temp = '\0';
    temp = *char1;
    *char1 = *char2;
    *char2 = temp;
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
