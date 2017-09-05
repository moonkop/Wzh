#include "../../Driver/stm32f4xx.h"
#include "sen2020.h"
#include "USART.h"
#include "preProcesser.h"
#include "../drivers/RespCom.h"
#include "../LCD_driver/LCD_print.h"


extern int pulse;
//raspberry 
void USART1_init()
{

	GPIO_InitTypeDef g;
	g.GPIO_Mode = GPIO_Mode_AF;
	g.GPIO_OType = GPIO_OType_OD;
	g.GPIO_Pin = GPIO_Pin_9;
	g.GPIO_PuPd = GPIO_PuPd_NOPULL;
	g.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(GPIOA, &g);

	g.GPIO_Pin = GPIO_Pin_10;
	g.GPIO_OType = GPIO_OType_PP;
	g.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOA, &g);

	GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_USART1);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF_USART1);

	USART_InitTypeDef a;
	a.USART_BaudRate = 9600;
	a.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	a.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
	a.USART_Parity = USART_Parity_No;
	a.USART_StopBits = USART_StopBits_1;
	a.USART_WordLength = USART_WordLength_8b;
	USART_Init(USART1, &a);
	USART_Cmd(USART1, ENABLE);

	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);

	NVIC_InitTypeDef n;
	n.NVIC_IRQChannel = USART1_IRQn;
	n.NVIC_IRQChannelCmd = ENABLE;
	n.NVIC_IRQChannelPreemptionPriority = 1;
	n.NVIC_IRQChannelSubPriority = 0;
	NVIC_Init(&n);

}
//debug
void USART2_init()
{

	GPIO_InitTypeDef g;
	g.GPIO_Mode = GPIO_Mode_AF;
	g.GPIO_OType = GPIO_OType_OD;
	g.GPIO_Pin = GPIO_Pin_2;
	g.GPIO_PuPd = GPIO_PuPd_NOPULL;
	g.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(GPIOA, &g);

	g.GPIO_Pin = GPIO_Pin_3;
	g.GPIO_OType = GPIO_OType_PP;
	g.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOA, &g);

	GPIO_PinAFConfig(GPIOA, GPIO_PinSource2, GPIO_AF_USART2);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource3, GPIO_AF_USART2);


	USART_InitTypeDef a;
	a.USART_BaudRate = 115200;
	a.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	a.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
	a.USART_Parity = USART_Parity_No;
	a.USART_StopBits = USART_StopBits_1;
	a.USART_WordLength = USART_WordLength_8b;
	USART_Init(USART2, &a);
	USART_Cmd(USART2, ENABLE);

