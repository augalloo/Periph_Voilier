#include "stm32f10x.h"
#include "Driver_GPIO.h"
#include "MyTimer.h"
#include "MyUART.h"
#include "MyADC.h"

MyGPIO_Struct_TypeDef rx ;
MyGPIO_Struct_TypeDef tx ;
MyGPIO_Struct_TypeDef GPIO_PWM ;
MyGPIO_Struct_TypeDef GPIO_bds ;

MyUSART_Struct_TypeDef uart_test ;
MyTimer_Struct_TypeDef timer_uart;

signed char toto;
char channel;

MyGPIO_Struct_TypeDef  GPIO_Struct;
	
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
	//Cycle_PWM(timer_uart.Timer, channel, toto) ;
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
	

	MyUART_Init(uart_test, Reception_USART);
	
	timer_uart.Timer = TIM4;
	timer_uart.PSC=0;
	timer_uart.ARR=720;
	MyTimer_Base_Init(&timer_uart);
	MyTimer_Base_Start(timer_uart.Timer);
	MyTimer_PWM(timer_uart.Timer, channel) ;
	Lancer_PWM(timer_uart.Timer, channel);
	
	
	do
	{
		
	}while(1) ;
}
