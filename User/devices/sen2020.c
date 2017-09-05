#include"stm32f4xx.h"
#include"sen2020.h"
#include "USART.h"
#include "preProcesser.h"



//  a[0] a[1] a[2] a[3] a[4] a[5] a[6] a[7]
//left									right
u8 SEN2020Array[8];
extern u8* sensers;


// 00000000
//HIGH LOW
//left right
u8 SEN2020Datas;

unsigned char SEN2020Analogdatas[8];
unsigned char SEN2020AnalogRxFlag = 0;
unsigned char dataIndex = 0;


void _SEN2020_init_channel(GPIO_TypeDef* GPIOx, int gpio_pin)
{

	GPIO_InitTypeDef g;
	g.GPIO_Mode = GPIO_Mode_IN;
	g.GPIO_OType = GPIO_OType_OD;
	g.GPIO_PuPd = GPIO_PuPd_UP;
	g.GPIO_Speed = GPIO_Speed_100MHz;
	g.GPIO_Pin = gpio_pin;
	GPIO_Init(GPIOx, &g);
}


void SEN2020_init()
{

	_SEN2020_init_channel(GPIOC, GPIO_Pin_9); //left
	_SEN2020_init_channel(GPIOC, GPIO_Pin_11);
	_SEN2020_init_channel(GPIOB, GPIO_Pin_6);
	_SEN2020_init_channel(GPIOE, GPIO_Pin_5);
	_SEN2020_init_channel(GPIOE, GPIO_Pin_6);
	_SEN2020_init_channel(GPIOA, GPIO_Pin_6);
	_SEN2020_init_channel(GPIOA, GPIO_Pin_8);
	_SEN2020_init_channel(GPIOD, GPIO_Pin_3);	//right
	//USART6_init();


	//usart init
	
}

u8 getSEN2020DigitalData()
{
	SEN2020Array[0] = GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_9); //left
	SEN2020Array[1] = GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_11);
	SEN2020Array[2] = GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_6);
	SEN2020Array[3] = GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_5);
	SEN2020Array[4] = GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_6);
	SEN2020Array[5] = GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_6);
	SEN2020Array[6] = GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_8);
	SEN2020Array[7] = GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_3);	//right
	SEN2020Datas = 0;
	for (u8 i = 0; i < 8; i++)
	{
		SEN2020Datas >>= 1;
		SEN2020Datas |= SEN2020Array[i]? 0x80 :0;
	}
	sensers=SEN2020Array;
	return SEN2020Datas;

}

void SEN2020USARTEnable()
{
	USART_ClearITPendingBit(USART6, USART_IT_RXNE);
	USART_ITConfig(USART6, USART_IT_RXNE, ENABLE);

}
void SEN2020USARTDisable()
{

	USART_ITConfig(USART6, USART_IT_RXNE, DISABLE);
	USART_ClearITPendingBit(USART6, USART_IT_RXNE);

}

void getSEN2020AnalogData()
{
	dataIndex = 0;
	SEN2020USARTEnable();
	USART_SendData(USART6, 0xd2);
	SEN2020AnalogRxFlag = 0;

}


void SEN2020ImportData(u8 data)
{
	SEN2020Analogdatas[dataIndex++] = data;
	if (dataIndex==8)
	{
		SEN2020USARTDisable();
		SEN2020AnalogRxFlag = 1;

	}
}
void waitforSen2020Data()
{
	while (!SEN2020AnalogRxFlag)
	{
		;
	}
}
