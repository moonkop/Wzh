#include "stm32f4xx.h"
#include "preProcesser.h"
#include "USART_DMA.h"
u8 dmaTxCompleteFlag = 0;
u8 dmaRxCompleteFlag = 0;
unsigned char rxbuf[100] = { 0 };
unsigned char txbuf[1000];
int rxCount = 0;
int blinkInterval = 1000;
u8 LCD_printflag = 0;

void USART1_DMA_TX_Init()
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

	DMA_InitTypeDef d;

	d.DMA_DIR = DMA_DIR_MemoryToPeripheral;
	d.DMA_Channel = DMA_Channel_4;

	d.DMA_PeripheralBaseAddr = (u32)&USART1->DR;
	d.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	d.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;
	d.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;

	d.DMA_Memory0BaseAddr = (uint32_t)txbuf;
	d.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
	d.DMA_MemoryInc = DMA_MemoryInc_Enable;
	d.DMA_MemoryBurst = DMA_MemoryBurst_Single;

	d.DMA_BufferSize = 1000;
	d.DMA_Mode = DMA_Mode_Normal;
	d.DMA_Priority = DMA_Priority_Medium;

	d.DMA_FIFOMode = DMA_FIFOMode_Disable;
	d.DMA_FIFOThreshold = DMA_FIFOStatus_HalfFull;

	DMA_Init(DMA2_Stream7, &d);

	USART_DMACmd(USART1, USART_DMAReq_Tx, ENABLE);

	DMA_ITConfig(DMA2_Stream7, DMA_IT_TC, ENABLE);

	NVIC_InitTypeDef n;
	n.NVIC_IRQChannel = DMA2_Stream7_IRQn;
	n.NVIC_IRQChannelCmd = ENABLE;
	n.NVIC_IRQChannelPreemptionPriority = 0;
	n.NVIC_IRQChannelSubPriority = 0;
	NVIC_Init(&n);

}
void USART1_DMA_RX_Init()
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

	DMA_InitTypeDef d;
	d.DMA_Channel = DMA_Channel_4;
	d.DMA_DIR = DMA_DIR_PeripheralToMemory;
	d.DMA_Mode = DMA_Mode_Normal;
	d.DMA_Priority = DMA_Priority_High;

	d.DMA_Memory0BaseAddr = (u32)rxbuf;
	d.DMA_MemoryInc = DMA_MemoryInc_Enable;
	d.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
	d.DMA_MemoryBurst = DMA_MemoryBurst_Single;

	d.DMA_PeripheralBaseAddr = (u32)USART1->DR;
	d.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;
	d.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
	d.DMA_PeripheralInc = DMA_PeripheralInc_Disable;

	d.DMA_BufferSize = 100;
	d.DMA_FIFOMode = DMA_FIFOMode_Disable;
	d.DMA_FIFOThreshold = DMA_FIFOStatus_Full;

	DMA_Init(DMA2_Stream5, &d);

	DMA_ITConfig(DMA2_Stream5, DMA_IT_TC, ENABLE);

	NVIC_InitTypeDef n;
	n.NVIC_IRQChannel = DMA2_Stream5_IRQn;
	n.NVIC_IRQChannelCmd = ENABLE;
	n.NVIC_IRQChannelPreemptionPriority = 0;
	n.NVIC_IRQChannelSubPriority = 0;
	NVIC_Init(&n);

	USART_DMACmd(USART1, USART_DMAReq_Rx, ENABLE);
}



void USART1_IRQHandler(void)
{
	if (USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)
	{
		u8 res = USART_ReceiveData(USART1);
		rxbuf[rxCount++] = res;
		if (!res)
		{
			LCD_printflag = 1;
			rxCount = 0;
		}
	}
}

void DMA2_Stream7_IRQHandler(void)
{
	if (DMA_GetITStatus(DMA2_Stream7, DMA_IT_TCIF7) != RESET)
	{
		DMA_ClearITPendingBit(DMA2_Stream7, DMA_IT_TCIF7);
		dmaTxCompleteFlag = 1;

	}
}
void DMA2_Stream5_IRQHandler(void)
{
	if (DMA_GetITStatus(DMA2_Stream5, DMA_IT_TCIF5) != RESET)
	{
		DMA_ClearITPendingBit(DMA2_Stream5, DMA_IT_TCIF5);
		dmaRxCompleteFlag = 1;

	}
}
