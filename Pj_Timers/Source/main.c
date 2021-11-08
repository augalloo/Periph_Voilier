#include "stm32f10x.h"
#include "MyTimer.h"
#include "Driver_GPIO.h"
#include "MyUART.h"


	static MyTimer_Struct_TypeDef test;
	static MyTimer_Struct_TypeDef test2;

//	void Callback (void){
//		MyGPIO_Toggle(GPIO_Struct.GPIO,1);
//	}
	

int main() {

/// Test PWM
//	test2.Timer = TIM3;
//	test2.PSC=1;
//	test2.ARR=359;
//	MyTimer_Base_Init(&test2);
//	MyTimer_PWM(test2.Timer, 4) ;
//	MyTimer_DutyCycle(test2.Timer, 90) ;
//	
//	MyTimer_Base_Start(test2.Timer);
//	
	/*
	On utilise nos fonctions de MyTimer.h pour gérer les interruptions des timers
	et appeler la fonction définie/programmée par l'utilisateur dans le main
	*/
	//MyTimer_ActiveIT(test.Timer, 2, Callback ); 
	//MyTimer_ActiveIT(test2.Timer, 3, C2 ); 
	


	while(1) {
	}
}
