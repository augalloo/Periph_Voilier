#include "stm32f10x.h"
#include "MyADC.h"
#include "MyTimer.h"
#include "Driver_GPIO.h"

void MyADC_Init (ADC_TypeDef*ADC)
{
	if (ADC==ADC1)
	{
		RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;
		RCC->CFGR|=RCC_CFGR_ADCPRE_DIV6;
	}
	if (ADC==ADC2)
	{
		RCC->APB2ENR |= RCC_APB2ENR_ADC2EN;
	  RCC->CFGR|=RCC_CFGR_ADCPRE_DIV6;
	}
	ADC->CR2|= ADC_CR2_ADON;
	ADC->SQR1&=~ADC_SQR1_L; //1 seul conversion
	
}



int MyADC_Start ( ADC_TypeDef*ADC, char voie)
{
	 //power on 
	int resultat;
	ADC->CR2|= ADC_CR2_ADON;
	ADC->SQR3|=(voie << 0); //1er bit de SQR3 car une seule conversion
	while ((ADC->SR & (ADC_SR_EOC))==0)
	{
	}
	
	resultat= ADC->DR;
	return resultat;		
}	

