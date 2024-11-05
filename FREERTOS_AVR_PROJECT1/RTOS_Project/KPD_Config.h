/*************************************************************/
/*************** Name	: Ahmed Zaky *************************/
/*************** Date	: 13/1/2021  *************************/
/*************** Version: 1.0V 		 *************************/
/*************** SWC	: KEYPAD 	 *************************/
/*************************************************************/

#ifndef KPD_CONFIG_H
#define KPD_CONFIG_H

#define KPD_u8_ROWS_NUMBER			4
#define KPD_u8_COLS_NUMBER			4

/* ROWS => OUTPUT */
#define KPD_u8_ROWS_PORT			DIO_u8_PORTC
#define KPD_u8_R1_PIN				DIO_u8_PIN4
#define KPD_u8_R2_PIN				DIO_u8_PIN5
#define KPD_u8_R3_PIN				DIO_u8_PIN6
#define KPD_u8_R4_PIN				DIO_u8_PIN7
		
/* COLUMNS => INPUT */		
#define KPD_u8_COLUMNS_PORT			DIO_u8_PORTD
#define KPD_u8_C1_PIN				DIO_u8_PIN4
#define KPD_u8_C2_PIN				DIO_u8_PIN5
#define KPD_u8_C3_PIN				DIO_u8_PIN6
#define KPD_u8_C4_PIN				DIO_u8_PIN7


#define KPD_ROWS_PINS				{KPD_u8_R1_PIN, KPD_u8_R2_PIN, KPD_u8_R3_PIN, KPD_u8_R4_PIN}
#define KPD_COLS_PINS				{KPD_u8_C1_PIN, KPD_u8_C2_PIN, KPD_u8_C3_PIN, KPD_u8_C4_PIN}

#define KPD_KEYS					{{'7', '8', '9', '/'},    \
									 {'4', '5', '6', '*'},    \
									 {'1', '2', '3', '-'},    \
									 {'r', '0', '=', '+'}}

#endif
