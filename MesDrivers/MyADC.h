#include "stm32f10x.h"

typedef struct
{
ADC_TypeDef * ADC;
}
MyADC_Struct_TypeDef ;

void MyADC_Init (ADC_TypeDef*ADC);
int MyADC_Start ( ADC_TypeDef*ADC, char voie);

