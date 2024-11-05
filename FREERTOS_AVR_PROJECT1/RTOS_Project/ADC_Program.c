/*************************************************************/
/*************** Name	: Ahmed Zaky *************************/
/*************** Date	: 19/1/2021  *************************/
/*************** Version: 1.0V 		 *************************/
/*************** SWC	: ADC 		 *************************/
/*************************************************************/

#include "BIT_MATH.h"
#include "STD_TYPES.h"

#include "ADC_Interface.h"
#include "ADC_Private.h"
#include "ADC_Config.h"

/* Busy flag */
static u8 ADC_u8BusyFlag = 0;
/* Global Pointers */
static void(* ADC_pfNotification)(u16) = NULL;

void ADC_voidInit		  (void)
{
	/* 1- Select Vref = AVCC */
	CLR_BIT(ADC_u8_ADMUX_REG, 7);
	SET_BIT(ADC_u8_ADMUX_REG, 6);
	
	/* 2- Select Right Adjustment */
	CLR_BIT(ADC_u8_ADMUX_REG, 5);
	
	/* 3- Select Conversion Mode = Single Conversion Mode */
	CLR_BIT(ADC_u8_ADCSRA_REG, 5);
	
	/* 4- Select Prescaler value = 64 for (8 MHz Clock) */
	SET_BIT(ADC_u8_ADCSRA_REG, 2);
	SET_BIT(ADC_u8_ADCSRA_REG, 1);
	CLR_BIT(ADC_u8_ADCSRA_REG, 0);
	
	/* 5- ADC Enabele */
	SET_BIT(ADC_u8_ADCSRA_REG, 7);
}

u8   ADC_u8GetDigitalValueSynchronous(u8 Copy_u8ChannelNumber, u16* Copy_pu16DigitalValue)
{
	u8  Local_u8ErrorState      = STD_TYPES_OK;
	u32 Local_u32TimeOutCounter = 0;
	
	if((Copy_u8ChannelNumber<32) && (Copy_pu16DigitalValue != NULL))
	{
		/* Select Channel Number */
		ADC_u8_ADMUX_REG &= 0b11100000; /* Clear the 5 bits channel number (MUX bits) before assigning the new channel number */
		ADC_u8_ADMUX_REG |= Copy_u8ChannelNumber; /* I make it using OR logic to not lose the data in the remaining bits of the register*/
		/* Start Convrsion */
		SET_BIT(ADC_u8_ADCSRA_REG, 6);
		/* Wait for ADC Flag (ADIF) to be up */
		while((GET_BIT(ADC_u8_ADCSRA_REG, 4) == 0) && (Local_u32TimeOutCounter < ADC_u32_TIMEOUT_COUNTER))
		{
			Local_u32TimeOutCounter++;
		}
		
		if(GET_BIT(ADC_u8_ADCSRA_REG, 4) != 0) /* Flag was set before the counter times out */
		{
			/* Clear flag */
			SET_BIT(ADC_u8_ADCSRA_REG, 4);
			/* Read Digital Value */
			*Copy_pu16DigitalValue = ADC_u16_ADC_REG; /* From ADCH and ADCL Registers */
		}
		else
		{
			Local_u8ErrorState = STD_TYPES_NOK;
		}
		
	}
	else
	{
		Local_u8ErrorState = STD_TYPES_NOK;
	}
	
	return Local_u8ErrorState;
}

u8   ADC_u8GetDigitalValueAsynchronous(u8 Copy_u8ChannelNumber, void(*Copy_pfNotification)(u16))
{
	u8 Local_u8ErrorState = STD_TYPES_OK;
	
	if((Copy_u8ChannelNumber<32) && (Copy_pfNotification != NULL) && (ADC_u8BusyFlag == 0)) /* The flag is not busy */
	{
		/* Set Busy Flag */
		ADC_u8BusyFlag = 1;
		/* Update Global Pointers so ISR can access them */
		ADC_pfNotification = Copy_pfNotification;
		/* Select Channel */
		ADC_u8_ADMUX_REG &= 0b11100000;
		ADC_u8_ADMUX_REG |= Copy_u8ChannelNumber;
		/* Enable Interrupt of ADC */
		SET_BIT(ADC_u8_ADCSRA_REG, 3);
		/* Start Conversion */
		SET_BIT(ADC_u8_ADCSRA_REG, 6);
	}
	else
	{
		Local_u8ErrorState = STD_TYPES_NOK;
	}
	
	return Local_u8ErrorState;
}

/* ADC ISR Implementation */
void __vector_16(void) __attribute__((signal));
void __vector_16(void)
{
	if(ADC_pfNotification != NULL)
	{
		/* Disable Interrupt */
		CLR_BIT(ADC_u8_ADCSRA_REG, 3);
		/* Call Notification Function */
		ADC_pfNotification(ADC_u16_ADC_REG);
		/* Clear Busy Flag */
		ADC_u8BusyFlag = 0;
	}
}