#ifndef MYTIMER_H
#define MYTIMER_H
#include "stm32f10x.h"

typedef struct
{
TIM_TypeDef * Timer ; // TIM1 à TIM4
unsigned short ARR ;
unsigned short PSC ;
} 

MyTimer_Struct_TypeDef ;
/*
*****************************************************************************************
* @brief
* @param -> Paramètre sous forme d ’une structure (son adresse) contenant les
informations de base
* @Note -> Fonctition à lancer systématiquement avant d ’aller plus en détail dans les
conf plus fines (PWM, codeur inc . . . )
*************************************************************************************************
*/
void MyTimer_Base_Init ( MyTimer_Struct_TypeDef * Timer ) ;
#define MyTimer_Base_Start(Timer) (Timer->CR1 |= TIM_CR1_CEN)
#define MyTimer_Base_Stop(Timer) (Timer->CR1 &= ~TIM_CR1_CEN)
#endif

/*
**************************************************************************************************
* @brief
* @param : - TIM_TypeDef * Timer : Timer concerne
- char Prio : de 0 a 15
* @Note : La fonction MyTimer_Base_ Initdoit avoir ete lancee au prealable
**************************************************************************************************
*/

//----------- version 1 interruption -------------//
//void MyTimer_ActiveIT ( TIM_TypeDef * Timer , char Prio ) ;

//----------- version 2 interruption (pointeur de fonctions) -------------//
//void ( * ptrF ) ();
void MyTimer_ActiveIT ( TIM_TypeDef * Timer , char Prio , void (*IT_function) (void) ) ;
void MyTimer_PWM( TIM_TypeDef * Timer , char Channel ) ;
void Lancer_PWM (TIM_TypeDef * Timer, char Channel);
void Cycle_PWM (TIM_TypeDef * Timer, char Channel, int pourcentage);
void Encodeur (TIM_TypeDef*Timer);
