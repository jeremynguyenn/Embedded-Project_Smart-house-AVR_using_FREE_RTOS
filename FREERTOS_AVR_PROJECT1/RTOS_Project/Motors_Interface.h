/*************************************************************/
/*************** Name	: Ahmed Zaky *************************/
/*************** Date	: 16/1/2021  *************************/
/*************** Version: 1.0V 		 *************************/
/*************** SWC	: MOTORS 	 *************************/
/*************************************************************/

#ifndef MOTORS_INTERFACE_H
#define MOTORS_INTERFACE_H

#define MOTORS_u8_DC_CW 	1
#define MOTORS_u8_DC_CCW	0

void Motors_voidStepperMotorON (u8 Copy_u8Angle);
void Motors_voidStepperMotorOFF(void);

void Motors_voidDCMotorON 		(u8 Copy_u8Direction);
void Motors_voidDCMotorOFF		(void);
#endif