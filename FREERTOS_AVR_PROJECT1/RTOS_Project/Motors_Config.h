/*************************************************************/
/*************** Name	: Ahmed Zaky *************************/
/*************** Date	: 16/1/2021  *************************/
/*************** Version: 1.0V 		 *************************/
/*************** SWC	: MOTORS 	 *************************/
/*************************************************************/

#ifndef MOTORS_CONFIG_H
#define MOTORS_CONFIG_H

/*** Macros for STEPPER MOTOR ***/

#define MOTORS_u8_COMMON_PIN			DIO_u8_PIN0
#define MOTORS_u8_COMMON_PORT			DIO_u8_PORTA

#define MOTORS_u8_BLUE_PIN				DIO_u8_PIN1
#define MOTORS_u8_BLUE_PORT				DIO_u8_PORTA

#define MOTORS_u8_PINK_PIN				DIO_u8_PIN2
#define MOTORS_u8_PINK_PORT				DIO_u8_PORTA

#define MOTORS_u8_YELLOW_PIN			DIO_u8_PIN3
#define MOTORS_u8_YELLOW_PORT			DIO_u8_PORTA

#define MOTORS_u8_ORANGE_PIN			DIO_u8_PIN4
#define MOTORS_u8_ORANGE_PORT			DIO_u8_PORTA

/*** Macros for DC MOTOR ***/

#define MOTORS_u8_DC_CW_PIN				DIO_u8_PIN1
#define MOTORS_u8_DC_CW_PORT			DIO_u8_PORTC

#define MOTORS_u8_DC_CCW_PIN			DIO_u8_PIN2
#define MOTORS_u8_DC_CCW_PORT			DIO_u8_PORTC


#endif
