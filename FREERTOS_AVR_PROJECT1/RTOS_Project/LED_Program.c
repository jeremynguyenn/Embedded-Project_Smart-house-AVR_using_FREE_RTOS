/*************************************************************/
/*************** Name	: Ahmed Zaky *************************/
/*************** Date	: 10/1/2021  *************************/
/*************** Version: 1.0V 		 *************************/
/*************** SWC	: LED 		 *************************/
/*************************************************************/

/* Library Layer */
#include "STD_TYPES.h"
#include "BIT_MATH.h"
/* MCAL */
#include "DIO_Interface.h"
/* HAL */
#include "LED_Interface.h"
#include "LED_Private.h"
#include "LED_Config.h"


u8 LED_u8TurnOn	(LED_t* Copy_u8LED)
{
	u8 Local_u8ErrorState = STD_TYPES_OK;
	
	if((Copy_u8LED->LED_u8PORTID <= DIO_u8_PORTD) && (Copy_u8LED->LED_u8PINID <= DIO_u8_PIN7)
		&& ((Copy_u8LED->LED_u8ConnectionType == LED_u8_ACTIVE_HIGH) || (Copy_u8LED->LED_u8ConnectionType == LED_u8_ACTIVE_LOW)) && Copy_u8LED != NULL)
	{
		if(Copy_u8LED->LED_u8ConnectionType == LED_u8_ACTIVE_HIGH)
		{
			DIO_u8SetPinValue(Copy_u8LED->LED_u8PORTID, Copy_u8LED->LED_u8PINID, DIO_u8_HIGH);
		}
		else
		{
			DIO_u8SetPinValue(Copy_u8LED->LED_u8PORTID, Copy_u8LED->LED_u8PINID, DIO_u8_LOW);
		}
	}
	else
	{
		Local_u8ErrorState = STD_TYPES_NOK;
	}
	return Local_u8ErrorState;
}

u8 LED_u8TurnOff(LED_t* Copy_u8LED)
{
	u8 Local_u8ErrorState = STD_TYPES_OK;
	
	if((Copy_u8LED->LED_u8PORTID <= DIO_u8_PORTD) && (Copy_u8LED->LED_u8PINID <= DIO_u8_PIN7)
		&& ((Copy_u8LED->LED_u8ConnectionType == LED_u8_ACTIVE_HIGH) || (Copy_u8LED->LED_u8ConnectionType == LED_u8_ACTIVE_LOW)) && Copy_u8LED != NULL)
	{
		if(Copy_u8LED->LED_u8ConnectionType == LED_u8_ACTIVE_HIGH)
		{
			DIO_u8SetPinValue(Copy_u8LED->LED_u8PORTID, Copy_u8LED->LED_u8PINID, DIO_u8_LOW);
		}
		else
		{
			DIO_u8SetPinValue(Copy_u8LED->LED_u8PORTID, Copy_u8LED->LED_u8PINID, DIO_u8_HIGH);
		}
	}
	else
	{
		Local_u8ErrorState = STD_TYPES_NOK;
	}
	return Local_u8ErrorState;
}

u8 LED_u8Toggle	(LED_t* Copy_u8LED)
{
	u8 Local_u8ErrorState = STD_TYPES_OK;
	
	if((Copy_u8LED->LED_u8PORTID <= DIO_u8_PORTD) && (Copy_u8LED->LED_u8PINID <= DIO_u8_PIN7))
	{
		DIO_u8TogglePinValue(Copy_u8LED->LED_u8PORTID, Copy_u8LED->LED_u8PINID);
	}
	else
	{
		Local_u8ErrorState = STD_TYPES_NOK;
	}
	return Local_u8ErrorState;
}
