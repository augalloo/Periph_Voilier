#include "stm32f10x.h"
#include "Driver_GPIO.h"
#include "MyTimer.h"
#include "MyUART.h"
#include "MyADC.h"

MyGPIO_Struct_TypeDef tension_bat ;
MyGPIO_Struct_TypeDef rx ;
MyGPIO_Struct_TypeDef tx ;
MyGPIO_Struct_TypeDef GPIO_PWM ;
MyGPIO_Struct_TypeDef GPIO_bds ;
MyGPIO_Struct_TypeDef  GPIO_Struct;

MyTimer_Struct_TypeDef timer_transinfo;
MyTimer_Struct_TypeDef timer_uart;

MyUSART_Struct_TypeDef uart_test ;

ADC_TypeDef * ADCtension_batterie ;

char * mot = "Batterie faible\n";
signed char toto;
char channel;


void Reception_USART (void){
	toto= MyUART(uart_test.USART);
	
	if (toto <= 0) {
		GPIO_bds.GPIO->ODR &= ~GPIO_ODR_ODR7 ;
		toto = - toto;
		Cycle_PWM(timer_uart.Timer, channel, toto) ;
	} else if (toto > 0) {
		GPIO_bds.GPIO->ODR = GPIO_ODR_ODR7 ;
		Cycle_PWM(timer_uart.Timer, channel, toto) ;
	}
}

void Test_batterie (void){
	int i = 0;
	int max = 2^12 - 1 ;
	int tension;
	//tension = MyADC_Start(ADCtension_batterie, 10);
	tension = 0.1*max;
	if (tension < 0.2*max) {
		while(mot[i] != '\0') {	
			uart_test.USART->DR = mot[i];
			while((uart_test.USART->SR & USART_SR_TXE) == 0){
			}
			i ++;
		}
	}		
}

int main(void)
{
	channel = 1;
	
	rx.GPIO = GPIOA ;
	rx.GPIO_Pin = 10 ;
	MyGPIO_Init (&rx);
	tx.GPIO = GPIOA ;
	tx.GPIO_Pin = 9 ;
	MyGPIO_Init (&tx);
	
	uart_test.RX = rx ;
	uart_test.TX = tx ;
	uart_test.debit = 9600 ;
	uart_test.priorite = 3 ;
	uart_test.USART = USART1 ;
	MyUART_Init(uart_test, Reception_USART);
	
	// Port GPIO PWM Rotation plateau
	GPIO_PWM.GPIO = GPIOB ;
	GPIO_PWM.GPIO_Pin = 6 ;
	GPIO_PWM.GPIO_Conf = AltOut_Ppull ;
	MyGPIO_Init (&GPIO_PWM);
	
	// Port GPIO bit de sens plateau
	GPIO_bds.GPIO = GPIOB ;
	GPIO_bds.GPIO_Pin = 7 ;
	GPIO_bds.GPIO_Conf = Out_Ppull ;
	MyGPIO_Init (&GPIO_bds);
	
	// Port GPIO ADC Tension batterie
	tension_bat.GPIO = GPIOC ;
	tension_bat.GPIO_Pin = 0 ;
	tension_bat.GPIO_Conf = In_Analog ;
	MyGPIO_Init (&tension_bat);
	
	ADCtension_batterie = ADC1 ;
	MyADC_Init (ADCtension_batterie);
	
	timer_uart.Timer = TIM4;
	timer_uart.PSC=0;
	timer_uart.ARR=720;
	MyTimer_Base_Init(&timer_uart);
	MyTimer_Base_Start(timer_uart.Timer);
	MyTimer_PWM(timer_uart.Timer, channel) ;
	Lancer_PWM(timer_uart.Timer, channel);
	

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

