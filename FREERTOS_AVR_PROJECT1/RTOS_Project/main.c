#define		F_CPU	8000000UL
#include "util/delay.h"

/* FreeRTOS Main Header files */
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"
#include "event_groups.h"

#include "BIT_MATH.h"
#include "STD_TYPES.h"
#include "DIO_Interface.h"
#include "LCD_Interface.h"
#include "LED_Interface.h"
#include "ADC_Interface.h"
#include "Motors_Interface.h"
#include "KPD_Interface.h"

#include "usart_driver.h"

/* Tasks and Funcs proto. */
void system_init(void);

void T_Actuators(void* pvParam);
void T_Login(void* pvParam);
void T_TemperatureSensor(void* pvParam);
void T_LDRSensor(void* pvParam);
void T_Display(void* pvParam);

TaskHandle_t		Tl_handle=NULL;
TaskHandle_t		T2_handle=NULL;
TaskHandle_t		T3_handle=NULL;
TaskHandle_t		T4_handle=NULL;
TaskHandle_t		T5_handle=NULL;

EventGroupHandle_t egActions;
EventGroupHandle_t egStates;
EventBits_t		   ebBits;
EventBits_t		   ebStateBits;

/* Actions */
#define E_OpenDoor			(1<<4)
#define E_BUZZER			(1<<5)
#define E_LOGIN				(1<<6)
/* States */
#define E_MAIN              (1<<0)
#define E_ENPASS            (1<<1)
#define E_ENEWPASS          (1<<2)
#define E_BLOCKED           (1<<3)
#define E_DOOR              (1<<4)
#define E_WRONGPASS		    (1<<5)

xSemaphoreHandle bsPassword;

LED_t Lights = {DIO_u8_PORTC, DIO_u8_PIN0, LED_u8_ACTIVE_HIGH};


typedef struct
{
	u32 	 Password;
}Home_t;

Home_t Smart = {1234};

int main (void)
{
	system_init();

	egActions = xEventGroupCreate();
	egStates  = xEventGroupCreate();
	vSemaphoreCreateBinary(bsPassword, 1);

	xTaskCreate(T_Actuators, NULL, 100, NULL, 5, &Tl_handle);
	xTaskCreate(T_Login, NULL, 150, NULL, 4, &T2_handle);
	xTaskCreate(T_TemperatureSensor, NULL, 100, NULL, 2, &T3_handle);
	xTaskCreate(T_LDRSensor, NULL, 100, NULL, 1, &T4_handle);
	xTaskCreate(T_Display, NULL, 100, NULL, 3, &T5_handle);


	/* Start RTOS */
	vTaskStartScheduler();

	while(1);
	return 0;
}

void T_Actuators(void* pvParam)
{
	while(1)
	{
		ebBits = xEventGroupWaitBits(egActions,
				(E_OpenDoor | E_BUZZER),
				1,
				0,
				portMAX_DELAY);

		if((ebBits&E_OpenDoor) == E_OpenDoor)
		{
			Motors_voidDCMotorON(MOTORS_u8_DC_CW);
			vTaskDelay(1000);
			Motors_voidDCMotorOFF();
			vTaskDelay(3000);
			Motors_voidDCMotorON(MOTORS_u8_DC_CCW);
			vTaskDelay(1000);
			Motors_voidDCMotorOFF();
			xEventGroupSetBits(egStates, E_MAIN);
			xSemaphoreGive(bsPassword);
			vTaskDelay(100);
		}
		if((ebBits&E_BUZZER) == E_BUZZER)
		{
			DIO_u8SetPinValue(DIO_u8_PORTB, DIO_u8_PIN0, DIO_u8_HIGH);
			vTaskDelay(1000);
			DIO_u8SetPinValue(DIO_u8_PORTB, DIO_u8_PIN0, DIO_u8_LOW);
			vTaskDelay(1000);
			xEventGroupSetBits(egStates, E_MAIN);
			xSemaphoreGive(bsPassword);
			vTaskDelay(100);
		}
	}
}

