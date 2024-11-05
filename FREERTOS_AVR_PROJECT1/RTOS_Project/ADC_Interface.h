/*************************************************************/
/*************** Name	: Ahmed Zaky *************************/
/*************** Date	: 19/1/2021  *************************/
/*************** Version: 1.0V 		 *************************/
/*************** SWC	: ADC 		 *************************/
/*************************************************************/

#ifndef ADC_INTERFACE_H
#define ADC_INTERFACE_H

/* Macros for Channel Number (Single Ended) */
#define ADC_u8_CHANNEL_0			0
#define ADC_u8_CHANNEL_1			1
#define ADC_u8_CHANNEL_2			2
#define ADC_u8_CHANNEL_3			3
#define ADC_u8_CHANNEL_4			4
#define ADC_u8_CHANNEL_5			5
#define ADC_u8_CHANNEL_6			6
#define ADC_u8_CHANNEL_7			7


void ADC_voidInit		  			  (void);
u8   ADC_u8GetDigitalValueSynchronous (u8 Copy_u8ChannelNumber, u16* Copy_pu16DigitalValue);
u8   ADC_u8GetDigitalValueAsynchronous(u8 Copy_u8ChannelNumber, void(*Copy_pfNotification)(u16));  /* Las arguement is pointer to function */

u8   ADC_u8StartChainConversion();
#endif