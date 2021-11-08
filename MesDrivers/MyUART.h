#ifndef MYUART_H
#define MYUART_H
#include "stm32f10x.h"
#include "Driver_GPIO.h"

typedef struct
{
	USART_TypeDef * USART ;
	MyGPIO_Struct_TypeDef  RX;
	MyGPIO_Struct_TypeDef  TX;
	float debit;
	char priorite;
} MyUSART_Struct_TypeDef ;

void MyUART_Init(MyUSART_Struct_TypeDef usart, void(*IT_function)(void));
 
char MyUART(USART_TypeDef * USART);

#endif
