/*************************************************************/
/*************** Name	: Ahmed Zaky *************************/
/*************** Date	: 11/1/2021  *************************/
/*************** Version: 1.0V 		 *************************/
/*************** SWC	: LCD 		 *************************/
/*************************************************************/

/* Library Layer */
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#define F_CPU 8000000UL
#include <util/delay.h>

/* MCAL */
#include "DIO_Interface.h"
#include "LCD_Interface.h"
#include "LCD_Private.h"
#include "LCD_Config.h"

void LCD_voidInit    (void) /* Datasheet page 13 */
{
#if LCD_u8_MODE == LCD_u8_8_BIT_MODE	
	
	_delay_ms(35);
	/* Function Set Cmd */
	LCD_voidSendCmd(0b00111000); 
	_delay_us(45);
	
#elif LCD_u8_MODE == LCD_u8_4_BIT_MODE
	DIO_u8SetPinValue(LCD_u8_RS_PORT, LCD_u8_RS_PIN, DIO_u8_LOW);
	DIO_u8SetPinValue(LCD_u8_RW_PORT, LCD_u8_RW_PIN, DIO_u8_LOW);
	
	Private_voidWriteHalfPort(0b0010);
	/* Enable Pulse *//* H => L */
	DIO_u8SetPinValue(LCD_u8_En_PORT, LCD_u8_En_PIN, DIO_u8_HIGH);
	_delay_ms(1);
	DIO_u8SetPinValue(LCD_u8_En_PORT, LCD_u8_En_PIN, DIO_u8_LOW);
	
	LCD_voidSendCmd(0b00101000);
#endif	
/**** The next commands are same for both modes initialiazation ****/

	/* Diplay On/Off Control Cmd */
	LCD_voidSendCmd(0b00001110); /* Display = On / Cursor = On / Cursor_Blink = On*/
	_delay_us(45);
	
	/* Display Clear Cmd*/
	LCD_voidSendCmd(0b00000001);
	_delay_ms(2);
	
	/* Entry Mode Set Cmd */
	LCD_voidSendCmd(0b00000110);	
}

void LCD_voidSendCmd (u8 Copy_u8Cmd)
{
#if LCD_u8_MODE == LCD_u8_8_BIT_MODE
	/* Rs Pin = 0 */
	DIO_u8SetPinValue(LCD_u8_CONTROL_PORT, LCD_u8_RS_PIN, DIO_u8_LOW);
	
	/* R/W Pin = 0 */
	DIO_u8SetPinValue(LCD_u8_CONTROL_PORT, LCD_u8_RW_PIN, DIO_u8_LOW);
	
	/* Write cmd on Data Pins */
	DIO_u8SetPortValue(LCD_u8_DATA_PORT, Copy_u8Cmd);
	
	/* Enable Pulse *//* H => L */
	DIO_u8SetPinValue(LCD_u8_CONTROL_PORT, LCD_u8_En_PIN, DIO_u8_HIGH);
	_delay_ms(1);
	DIO_u8SetPinValue(LCD_u8_CONTROL_PORT, LCD_u8_En_PIN, DIO_u8_LOW);

#elif LCD_u8_MODE == LCD_u8_4_BIT_MODE
	DIO_u8SetPinValue(LCD_u8_RS_PORT, LCD_u8_RS_PIN, DIO_u8_LOW);
	DIO_u8SetPinValue(LCD_u8_RW_PORT, LCD_u8_RW_PIN, DIO_u8_LOW);

	/* Send to LCD the MOST 4 bits of command */	
	Private_voidWriteHalfPort(Copy_u8Cmd>>4); 
	/* Enable Pulse *//* H => L */
	DIO_u8SetPinValue(LCD_u8_En_PORT, LCD_u8_En_PIN, DIO_u8_HIGH);
	_delay_ms(1);
	DIO_u8SetPinValue(LCD_u8_En_PORT, LCD_u8_En_PIN, DIO_u8_LOW);
	
	/* Send to LCD the LEAST 4 bits of command */
	Private_voidWriteHalfPort(Copy_u8Cmd); 
	/* Enable Pulse *//* H => L */
	DIO_u8SetPinValue(LCD_u8_En_PORT, LCD_u8_En_PIN, DIO_u8_HIGH);
	_delay_ms(1);
	DIO_u8SetPinValue(LCD_u8_En_PORT, LCD_u8_En_PIN, DIO_u8_LOW);
#endif
}