void T_Login(void* pvParam)
{
	u8 Local_u8KPDData 	    = 0;
	u16 Local_u8EnteredPass = 0;
	u8 Local_u8Cursor       = 0;
	u16 Local_u8NewPass      = 0;
	u8 Local_u8Trial        = 3;
	while(1)
	{
		if(xSemaphoreTake(bsPassword, portMAX_DELAY))
		{
			while(Local_u8EnteredPass != Smart.Password)
			{
				KPD_u8GetSwitch(&Local_u8KPDData);
				switch (Local_u8KPDData)
				{
				case'+':
					Local_u8Trial	    = 3;
					while(Local_u8Trial > 0)
					{
						xEventGroupSetBits(egStates, E_ENPASS);
						vTaskDelay(30);
						while(Local_u8Cursor<4)
						{
							KPD_u8GetSwitch(&Local_u8KPDData);
							if(Local_u8KPDData != KPD_u8_NOT_PRESSED)
							{
								Local_u8EnteredPass = (Local_u8EnteredPass*10) + (Local_u8KPDData-48);
								LCD_voidSetCursor(2,Local_u8Cursor);
								LCD_voidWriteChar('*');
								Local_u8Cursor++;
							}
						}
						if(Local_u8EnteredPass == Smart.Password)
						{
							Local_u8Trial	    = 0;
							Local_u8EnteredPass = 0;
							Local_u8Cursor		= 0;
							xEventGroupSetBits(egStates, E_ENEWPASS);
							vTaskDelay(100);
							Local_u8Cursor = 0;
							/* Get New Password */
							while(Local_u8Cursor<4)
							{
								KPD_u8GetSwitch(&Local_u8KPDData);
								if(Local_u8KPDData != KPD_u8_NOT_PRESSED)
								{
									Local_u8NewPass = (Local_u8NewPass*10) + (Local_u8KPDData-48);
									LCD_voidSetCursor(2,Local_u8Cursor);
									LCD_voidWriteChar(Local_u8KPDData);
									Local_u8Cursor++;
								}
							}
							Smart.Password = Local_u8NewPass;

							Local_u8NewPass     = 0;
							Local_u8Cursor 		= 0;
							Local_u8EnteredPass = 0;

							xEventGroupSetBits(egStates, E_MAIN);
						}
						else
						{
							Local_u8EnteredPass = 0;
							Local_u8Cursor = 0;
							xEventGroupSetBits(egStates, E_WRONGPASS);
							vTaskDelay(30);
							Local_u8Trial --;
							if(Local_u8Trial == 0)
							{
								xEventGroupSetBits(egStates, E_BLOCKED);
								xEventGroupSetBits(egActions, E_BUZZER);
								vTaskDelay(30);
							}
						}
					}
					break;

				case'-':
					Local_u8Trial = 3;
					while(Local_u8Trial > 0)
					{
						xEventGroupSetBits(egStates, E_ENPASS);
						vTaskDelay(30);
						while(Local_u8Cursor<4)
						{
							KPD_u8GetSwitch(&Local_u8KPDData);
							if(Local_u8KPDData != KPD_u8_NOT_PRESSED)
							{
								Local_u8EnteredPass = (Local_u8EnteredPass*10) + (Local_u8KPDData-48);
								LCD_voidSetCursor(2,Local_u8Cursor);
								LCD_voidWriteChar('*');
								Local_u8Cursor++;
							}
						}
						if(Local_u8EnteredPass == Smart.Password)
						{
							Local_u8Trial       = 0;
							Local_u8EnteredPass = 0;
							Local_u8NewPass     = 0;
							Local_u8Cursor		= 0;

							xEventGroupSetBits(egStates, E_OpenDoor);
							xEventGroupSetBits(egActions, E_DOOR);
						}
						else
						{
							Local_u8EnteredPass = 0;
							Local_u8Cursor = 0;

							xEventGroupSetBits(egStates, E_WRONGPASS);
							vTaskDelay(300);
							Local_u8Trial --;
							if(Local_u8Trial == 0)
							{
								xEventGroupSetBits(egStates, E_BLOCKED);
								xEventGroupSetBits(egActions, E_BUZZER);
								vTaskDelay(30);
							}
						}
					}
					break;

				default:
					break;
				}
				vTaskDelay(10);
			}
			vTaskDelay(10);
		}
	}
}

