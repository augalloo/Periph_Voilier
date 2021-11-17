#include "stm32f10x.h"
#include "Driver_GPIO.h"
#include "MyTimer.h"
#include "MyUART.h"
#include "MyADC.h"

MyGPIO_Struct_TypeDef tension_bat ;

//MyUSART_Struct_TypeDef uart_test ;
MyTimer_Struct_TypeDef timer_transinfo;

MyGPIO_Struct_TypeDef rx ;
MyGPIO_Struct_TypeDef tx ;
MyUSART_Struct_TypeDef uart_trans ;

ADC_TypeDef * ADCtension_batterie ;



char * mot = "Batterie faible\n";

void Test_batterie (void){
	int i = 0;
	int max = 2^12 - 1 ;
	int tension;
	tension = MyADC_Start(ADCtension_batterie, 10);
	if (tension < 0.2*max) {
		while(mot[i] != '\0') {	
			uart_trans.USART->DR = mot[i];
			while((uart_trans.USART->SR & USART_SR_TXE) == 0){
			}
			i ++;
		}
	}		
}

int main(void)
{
	ADCtension_batterie = ADC1 ;
	MyADC_Init (ADCtension_batterie);

	// Port GPIO ADC Tension batterie
	tension_bat.GPIO = GPIOC ;
	tension_bat.GPIO_Pin = 0 ;
	tension_bat.GPIO_Conf = In_Analog ;
	MyGPIO_Init (&tension_bat);
	
	rx.GPIO = GPIOA ;
	rx.GPIO_Pin = 10 ;
	MyGPIO_Init (&rx);
	tx.GPIO = GPIOA ;
	tx.GPIO_Pin = 9 ;
	MyGPIO_Init (&tx);
	
	uart_trans.RX = rx ;
	uart_trans.TX = tx ;
	uart_trans.debit = 9600 ;
	uart_trans.priorite = 3 ;
	uart_trans.USART = USART1 ;
	MyUART_Init(uart_trans, 0);
	
	
	timer_transinfo.Timer = TIM1;
	timer_transinfo.PSC=7199;
	timer_transinfo.ARR=29999;
	MyTimer_Base_Init(&timer_transinfo);
	MyTimer_Base_Start(timer_transinfo.Timer);
	MyTimer_ActiveIT ( timer_transinfo.Timer , 5 , Test_batterie) ;
	
	do
	{
		
	}while(1) ;
}