void LCD_voidWriteChar(u8 Copy_u8Char)
{
#if LCD_u8_MODE == LCD_u8_8_BIT_MODE
	/* Rs Pin = 1 */
	DIO_u8SetPinValue(LCD_u8_CONTROL_PORT, LCD_u8_RS_PIN, DIO_u8_HIGH);
	
	/* R/W Pin = 0 */
	DIO_u8SetPinValue(LCD_u8_CONTROL_PORT, LCD_u8_RW_PIN, DIO_u8_LOW);
	
	/* Write cmd on Data Pins (from Data Sheet page 13) */
	DIO_u8SetPortValue(LCD_u8_DATA_PORT, Copy_u8Char);
	
	/* Enable Pulse *//* H => L */
	DIO_u8SetPinValue(LCD_u8_CONTROL_PORT, LCD_u8_En_PIN, DIO_u8_HIGH);
	_delay_ms(1);
	DIO_u8SetPinValue(LCD_u8_CONTROL_PORT, LCD_u8_En_PIN, DIO_u8_LOW);

#elif LCD_u8_MODE == LCD_u8_4_BIT_MODE
	DIO_u8SetPinValue(LCD_u8_RS_PORT, LCD_u8_RS_PIN, DIO_u8_HIGH);
	DIO_u8SetPinValue(LCD_u8_RW_PORT, LCD_u8_RW_PIN, DIO_u8_LOW);

	/* Send to LCD the MOST 4 bits of command */	
	Private_voidWriteHalfPort(Copy_u8Char>>4); 
	/* Enable Pulse *//* H => L */
	DIO_u8SetPinValue(LCD_u8_En_PORT, LCD_u8_En_PIN, DIO_u8_HIGH);
	_delay_ms(1);
	DIO_u8SetPinValue(LCD_u8_En_PORT, LCD_u8_En_PIN, DIO_u8_LOW);
	
	/* Send to LCD the LEAST 4 bits of command */
	Private_voidWriteHalfPort(Copy_u8Char); 
	/* Enable Pulse *//* H => L */
	DIO_u8SetPinValue(LCD_u8_En_PORT, LCD_u8_En_PIN, DIO_u8_HIGH);
	_delay_ms(1);
	DIO_u8SetPinValue(LCD_u8_En_PORT, LCD_u8_En_PIN, DIO_u8_LOW);
#endif
}

void LCD_voidWriteStr (const u8* Copy_Pu8Str)
{
	for(int i = 0; Copy_Pu8Str[i] != '\0'; i++)
	{
		LCD_voidWriteChar(Copy_Pu8Str[i]);
	}
}

void LCD_voidWriteNumber(u32  Copy_u8Number)
{
	u8 Local_u8ADigits[20];
	u8 Local_u8Char;
	u8 Local_u8DigitIndex = 0;
	
	if(Copy_u8Number == 0) LCD_voidWriteChar('0');
	else
	{
		for(;Copy_u8Number>0; Local_u8DigitIndex++)
		{
			Local_u8ADigits[Local_u8DigitIndex] = Copy_u8Number%10;
			Copy_u8Number = Copy_u8Number/10;
		}
		Local_u8DigitIndex--;
		for(unsigned int i=Local_u8DigitIndex; i>=0; i--)
		{
			Local_u8Char = Local_u8ADigits[i]+48;
			LCD_voidWriteChar(Local_u8Char);
			if(i==0) break;
		}
	}
}

