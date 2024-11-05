################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../ADC_Program.c \
../DIO_Program.c \
../KPD_Program.c \
../LCD_Program.c \
../LED_Program.c \
../Motors_Program.c \
../main.c \
../usart_driver.c 

OBJS += \
./ADC_Program.o \
./DIO_Program.o \
./KPD_Program.o \
./LCD_Program.o \
./LED_Program.o \
./Motors_Program.o \
./main.o \
./usart_driver.o 

C_DEPS += \
./ADC_Program.d \
./DIO_Program.d \
./KPD_Program.d \
./LCD_Program.d \
./LED_Program.d \
./Motors_Program.d \
./main.d \
./usart_driver.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -I"D:\NTI\RTOS Course\Workspaces\Eclipse Workspace\RTOS_Project\FreeRTOS\Inc" -I"D:\NTI\RTOS Course\Workspaces\Eclipse Workspace\RTOS_Project\FreeRTOS\Inc" -Wall -g2 -gstabs -Os -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


