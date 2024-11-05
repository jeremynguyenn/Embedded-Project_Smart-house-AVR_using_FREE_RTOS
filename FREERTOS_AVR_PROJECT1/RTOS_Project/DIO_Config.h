/*************************************************************/
/*************** Name	: Ahmed Zaky *************************/
/*************** Date	: 6/1/2021 	 *************************/
/*************** Version: 1.0V 		 *************************/
/*************** SWC	: DIO 		 *************************/
/*************************************************************/

#ifndef DIO_CONFIG_H
#define DIO_CONFIG_H

/* Macros for Initial Direction */
/* Options:
	1- DIO_u8_INITIAL_INPUT
	2- DIO_u8_INITIAL_OUTPUT
*/

#define DIO_u8_PA0_Direction				DIO_u8_INITIAL_INPUT
#define DIO_u8_PA1_Direction    			DIO_u8_INITIAL_INPUT
#define DIO_u8_PA2_Direction    			DIO_u8_INITIAL_OUTPUT
#define DIO_u8_PA3_Direction    			DIO_u8_INITIAL_OUTPUT
#define DIO_u8_PA4_Direction    			DIO_u8_INITIAL_OUTPUT
#define DIO_u8_PA5_Direction    			DIO_u8_INITIAL_OUTPUT
#define DIO_u8_PA6_Direction    			DIO_u8_INITIAL_OUTPUT
#define DIO_u8_PA7_Direction    			DIO_u8_INITIAL_OUTPUT
											
#define DIO_u8_PB0_Direction    			DIO_u8_INITIAL_OUTPUT
#define DIO_u8_PB1_Direction    			DIO_u8_INITIAL_INPUT
#define DIO_u8_PB2_Direction    			DIO_u8_INITIAL_INPUT
#define DIO_u8_PB3_Direction    			DIO_u8_INITIAL_INPUT
#define DIO_u8_PB4_Direction    			DIO_u8_INITIAL_INPUT
#define DIO_u8_PB5_Direction    			DIO_u8_INITIAL_INPUT
#define DIO_u8_PB6_Direction    			DIO_u8_INITIAL_INPUT
#define DIO_u8_PB7_Direction    			DIO_u8_INITIAL_INPUT
											
#define DIO_u8_PC0_Direction    			DIO_u8_INITIAL_OUTPUT
#define DIO_u8_PC1_Direction    			DIO_u8_INITIAL_OUTPUT
#define DIO_u8_PC2_Direction    			DIO_u8_INITIAL_OUTPUT
#define DIO_u8_PC3_Direction    			DIO_u8_INITIAL_OUTPUT
#define DIO_u8_PC4_Direction    			DIO_u8_INITIAL_OUTPUT
#define DIO_u8_PC5_Direction    			DIO_u8_INITIAL_OUTPUT
#define DIO_u8_PC6_Direction    			DIO_u8_INITIAL_OUTPUT
#define DIO_u8_PC7_Direction    			DIO_u8_INITIAL_OUTPUT
											
#define DIO_u8_PD0_Direction    			DIO_u8_INITIAL_INPUT
#define DIO_u8_PD1_Direction    			DIO_u8_INITIAL_INPUT
#define DIO_u8_PD2_Direction    			DIO_u8_INITIAL_INPUT
#define DIO_u8_PD3_Direction    			DIO_u8_INITIAL_INPUT
#define DIO_u8_PD4_Direction    			DIO_u8_INITIAL_INPUT
#define DIO_u8_PD5_Direction    			DIO_u8_INITIAL_INPUT
#define DIO_u8_PD6_Direction    			DIO_u8_INITIAL_INPUT
#define DIO_u8_PD7_Direction    			DIO_u8_INITIAL_INPUT


/* Macros for Initial Values for PINS */
/* Options: 
	1- DIO_u8_OUTPUT_HIGH
	2- DIO_u8_OUTPUT_LOW
	3- DIO_u8_INPUT_FLOATING
	4- DIO_u8_INPUT_PULLUP
*/

#define DIO_u8_PA0_INITIAL_VALUE			DIO_u8_INPUT_FLOATING
#define DIO_u8_PA1_INITIAL_VALUE  			DIO_u8_INPUT_FLOATING
#define DIO_u8_PA2_INITIAL_VALUE  			DIO_u8_OUTPUT_LOW
#define DIO_u8_PA3_INITIAL_VALUE  			DIO_u8_OUTPUT_LOW
#define DIO_u8_PA4_INITIAL_VALUE  			DIO_u8_OUTPUT_LOW
#define DIO_u8_PA5_INITIAL_VALUE  			DIO_u8_OUTPUT_LOW
#define DIO_u8_PA6_INITIAL_VALUE  			DIO_u8_OUTPUT_LOW
#define DIO_u8_PA7_INITIAL_VALUE  			DIO_u8_OUTPUT_LOW
												
#define DIO_u8_PB0_INITIAL_VALUE  			DIO_u8_OUTPUT_LOW
#define DIO_u8_PB1_INITIAL_VALUE  			DIO_u8_INPUT_FLOATING
#define DIO_u8_PB2_INITIAL_VALUE  			DIO_u8_INPUT_FLOATING
#define DIO_u8_PB3_INITIAL_VALUE  			DIO_u8_INPUT_FLOATING
#define DIO_u8_PB4_INITIAL_VALUE  			DIO_u8_INPUT_FLOATING
#define DIO_u8_PB5_INITIAL_VALUE  			DIO_u8_INPUT_FLOATING
#define DIO_u8_PB6_INITIAL_VALUE  			DIO_u8_INPUT_FLOATING
#define DIO_u8_PB7_INITIAL_VALUE  			DIO_u8_INPUT_FLOATING
												
#define DIO_u8_PC0_INITIAL_VALUE  			DIO_u8_OUTPUT_LOW
#define DIO_u8_PC1_INITIAL_VALUE  			DIO_u8_OUTPUT_LOW
#define DIO_u8_PC2_INITIAL_VALUE  			DIO_u8_OUTPUT_LOW
#define DIO_u8_PC3_INITIAL_VALUE  			DIO_u8_OUTPUT_LOW
#define DIO_u8_PC4_INITIAL_VALUE  			DIO_u8_OUTPUT_HIGH
#define DIO_u8_PC5_INITIAL_VALUE  			DIO_u8_OUTPUT_HIGH
#define DIO_u8_PC6_INITIAL_VALUE  			DIO_u8_OUTPUT_HIGH
#define DIO_u8_PC7_INITIAL_VALUE  			DIO_u8_OUTPUT_HIGH
												
#define DIO_u8_PD0_INITIAL_VALUE  			DIO_u8_INPUT_FLOATING
#define DIO_u8_PD1_INITIAL_VALUE  			DIO_u8_INPUT_FLOATING
#define DIO_u8_PD2_INITIAL_VALUE  			DIO_u8_INPUT_FLOATING
#define DIO_u8_PD3_INITIAL_VALUE  			DIO_u8_INPUT_FLOATING
#define DIO_u8_PD4_INITIAL_VALUE  			DIO_u8_INPUT_PULLUP
#define DIO_u8_PD5_INITIAL_VALUE  			DIO_u8_INPUT_PULLUP
#define DIO_u8_PD6_INITIAL_VALUE  			DIO_u8_INPUT_PULLUP
#define DIO_u8_PD7_INITIAL_VALUE  			DIO_u8_INPUT_PULLUP

#endif
