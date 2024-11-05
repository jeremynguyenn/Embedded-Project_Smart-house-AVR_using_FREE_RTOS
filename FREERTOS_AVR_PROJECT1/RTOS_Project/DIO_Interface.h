/*************************************************************/
/*************** Name	: Ahmed Zaky *************************/
/*************** Date	: 6/1/2021 	 *************************/
/*************** Version: 1.0V 		 *************************/
/*************** SWC	: DIO 		 *************************/
/*************************************************************/

#ifndef DIO_INTERFACE_H
#define DIO_INTERFACE_H

/* Macros For PORT ID */
#define DIO_u8_PORTA 0
#define DIO_u8_PORTB 1
#define DIO_u8_PORTC 2
#define DIO_u8_PORTD 3

/* Macros For PIN ID */
#define DIO_u8_PIN0 0
#define DIO_u8_PIN1 1
#define DIO_u8_PIN2 2
#define DIO_u8_PIN3 3
#define DIO_u8_PIN4 4
#define DIO_u8_PIN5 5
#define DIO_u8_PIN6 6
#define DIO_u8_PIN7 7

/* Macros For PIN DIRECTION */
#define DIO_u8_INPUT 	0
#define DIO_u8_OUTPUT 	1

/* Macros For PIN VALUE */
#define DIO_u8_HIGH 1
#define DIO_u8_LOW 	0

u8 DIO_u8SetPinDirection  (u8 Copy_u8PortID, u8 Copy_u8PinID, u8 Copy_u8PinDirection);
u8 DIO_u8SetPinValue 	  (u8 Copy_u8PortID, u8 Copy_u8PinID, u8 Copy_u8PinValue);
u8 DIO_u8GetPinValue 	  (u8 Copy_u8PortID, u8 Copy_u8PinID, u8* Copy_pu8PinValue);
u8 DIO_u8TogglePinValue	  (u8 Copy_u8PortID, u8 Copy_u8PinID);

u8 DIO_u8SetPortDirection (u8 Copy_u8PortID, u8 Copy_u8PortDirection);
u8 DIO_u8SetPortValue 	  (u8 Copy_u8PortID, u8 Copy_u8PortValue);
u8 DIO_u8GetPortValue 	  (u8 Copy_u8PortID, u8* Copy_pu8PortValue);

void DIO_voidInit		  (void);  /*Initializes the registers during runtime*/

#endif
