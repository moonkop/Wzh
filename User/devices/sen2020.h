#ifndef __SEN2020_H
#define __SEN2020_H
#include "USART.h"
#include "USART_DMA.h"

extern u8 SEN2020Array[8];

extern u8 SEN2020Datas;

extern unsigned char SEN2020Analogdatas[8];
extern unsigned char SEN2020AnalogRxFlag;


void SEN2020_init(void);
u8 getSEN2020DigitalData(void);
void SEN2020USARTEnable();
void SEN2020USARTDisable();
void getSEN2020AnalogData();
void SEN2020ImportData(u8 data);
void waitforSen2020Data();
#endif // !__SEN2020_H
