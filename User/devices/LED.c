#include  "../../Driver/stm32f4xx.h"
#include "LED.h"
#include "preProcesser.h"
void LED_init()
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
	GPIO_InitTypeDef a;
	a.GPIO_Mode = GPIO_Mode_OUT;
	a.GPIO_OType = GPIO_OType_PP;
	a.GPIO_Speed = GPIO_Speed_100MHz;
	a.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_3;
	GPIO_Init(GPIOE, &a);
	a.GPIO_Pin = GPIO_Pin_9;
	GPIO_Init(GPIOG, &a);
	LED_SET(0,0);
	LED_SET(1,0);
	LED_SET(2,0);
}

u8 ledState[3] ={ 0};


void LED_flash(int i )
{
	LED_SET(i, !ledState[i]);
}


void LED_SET(int i, int mode)
{
	if (!mode)
	{

		switch (i)
		{

		case 0:
			GPIO_SetBits(GPIOE, GPIO_Pin_3);
			ledState[0] = 0;
			break;
		case 1:
			GPIO_SetBits(GPIOE, GPIO_Pin_4); 
			ledState[1] = 0;
			break;
		case 2:
			GPIO_SetBits(GPIOG, GPIO_Pin_9); 
			ledState[2] = 0;
			break;

		}
	}
	else
	{
		switch (i)
		{

		case 0:
			GPIO_ResetBits(GPIOE, GPIO_Pin_3);
			ledState[0] = 1;
			break;
		case 1:
			GPIO_ResetBits(GPIOE, GPIO_Pin_4);
			ledState[1] = 1;
			break;
		case 2:
			GPIO_ResetBits(GPIOG, GPIO_Pin_9);
			ledState[2] = 1;
			break;

		}
	}
}