void T_TemperatureSensor(void* pvParam)
{
	u16 Local_u16DigitalValue;
	u16 Local_u16AnalogValue;
	u16	Local_u16Temperature;
	while(1)
	{
		ADC_u8GetDigitalValueSynchronous(ADC_u8_CHANNEL_0, &Local_u16DigitalValue);
		Local_u16AnalogValue = ((u32)Local_u16DigitalValue * 500) / 1024;

		Local_u16Temperature = Local_u16AnalogValue;
		if(Local_u16Temperature >= 30)
		{
			DIO_u8SetPinValue(DIO_u8_PORTC, DIO_u8_PIN3, DIO_u8_HIGH);
		}
		else
		{
			DIO_u8SetPinValue(DIO_u8_PORTC, DIO_u8_PIN3, DIO_u8_LOW);
		}
		vTaskDelay(100);
	}

}

void T_LDRSensor(void* pvParam)
{
	u16 Local_u16DigitalValue;
	u16 Local_u16AnalogValue;
	while(1)
	{
		ADC_u8GetDigitalValueSynchronous(ADC_u8_CHANNEL_1, &Local_u16DigitalValue);
		Local_u16AnalogValue = ((u32)Local_u16DigitalValue * 5000) / 1024;

		if(Local_u16AnalogValue > 2500)
		{
			LED_u8TurnOn(&Lights);
		}
		else
		{
			LED_u8TurnOff(&Lights);
		}
		vTaskDelay(100);
	}
}

void T_Display(void* pvParam)
{
	xEventGroupSetBits(egStates,E_MAIN);
	while(1)
	{
		ebStateBits = xEventGroupWaitBits(egStates,
				(E_MAIN | E_ENPASS | E_ENEWPASS | E_BLOCKED | E_DOOR | E_WRONGPASS),
				1,
				0,
				portMAX_DELAY);

		if((ebStateBits&E_MAIN) == E_MAIN)
		{
			LCD_voidSetCursor(1,0);
			LCD_voidWriteStr("+ Change Pass");
			LCD_voidSetCursor(2,0);
			LCD_voidWriteStr("- Open Door");
		}
		if((ebStateBits&E_ENPASS) == E_ENPASS)
		{
			LCD_voidClear();
			LCD_voidSetCursor(1,0);
			LCD_voidWriteStr("Enter Pass");
		}
		if((ebStateBits&E_ENEWPASS) == E_ENEWPASS)
		{
			LCD_voidClear();
			LCD_voidSetCursor(1,0);
			LCD_voidWriteStr("Enter New Pass");
		}
		if((ebStateBits&E_BLOCKED) == E_BLOCKED)
		{
			LCD_voidClear();
			LCD_voidSetCursor(1,0);
			LCD_voidWriteStr("BLOCKED !!");
			_delay_ms(2000);
		}
		if((ebStateBits&E_DOOR) == E_DOOR)
		{
			LCD_voidClear();
			LCD_voidSetCursor(1,0);
			LCD_voidWriteStr("Door Opened");
			vTaskDelay(3000);
			LCD_voidClear();
			LCD_voidWriteStr("Door Closed");
		}
		if((ebStateBits&E_WRONGPASS) == E_WRONGPASS)
		{
			LCD_voidClear();
			LCD_voidSetCursor(1,0);
			LCD_voidWriteStr("Wrong Pass");
			_delay_ms(1000);
		}
		vTaskDelay(100);
	}
}

void system_init(void)
{
	DIO_voidInit();
	ADC_voidInit();
	LCD_voidInit();
	usart_init(9600);
	usart_puts("   Smart Home  \r\n");
	usart_puts("     Group 1   \r\n");
}
