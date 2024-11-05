/*************************************************************/
/*************** Name	: Ahmed Zaky *************************/
/*************** Date	: 19/1/2021  *************************/
/*************** Version: 1.0V 		 *************************/
/*************** SWC	: ADC 		 *************************/
/*************************************************************/

#ifndef ADC_PRIVATE_H
#define ADC_PRIVATE_H

#define ADC_u8_SFIOR_REG				*((volatile u8*)0x50)
#define ADC_u8_ADMUX_REG				*((volatile u8*)0x27)
#define ADC_u8_ADCSRA_REG				*((volatile u8*)0x26)
#define ADC_u8_ADCH_REG					*((volatile u8*)0x25)
#define ADC_u8_ADCL_REG					*((volatile u8*)0x24)

#define ADC_u16_ADC_REG					*((volatile u16*)0x24) /* To get both ADCH and ADCL at one time */
#endif