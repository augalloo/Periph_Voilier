#include "MyUART.h"
#include "Driver_GPIO.h"

static void(*pFnc1)(void);
static void(*pFnc2)(void);
static void(*pFnc3)(void);


void MyUART_Init(MyUSART_Struct_TypeDef usart, void(*IT_function)(void)) {
	
	// Initialisation des pins sur lesquelles on va envoyer/recevoir des messages
		usart.TX.GPIO_Conf = AltOut_Ppull;
		MyGPIO_Init(&usart.TX);
	
		usart.RX.GPIO_Conf = In_Floating;
		MyGPIO_Init(&usart.RX);
	
		//BRR = Fclock / Debit --> attention, Fclock = 36Mhz pour UART1 et 72MHz pour UART2 et 3
		if (usart.USART == USART1) {
			
			RCC->APB2ENR|=RCC_APB2ENR_USART1EN;
			usart.USART->BRR = 72e6 / usart.debit ;
			NVIC->ISER[1] |= NVIC_ISER_SETENA_5;
			NVIC_SetPriority(USART2_IRQn, usart.priorite) ;
			pFnc1 = IT_function;
		} else if (usart.USART == USART2){
			RCC->APB1ENR|=RCC_APB1ENR_USART2EN;
			usart.USART->BRR = 36e6 / usart.debit ;
			NVIC->ISER[1] |= NVIC_ISER_SETENA_6;
			NVIC_SetPriority(USART2_IRQn, usart.priorite) ;
			pFnc2 = IT_function;
		} else if (usart.USART == USART3) {
			RCC->APB1ENR|=RCC_APB1ENR_USART3EN;
			usart.USART->BRR = 36e6 / usart.debit ;
			NVIC->ISER[1] |= NVIC_ISER_SETENA_7;
			NVIC_SetPriority(USART2_IRQn, usart.priorite) ;
			pFnc3 = IT_function;
		}
		
		//On enable l'usart
	  usart.USART->CR1 |= USART_CR1_UE;
		usart.USART->CR1 &= ~USART_CR1_M ;
		usart.USART->CR1 |= USART_CR1_RXNEIE;
		usart.USART->CR1 |= USART_CR1_TE;
		usart.USART->CR1 |= USART_CR1_RE;
		usart.USART->CR2 &= ~(3<<12) ;
}

char MyUART(USART_TypeDef * USART) {
return USART->DR ;
}



// Interruptions pour les différents Usart : si le pointeur pointe sur une fonction (appelée dans l'initialisation en paramètre), alors elle est exécutée

void USART1_IRQHandler() {
	//on baisse le flag direct
	USART1->SR &= ~USART_SR_RXNE ;
	if (pFnc1 != 0){
		(*pFnc1)();
	} 		
}	


void USART2_IRQHandler() {
	//on baisse le flag direct
	USART2->SR &= ~USART_SR_RXNE ;
	if (pFnc2 != 0){
		(*pFnc2)();
	}		
}	

void USART3_IRQHandler() {
	//on baisse le flag direct
	USART3->SR &= ~USART_SR_RXNE ;
	if (pFnc3 != 0){
		(*pFnc3)();
	}	
}	
