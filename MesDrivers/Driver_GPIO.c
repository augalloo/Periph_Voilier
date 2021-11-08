#include "Driver_GPIO.h"


void MyGPIO_Init (MyGPIO_Struct_TypeDef * GPIOStructPtr ) {
	char pin = GPIOStructPtr->GPIO_Pin ;
	
	if (GPIOStructPtr->GPIO == GPIOA) {
		RCC->APB2ENR |= RCC_APB2ENR_IOPAEN ;
	} else if (GPIOStructPtr->GPIO == GPIOB) {
		RCC->APB2ENR |= RCC_APB2ENR_IOPBEN ;
	} else if (GPIOStructPtr->GPIO == GPIOC) {
		RCC->APB2ENR |= RCC_APB2ENR_IOPCEN ;
	} else if (GPIOStructPtr->GPIO == GPIOD) {
		RCC->APB2ENR |= RCC_APB2ENR_IOPDEN ;
	}
	
	switch(GPIOStructPtr->GPIO_Conf) {
		case In_PullUp :
			if (pin <= 7) {
				GPIOStructPtr->GPIO->CRL &= ~(0xF << pin*4) ;
				GPIOStructPtr->GPIO->CRL |= (In_PullUp << pin*4) ;
				GPIOStructPtr->GPIO->ODR |= (0x01 << pin) ;
			} else {
				GPIOStructPtr->GPIO->CRH &= ~(0xF << (pin-8)*4) ;
				GPIOStructPtr->GPIO->CRH |= (In_PullUp << (pin-8)*4) ;
				GPIOStructPtr->GPIO->ODR |= (0x01 << pin) ;
			}
		default :
			if (pin <= 7) {
				GPIOStructPtr->GPIO->CRL &= ~(0xF << pin*4) ;
				GPIOStructPtr->GPIO->CRL |= (GPIOStructPtr->GPIO_Conf << pin*4) ;
			} else {
				GPIOStructPtr->GPIO->CRH &= ~(0xF << (pin-8)*4) ;
				GPIOStructPtr->GPIO->CRH |= (GPIOStructPtr->GPIO_Conf << (pin-8)*4) ;
			}
	}
} 

int MyGPIO_Read ( GPIO_TypeDef * GPIO , char GPIO_Pin ){
	if (GPIO->IDR & (0x1<<GPIO_Pin)){
		return 1;
	}else{
		return 0;
	}
}

void MyGPIO_Set(GPIO_TypeDef * GPIO , char GPIO_Pin ) {
	GPIO->ODR |= (0x01 <<  GPIO_Pin) ;
}

void MyGPIO_Reset(GPIO_TypeDef * GPIO , char GPIO_Pin ) {
	GPIO->ODR &= ~(0x01 <<  GPIO_Pin) ;
}

void MyGPIO_Toggle(GPIO_TypeDef * GPIO , char GPIO_Pin ) {
	GPIO->ODR ^= (0x01 << GPIO_Pin) ;
}
