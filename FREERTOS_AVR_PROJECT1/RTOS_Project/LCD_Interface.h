/*************************************************************/
/*************** Name	: Ahmed Zaky *************************/
/*************** Date	: 11/1/2021  *************************/
/*************** Version: 1.0V 		 *************************/
/*************** SWC	: LCD 		 *************************/
/*************************************************************/

#ifndef LCD_INTERFACE_H
#define LCD_INTERFACE_H

/* Macros for Line Number */
#define LCD_u8_LINE_ONE		1
#define LCD_u8_LINE_TWO		2


void LCD_voidInit	  	(void);
void LCD_voidSendCmd  	(u8 Copy_u8Cmd);
void LCD_voidWriteChar	(u8 Copy_u8Char);
void LCD_voidWriteStr 	(const u8* Copy_Pu8Str);
void LCD_voidWriteNumber(u32  Copy_u8Number);

void LCD_voidSetCursor	(u8 Copy_u8LineNum, u8 Copy_u8Position);
void LCD_voidWriteSpecialCharacter(u8* Copy_Pu8Pattern, u8 Copy_u8PatternPosition, u8 Copy_u8LineNum, u8 Copy_u8Position); /* Pattern Position => in CGRAM */
void LCD_voidClear();

#endif