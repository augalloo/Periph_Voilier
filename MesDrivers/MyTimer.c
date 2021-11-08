#include "stm32f10x.h"
#include "MyTimer.h"

//#include "Principal.c"


//------------  Initialisation timers  ---------------//
void MyTimer_Base_Init ( MyTimer_Struct_TypeDef * Timer ) 
{
	if (Timer->Timer==TIM1) //cas du timer1
	{
		RCC->APB2ENR |= RCC_APB2ENR_TIM1EN; //activation timer1
	}
	if (Timer->Timer==TIM2)
	{
		RCC->APB1ENR |= RCC_APB1ENR_TIM2EN; //activation timer2
	}
	if  (Timer->Timer==TIM3)
	{
		RCC->APB1ENR |= RCC_APB1ENR_TIM3EN; //activation timer3
	}
	if (Timer->Timer==TIM4)
	{
		RCC->APB1ENR |= RCC_APB1ENR_TIM4EN; //activation timer4
	}
	Timer->Timer->ARR=Timer->ARR;
	Timer->Timer->PSC=Timer->PSC;
	
}




//------------  Interruption timers version 2 (pointeur de fonctions) ---------------//

static void ( * ptrF1 ) ();
static void ( * ptrF2 ) ();
static void ( * ptrF3 ) ();
static void ( * ptrF4 ) ();


	
void MyTimer_ActiveIT ( TIM_TypeDef * Timer , char Prio , void (* IT_function ) ( void ) ) {
	
		Timer->DIER|=TIM_DIER_UIE;  //autorisation interruption
	
		if (Timer==TIM1)  //cas du timer1
	{
		NVIC->ISER[0] |=NVIC_ISER_SETENA_25;  //ligne correspondant au timer dans la NVIC
		NVIC->IP[0]|=Prio;  //on definit l'ordre de priorité de notre timer
		ptrF1=IT_function;
	}	

	if (Timer==TIM2)
	{
  	NVIC->ISER[0] |=NVIC_ISER_SETENA_28;
		NVIC->IP[0]|=Prio;
		ptrF2=IT_function;
	}
	if (Timer==TIM3)
	{
		NVIC->ISER[0] |= NVIC_ISER_SETENA_29;
		NVIC->IP[0]|=Prio;
		ptrF3=IT_function;
	}
	if (Timer==TIM4)
	{
		NVIC->ISER[0] |= NVIC_ISER_SETENA_30;
		NVIC->IP[0]|=Prio;
		ptrF4=IT_function;
	}

}

void TIM2_IRQHandler ( void )
{
	
	if (ptrF2 != 0)
		(*ptrF2) ();
	TIM2->SR&=~(TIM_SR_UIF);   //On abaisse la flag UIF déclanché par l'UIE dans la fonction au-dessus 
	
}

void TIM3_IRQHandler ( void )
{
		if (ptrF3 != 0)
		(*ptrF3) ();
		
	TIM3->SR&=~(TIM_SR_UIF);   //On abaisse la flag UIF déclanché par l'UIE dans la fonction au-dessus 
}

void TIM4_IRQHandler ( void )
{
		if (ptrF4 != 0)
		(*ptrF4) ();
		
	TIM4->SR&=~(TIM_SR_UIF);   //On abaisse la flag UIF déclanché par l'UIE dans la fonction au-dessus 
}

void TIM1_UP_IRQHandler ( void )
{
		if (ptrF1 != 0)
		(*ptrF1) ();
		
	TIM1->SR&=~(TIM_SR_UIF);   //On abaisse la flag UIF déclanché par l'UIE dans la fonction au-dessus 
}

/**
* @brief
* @param....
* @Note Active le channel spécifié sur Timer le timer spécifié
* la gestion de la configuration I/O n’est pas faite dans cette fonction
* ni le réglage de la période de la PWM (ARR, PSC)
*/


void MyTimer_PWM( TIM_TypeDef * Timer , char Channel ) 
{
	if (Timer==TIM1)
	{
		 Timer->BDTR|=TIM_BDTR_MOE; 
	
	}
	switch(Channel)
	{ //p386
		case 1:
			//Efface mode 2
		//Timer->CCER |= TIM_CCER_CC1E;
			Timer->CCMR1&=~(0x7<<4);
			//Mode 1
			Timer->CCMR1|=(0x6<<4);  //(110 au 4eme bit de CCMR1)
		  Timer->CCMR1|= TIM_CCMR1_OC1PE;
		break;
		case 2:
		//	Timer->CCER |= TIM_CCER_CC2E;
		//Efface mode 2
			Timer->CCMR1&=~(0x7<<12);
			//Mode 1
			Timer->CCMR1|=(0x6<<12);  //(110 au 12eme bit de CCMR1)
		  Timer->CCMR1|= TIM_CCMR1_OC2PE;
		break;
		case 3:
		//	Timer->CCER |= TIM_CCER_CC3E;
				//Efface mode 2
			Timer->CCMR2&=~(0x7<<4);
			//Mode 1
			Timer->CCMR2|=(0x6<<4);  //(110 au 4eme bit de CCMR2)
		  Timer->CCMR2|= TIM_CCMR2_OC3PE;
		break;
		case 4:
		//	Timer->CCER |= TIM_CCER_CC4E;
			//Efface mode 2
			Timer->CCMR2&=~(0x7<<12);
			//Mode 1
			Timer->CCMR2|=(0x6<<12);  //(110 au 12eme bit de CCMR2)
		  Timer->CCMR2|= TIM_CCMR2_OC4PE;
		break;
	}
}

void Lancer_PWM (TIM_TypeDef * Timer, char Channel)
{
	switch (Channel)
	{
		case 1:
			Timer->CCER |= TIM_CCER_CC1E;;
		break;
		case 2 :
			Timer->CCER |= TIM_CCER_CC2E;
		break;
		case 3 :
			Timer->CCER |= TIM_CCER_CC3E;
		break;
		case 4 :
			Timer->CCER |= TIM_CCER_CC4E;
		break;
			
	}
			
}


void Cycle_PWM (TIM_TypeDef * Timer, char Channel, int pourcentage)
{
	int reel=(pourcentage*(Timer->ARR+1))/100 ;	
	switch(Channel)
	{
		case 1:
			Timer->CCR1=reel;
		break;
		case 2:
			
			Timer->CCR2=reel;
		break;
		case 3:
			Timer->CCR3=reel;
		break;
		case 4:
			Timer->CCR4=reel;
		break;
	}
}

void Encodeur (TIM_TypeDef*Timer)
{
	
	
	Timer->CCMR1|=TIM_CCMR1_CC1S;
	Timer->CCMR1|=TIM_CCMR1_CC2S;
	
	Timer->CCER&=~TIM_CCER_CC1P;
	Timer->CCER&=~TIM_CCER_CC1NP;
	Timer->CCER&=~TIM_CCMR1_IC1F;
	
	Timer->CCER&=~TIM_CCER_CC2P;
	Timer->CCER&=~TIM_CCER_CC2NP;
	Timer->CCER&=~TIM_CCMR1_IC2F;
	
	Timer->SMCR|=(0x3<<0); //Bit SMS à 011 on compte sur les fronts TI1 et TI2
  Timer->CR1|=TIM_CR1_CEN;

	
}