//	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);

	NVIC_InitTypeDef n;
	n.NVIC_IRQChannel = USART2_IRQn;
	n.NVIC_IRQChannelCmd = ENABLE;
	n.NVIC_IRQChannelPreemptionPriority = 1;
	n.NVIC_IRQChannelSubPriority = 0;
	NVIC_Init(&n);
}
//lobotCotroller
void USART3_init()
{
	GPIO_InitTypeDef g;
	g.GPIO_Mode = GPIO_Mode_AF;
	g.GPIO_OType = GPIO_OType_OD;
	g.GPIO_Pin = GPIO_Pin_10;
	g.GPIO_PuPd = GPIO_PuPd_NOPULL;
	g.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(GPIOB, &g);

	g.GPIO_Pin = GPIO_Pin_11;
	g.GPIO_OType = GPIO_OType_PP;
	g.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOB, &g);

	GPIO_PinAFConfig(GPIOB, GPIO_PinSource11, GPIO_AF_USART3);
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource10, GPIO_AF_USART3);


	USART_InitTypeDef a;
	a.USART_BaudRate = 9600;
	a.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	a.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
	a.USART_Parity = USART_Parity_No;
	a.USART_StopBits = USART_StopBits_1;
	a.USART_WordLength = USART_WordLength_8b;
	USART_Init(USART3, &a);
	USART_Cmd(USART3, ENABLE);

	//todo interrupt
	//USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);


	NVIC_InitTypeDef n;
	n.NVIC_IRQChannel = USART3_IRQn;
	n.NVIC_IRQChannelCmd = ENABLE;
	n.NVIC_IRQChannelPreemptionPriority = 1;
	n.NVIC_IRQChannelSubPriority = 0;
	NVIC_Init(&n);

}
void USART4_init()
{
	GPIO_InitTypeDef g;
	g.GPIO_Mode = GPIO_Mode_AF;
	g.GPIO_OType = GPIO_OType_OD;
	g.GPIO_Pin = GPIO_Pin_0;
	g.GPIO_PuPd = GPIO_PuPd_NOPULL;
	g.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(GPIOA, &g);

	g.GPIO_Pin = GPIO_Pin_1;
	g.GPIO_OType = GPIO_OType_PP;
	g.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOA, &g);

	GPIO_PinAFConfig(GPIOA, GPIO_PinSource1, GPIO_AF_UART4);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource0, GPIO_AF_UART4);


	USART_InitTypeDef a;
	a.USART_BaudRate = 115200;
	a.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	a.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
	a.USART_Parity = USART_Parity_No;
	a.USART_StopBits = USART_StopBits_1;
	a.USART_WordLength = USART_WordLength_8b;
	USART_Init(UART4, &a);
	USART_Cmd(UART4, ENABLE);

}
void USART5_init()
{
	GPIO_InitTypeDef g;
	g.GPIO_Mode = GPIO_Mode_AF;
	g.GPIO_OType = GPIO_OType_OD;
	g.GPIO_Pin = GPIO_Pin_2;
	g.GPIO_PuPd = GPIO_PuPd_NOPULL;
	g.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(GPIOD, &g);

	g.GPIO_Pin = GPIO_Pin_12;
	g.GPIO_OType = GPIO_OType_PP;
	g.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOC, &g);

	GPIO_PinAFConfig(GPIOC, GPIO_PinSource12, GPIO_AF_UART5);
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource2, GPIO_AF_UART5);


	USART_InitTypeDef a;
	a.USART_BaudRate = 115200;
	a.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	a.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
	a.USART_Parity = USART_Parity_No;
	a.USART_StopBits = USART_StopBits_1;
	a.USART_WordLength = USART_WordLength_8b;
	USART_Init(UART5, &a);
	USART_Cmd(UART5, ENABLE);

}
//sen2020
void USART6_init()
{

	GPIO_InitTypeDef g;
	g.GPIO_Mode = GPIO_Mode_AF;
	g.GPIO_OType = GPIO_OType_OD;
	g.GPIO_Pin = GPIO_Pin_6;
	g.GPIO_PuPd = GPIO_PuPd_NOPULL;
	g.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(GPIOC, &g);

	g.GPIO_Pin = GPIO_Pin_7;
	g.GPIO_OType = GPIO_OType_PP;
	g.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOC, &g);

	GPIO_PinAFConfig(GPIOC, GPIO_PinSource6, GPIO_AF_USART6);
	GPIO_PinAFConfig(GPIOC, GPIO_PinSource7, GPIO_AF_USART6);



	USART_InitTypeDef a;
	a.USART_BaudRate = 115200;
	a.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	a.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
	a.USART_Parity = USART_Parity_No;
	a.USART_StopBits = USART_StopBits_1;
	a.USART_WordLength = USART_WordLength_8b;
	USART_Init(USART6, &a);
	USART_Cmd(USART6, ENABLE);

	USART_ITConfig(USART6, USART_IT_RXNE, ENABLE);



	NVIC_InitTypeDef n;
	n.NVIC_IRQChannel = USART6_IRQn;
	n.NVIC_IRQChannelCmd = ENABLE;
	n.NVIC_IRQChannelPreemptionPriority = 1;
	n.NVIC_IRQChannelSubPriority = 0;
	NVIC_Init(&n);

}



//int fputc(int ch, FILE *f)
//{
//	USART_SendData(USART, (u8)ch);
//	while (USART_GetFlagStatus(USART, USART_FLAG_TXE) == RESET);
//	return ch;
//}

void USART3_SendByByter(u8 Data)
{
	USART_GetFlagStatus(USART3, USART_FLAG_TC);
	USART_SendData(USART3, Data);
	while (USART_GetFlagStatus(USART3, USART_FLAG_TC) == RESET);
}

void Usart3_Send(u8 *data_to_send, u8 len)
{
	u8 i = 0;
	for (i = 0; i<len; i++)
	{
		USART3_SendByByter(data_to_send[i]);
	}
}


#ifdef __cplusplus
extern "C"
{

#endif // __cplusplus

	void USART1_IRQHandler(void) {
		if (USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)
		{
			USART_ClearITPendingBit(USART1, USART_IT_RXNE);
			unsigned char data = USART_ReceiveData(USART1);
			RaspiImportData(data);
		}
	}


	void USART6_IRQHandler(void)
	{
		if (USART_GetITStatus(USART6, USART_IT_RXNE) != RESET)
		{
			USART_ClearITPendingBit(USART6, USART_IT_RXNE);
			unsigned char data = USART_ReceiveData(USART6);
			SEN2020ImportData(data);
		}
	}

	//DEBUG no need
	//void USART2_IRQHandler(void)
	//{
	//	if (USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)
	//	{
	//		USART_ClearITPendingBit(USART2, USART_IT_RXNE);
	//	}
	//}

	//lobotcotroller no need
	//void USART3_IRQHandler(void)
	//{
	//	if (USART_GetITStatus(USART3, USART_IT_RXNE) != RESET)
	//	{
	//		USART_ClearITPendingBit(USART3, USART_IT_RXNE);
	//	}
	//}

#ifdef __cplusplus
}

#endif // __cplusplus





