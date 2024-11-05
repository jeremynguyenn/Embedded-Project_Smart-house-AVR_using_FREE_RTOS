/*************************************************************/
/*************** Name	: Ahmed Zaky *************************/
/*************** Date	: 13/1/2021  *************************/
/*************** Version: 1.0V 		 *************************/
/*************** SWC	: KEYPAD 	 *************************/
/*************************************************************/

/* Library Layer */
#include "STD_TYPES.h"
#include "BIT_MATH.h"
/* MCAL */
#include "DIO_Interface.h"
/* HAL */
#include "KPD_Interface.h"
#include "KPD_Private.h"
#include "KPD_Config.h"

u8 KPD_u8GetSwitch(u8* Copy_Pu8ReturnedSwitch)
{
	u8 Local_u8ErrorState = STD_TYPES_OK;
	u8 Local_u8PinValue;
	u8 Local_u8Flag = 0;
	static u8 Local_Au8RowsPinsArr[KPD_u8_ROWS_NUMBER] 						= KPD_ROWS_PINS;  /* Also make a Ports array if the ins are on different ports */
	static u8 Local_Au8ColsPinsArr[KPD_u8_COLS_NUMBER] 						= KPD_COLS_PINS;
	static u8 Local_Au8KPDValuesArr[KPD_u8_ROWS_NUMBER][KPD_u8_COLS_NUMBER] = KPD_KEYS;
	/* Made them static so it doesn't get pushed every time I call the function */
	
	if(Copy_Pu8ReturnedSwitch != NULL)
	{
		*Copy_Pu8ReturnedSwitch = KPD_u8_NOT_PRESSED;
		for(u8 Local_u8RowsCounter = 0; Local_u8RowsCounter<KPD_u8_ROWS_NUMBER; Local_u8RowsCounter++)
		{
			/* Activate each Row */
			DIO_u8SetPinValue(KPD_u8_ROWS_PORT, Local_Au8RowsPinsArr[Local_u8RowsCounter], DIO_u8_LOW);
			/* Check Column Pins*/
			for(u8 Local_u8ColsCounter = 0; Local_u8ColsCounter<KPD_u8_COLS_NUMBER; Local_u8ColsCounter++)
			{
				/* Check if a Column is low */
				DIO_u8GetPinValue(KPD_u8_COLUMNS_PORT, Local_Au8ColsPinsArr[Local_u8ColsCounter], &Local_u8PinValue);
				if(Local_u8PinValue == DIO_u8_LOW)
				{
					*Copy_Pu8ReturnedSwitch = Local_Au8KPDValuesArr[Local_u8RowsCounter][Local_u8ColsCounter];
					/* To make the function stuck so the number is returned only one time */
					while(Local_u8PinValue == DIO_u8_LOW)
					{
						DIO_u8GetPinValue(KPD_u8_COLUMNS_PORT, Local_Au8ColsPinsArr[Local_u8ColsCounter], &Local_u8PinValue);
					}
					Local_u8Flag = 1; /* A flag that indicates that i found the pressed switch */
					break;
				}
			}
			/* Deactivate current Row by adding High again */
			DIO_u8SetPinValue(KPD_u8_ROWS_PORT, Local_Au8RowsPinsArr[Local_u8RowsCounter], DIO_u8_HIGH);
			if(Local_u8Flag == 1)
			{
				break;
			}
		}
	}
	else
	{
		Local_u8ErrorState = STD_TYPES_NOK;
	}
	
	return Local_u8ErrorState;
}