void LCD_voidSetCursor	(u8 Copy_u8LineNum, u8 Copy_u8Position)
{
	switch(Copy_u8LineNum)
	{
		case LCD_u8_LINE_ONE:
			LCD_voidSendCmd(0x80+Copy_u8Position); /* 0x80 is the start of the first line */
		break;
		
		case LCD_u8_LINE_TWO:
			LCD_voidSendCmd(0xC0+Copy_u8Position);	/* 0xC0 is the start of the second line */
		break;
	}
}

void LCD_voidWriteSpecialCharacter(u8* Copy_Pu8Pattern, u8 Copy_u8PatternPosition, u8 Copy_u8LineNum, u8 Copy_u8Position)
{
	/* Move AC to start of CGRAM */
	LCD_voidSendCmd(0b01000000 + Copy_u8PatternPosition*8);
	/* Draw the character in the CGRAM */
	LCD_voidWriteChar(Copy_Pu8Pattern[0]);
	LCD_voidWriteChar(Copy_Pu8Pattern[1]);
	LCD_voidWriteChar(Copy_Pu8Pattern[2]);
	LCD_voidWriteChar(Copy_Pu8Pattern[3]);
	LCD_voidWriteChar(Copy_Pu8Pattern[4]);
	LCD_voidWriteChar(Copy_Pu8Pattern[5]);
	LCD_voidWriteChar(Copy_Pu8Pattern[6]);
	LCD_voidWriteChar(Copy_Pu8Pattern[7]);
	
	/* Go back to DDRAM to Display the character */
	LCD_voidSetCursor(Copy_u8LineNum, Copy_u8Position);
	LCD_voidWriteChar(Copy_u8PatternPosition);
}

static void Private_voidWriteHalfPort(u8 Copy_u8Value)
{
	u8 Local_u8BitValue;
	
	Local_u8BitValue = GET_BIT(Copy_u8Value,0);
	
	if(Local_u8BitValue == DIO_u8_HIGH) 
	{
		DIO_u8SetPinValue(LCD_u8_D4_PORT, LCD_u8_D4_PIN, DIO_u8_HIGH);
	}
	else 
	{
		DIO_u8SetPinValue(LCD_u8_D4_PORT, LCD_u8_D4_PIN, DIO_u8_LOW);
	}
	
	Local_u8BitValue = GET_BIT(Copy_u8Value,1);
	
	if(Local_u8BitValue == DIO_u8_HIGH) 
	{
		DIO_u8SetPinValue(LCD_u8_D5_PORT, LCD_u8_D5_PIN, DIO_u8_HIGH);
	}
	else 
	{
		DIO_u8SetPinValue(LCD_u8_D5_PORT, LCD_u8_D5_PIN, DIO_u8_LOW);
	}
	
	Local_u8BitValue = GET_BIT(Copy_u8Value,2);
	
	if(Local_u8BitValue == DIO_u8_HIGH) 
	{
		DIO_u8SetPinValue(LCD_u8_D6_PORT, LCD_u8_D6_PIN, DIO_u8_HIGH);
	}
	else 
	{
		DIO_u8SetPinValue(LCD_u8_D6_PORT, LCD_u8_D6_PIN, DIO_u8_LOW);
	}
	
	Local_u8BitValue = GET_BIT(Copy_u8Value,3);
	
	if(Local_u8BitValue == DIO_u8_HIGH) 
	{
		DIO_u8SetPinValue(LCD_u8_D7_PORT, LCD_u8_D7_PIN, DIO_u8_HIGH);
	}
	else 
	{
		DIO_u8SetPinValue(LCD_u8_D7_PORT, LCD_u8_D7_PIN, DIO_u8_LOW);
	}	
}

void LCD_voidClear()
{
	LCD_voidSendCmd(0b0000001);
}