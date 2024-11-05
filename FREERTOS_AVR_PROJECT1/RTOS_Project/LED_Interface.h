/*************************************************************/
/*************** Name	: Ahmed Zaky *************************/
/*************** Date	: 10/1/2021  *************************/
/*************** Version: 1.0V 		 *************************/
/*************** SWC	: LED 		 *************************/
/*************************************************************/


#ifndef LED_INTERFACE_H
#define LED_INTERFACE_H


typedef struct
{
	u8 LED_u8PORTID;
	u8 LED_u8PINID;
	u8 LED_u8ConnectionType;
} LED_t;

/* Macros for LED Connection Type */
#define LED_u8_ACTIVE_HIGH		1
#define LED_u8_ACTIVE_LOW		0

u8 LED_u8TurnOn	(LED_t* Copy_u8LED);
u8 LED_u8TurnOff(LED_t* Copy_u8LED);
u8 LED_u8Toggle	(LED_t* Copy_u8LED);

#endif 