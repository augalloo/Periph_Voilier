#ifndef MYGPIO_H
#define MYGPIO_H
#include "stm32f10x.h"

typedef struct
{
	GPIO_TypeDef * GPIO ;
	char GPIO_Pin ; //numero de 0 a 15
	char GPIO_Conf ; // v o i r c i de s sou s
} MyGPIO_Struct_TypeDef ;

#define In_Floating 0x4 // a comple te r
#define In_PullDown 0x8  // a comple te r
#define In_PullUp 0x8  // a comple te r
#define In_Analog 0x0  // a comple te r
#define Out_Ppull 0x1  // a comple te r
#define Out_OD 0x5 // a comple te r
#define AltOut_Ppull 0x9  // a comple te r
#define AltOut_OD 0xD // a comple te r

void MyGPIO_Init ( MyGPIO_Struct_TypeDef * GPIOStructPtr) ;
int MyGPIO_Read ( GPIO_TypeDef * GPIO , char GPIO_Pin ) ; // re nv oie 0 ou a u t re chose d i f f e r e n t de 0
void MyGPIO_Set ( GPIO_TypeDef * GPIO , char GPIO_Pin ) ;
void MyGPIO_Reset ( GPIO_TypeDef * GPIO , char GPIO_Pin ) ;
void MyGPIO_Toggle ( GPIO_TypeDef * GPIO , char GPIO_Pin ) ;

#endif
