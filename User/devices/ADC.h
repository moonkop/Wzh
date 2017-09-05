#ifndef  __ADC_H
#define __ADC_H
#include "stm32f4xx.h"
void ADC3_init(void);

void ADC1_Init(void);

u16 Get_Adc(u8 ch);

u16 GetAdc3(u8 ch);

u16 Get_Adc_Average(u8 ch, u8 times);

#endif // !__ADC_H

