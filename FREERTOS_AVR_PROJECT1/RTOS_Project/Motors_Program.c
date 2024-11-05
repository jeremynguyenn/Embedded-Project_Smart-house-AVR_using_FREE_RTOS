/*************************************************************/
/*************** Name	: Ahmed Zaky *************************/
/*************** Date	: 16/1/2021  *************************/
/*************** Version: 1.0V 		 *************************/
/*************** SWC	: MOTORS 	 *************************/
/*************************************************************/
#define F_CPU 8000000UL
#include <util/delay.h>
/* Library Layer */
#include "BIT_MATH.h"
#include "STD_TYPES.h"
/* MCAL */
#include "DIO_Interface.h"
/* HAL */
#include "MOTORS_Interface.h"
#include "MOTORS_Private.h"
#include "MOTORS_Config.h"

void Motors_voidStepperMotorON(u8 Copy_u8Angle)
{
	/* Determining steps from the data sheet */								/*** Check the start of LEC 10 ***/
	float Local_floatHalfStep = 5.625/64; /* Stride Angle */
	float Local_floatFullStep = 2*Local_floatHalfStep;
	u8	  Local_u8StepsNumber = Copy_u8Angle/Local_floatFullStep;
	u8	  Local_u8Iterator    = 0;
	
	/* Set Common Pin with High (From datasheet) */
	DIO_u8SetPinValue(MOTORS_u8_COMMON_PORT, MOTORS_u8_COMMON_PIN, DIO_u8_HIGH);
	
	for(Local_u8Iterator = 0; Local_u8Iterator<Local_u8StepsNumber/4; Local_u8Iterator++)
	{
		
		DIO_u8SetPinValue(MOTORS_u8_BLUE_PORT, MOTORS_u8_BLUE_PIN, DIO_u8_LOW);
		DIO_u8SetPinValue(MOTORS_u8_PINK_PORT, MOTORS_u8_PINK_PIN, DIO_u8_HIGH);
		DIO_u8SetPinValue(MOTORS_u8_YELLOW_PORT, MOTORS_u8_YELLOW_PIN, DIO_u8_HIGH);
		DIO_u8SetPinValue(MOTORS_u8_ORANGE_PORT, MOTORS_u8_ORANGE_PIN, DIO_u8_HIGH);
		_delay_ms(10);
		
		DIO_u8SetPinValue(MOTORS_u8_BLUE_PORT, MOTORS_u8_BLUE_PIN, DIO_u8_HIGH);
		DIO_u8SetPinValue(MOTORS_u8_PINK_PORT, MOTORS_u8_PINK_PIN, DIO_u8_LOW);
		DIO_u8SetPinValue(MOTORS_u8_YELLOW_PORT, MOTORS_u8_YELLOW_PIN, DIO_u8_HIGH);
		DIO_u8SetPinValue(MOTORS_u8_ORANGE_PORT, MOTORS_u8_ORANGE_PIN, DIO_u8_HIGH);
		_delay_ms(10);
		
		DIO_u8SetPinValue(MOTORS_u8_BLUE_PORT, MOTORS_u8_BLUE_PIN, DIO_u8_HIGH);
		DIO_u8SetPinValue(MOTORS_u8_PINK_PORT, MOTORS_u8_PINK_PIN, DIO_u8_HIGH);
		DIO_u8SetPinValue(MOTORS_u8_YELLOW_PORT, MOTORS_u8_YELLOW_PIN, DIO_u8_LOW);
		DIO_u8SetPinValue(MOTORS_u8_ORANGE_PORT, MOTORS_u8_ORANGE_PIN, DIO_u8_HIGH);
		_delay_ms(10);
		
		DIO_u8SetPinValue(MOTORS_u8_BLUE_PORT, MOTORS_u8_BLUE_PIN, DIO_u8_HIGH);
		DIO_u8SetPinValue(MOTORS_u8_PINK_PORT, MOTORS_u8_PINK_PIN, DIO_u8_HIGH);
		DIO_u8SetPinValue(MOTORS_u8_YELLOW_PORT, MOTORS_u8_YELLOW_PIN, DIO_u8_HIGH);
		DIO_u8SetPinValue(MOTORS_u8_ORANGE_PORT, MOTORS_u8_ORANGE_PIN, DIO_u8_LOW);
		_delay_ms(10);
	}
}

void Motors_voidStepperMotorOFF(void)
{
	DIO_u8SetPinValue(MOTORS_u8_COMMON_PORT, MOTORS_u8_COMMON_PIN, DIO_u8_LOW);
	
	DIO_u8SetPinValue(MOTORS_u8_BLUE_PORT, MOTORS_u8_BLUE_PIN, DIO_u8_HIGH);
	DIO_u8SetPinValue(MOTORS_u8_PINK_PORT, MOTORS_u8_PINK_PIN, DIO_u8_HIGH);
	DIO_u8SetPinValue(MOTORS_u8_YELLOW_PORT, MOTORS_u8_YELLOW_PIN, DIO_u8_HIGH);
	DIO_u8SetPinValue(MOTORS_u8_ORANGE_PORT, MOTORS_u8_ORANGE_PIN, DIO_u8_HIGH);
}

void Motors_voidDCMotorON (u8 Copy_u8Direction)
{
	if(Copy_u8Direction == MOTORS_u8_DC_CW)
	{
		DIO_u8SetPinValue(MOTORS_u8_DC_CCW_PORT, MOTORS_u8_DC_CCW_PIN, DIO_u8_LOW);
		DIO_u8SetPinValue(MOTORS_u8_DC_CW_PORT, MOTORS_u8_DC_CW_PIN, DIO_u8_HIGH); 
	}
	else if(Copy_u8Direction == MOTORS_u8_DC_CCW)
	{
		DIO_u8SetPinValue(MOTORS_u8_DC_CW_PORT, MOTORS_u8_DC_CW_PIN, DIO_u8_LOW);
		DIO_u8SetPinValue(MOTORS_u8_DC_CCW_PORT, MOTORS_u8_DC_CCW_PIN, DIO_u8_HIGH);
	}
}

void Motors_voidDCMotorOFF		(void)
{
	DIO_u8SetPinValue(MOTORS_u8_DC_CCW_PORT, MOTORS_u8_DC_CCW_PIN, DIO_u8_LOW);
	DIO_u8SetPinValue(MOTORS_u8_DC_CW_PORT, MOTORS_u8_DC_CW_PIN, DIO_u8_LOW);
}