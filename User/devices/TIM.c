
#include "../../Driver/stm32f4xx.h"
#include "preProcesser.h"
#include "TIM.h"
//#include "task.h"
extern void loopCounter();
void TIM4_init()
{
	TIM_TimeBaseInitTypeDef t;
	t.TIM_Prescaler = 83;
	t.TIM_Period = 999;
	t.TIM_CounterMode = TIM_CounterMode_Up;
	t.TIM_ClockDivision = 0;
	t.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM4, &t);

	TIM_Cmd(TIM4, ENABLE);

	TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE);

	NVIC_InitTypeDef n;
	n.NVIC_IRQChannel = TIM4_IRQn;
	n.NVIC_IRQChannelCmd = ENABLE;
	n.NVIC_IRQChannelPreemptionPriority = 7;
	n.NVIC_IRQChannelSubPriority = 0;
	NVIC_Init(&n);
}

void TIM3_init(int prescaler)
{
	TIM_TimeBaseInitTypeDef t;
	t.TIM_ClockDivision = 0;
	t.TIM_CounterMode = TIM_CounterMode_Up;
	t.TIM_Prescaler = prescaler*15;
	t.TIM_Period = 255;
	t.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM3, &t);
	TIM_ARRPreloadConfig(TIM3,ENABLE);
	
	TIM_Cmd(TIM3, ENABLE);

}

void TIM3_OC_init()
{
	GPIO_InitTypeDef g;
	g.GPIO_Mode = GPIO_Mode_AF;
	g.GPIO_OType = GPIO_OType_PP;
	g.GPIO_PuPd = GPIO_PuPd_NOPULL;
	g.GPIO_Speed = GPIO_Speed_100MHz;
	g.GPIO_Pin = GPIO_Pin_7 | GPIO_Pin_8;
	GPIO_Init(GPIOC, &g);

	GPIO_PinAFConfig(GPIOC, GPIO_PinSource7, GPIO_AF_TIM3);
	GPIO_PinAFConfig(GPIOC, GPIO_PinSource8, GPIO_AF_TIM3);



	TIM_OCInitTypeDef t;
	t.TIM_OCMode = TIM_OCMode_PWM1;
	t.TIM_OCIdleState = TIM_OCIdleState_Reset;
	t.TIM_OutputState = TIM_OutputState_Enable;
	t.TIM_OutputNState = TIM_OutputNState_Disable;
	t.TIM_OCPolarity = TIM_OCPolarity_High;
	t.TIM_Pulse = 0;


	TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);
	TIM_OC2Init(TIM3, &t); //left

	TIM_OC3PreloadConfig(TIM3, TIM_OCPreload_Enable);
	TIM_OC3Init(TIM3, &t);//right
}

void TIM4_init(int prescaler)
{
	TIM_TimeBaseInitTypeDef t;
	t.TIM_ClockDivision = 0;
	t.TIM_CounterMode = TIM_CounterMode_Up;
	t.TIM_Prescaler = prescaler * 10;
	t.TIM_Period = 255;
	t.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM3, &t);
	TIM_ARRPreloadConfig(TIM3, ENABLE);

	TIM_Cmd(TIM3, ENABLE);

}

void TIM5_OC_init()
{
	GPIO_InitTypeDef g;
	g.GPIO_Mode = GPIO_Mode_AF;
	g.GPIO_OType = GPIO_OType_PP;
	g.GPIO_PuPd = GPIO_PuPd_NOPULL;
	g.GPIO_Speed = GPIO_Speed_100MHz;
	g.GPIO_Pin = GPIO_Pin_7 | GPIO_Pin_8;
	GPIO_Init(GPIOC, &g);

	GPIO_PinAFConfig(GPIOC, GPIO_PinSource7, GPIO_AF_TIM3);
	GPIO_PinAFConfig(GPIOC, GPIO_PinSource8, GPIO_AF_TIM3);



	TIM_OCInitTypeDef t;
	t.TIM_OCMode = TIM_OCMode_PWM1;
	t.TIM_OCIdleState = TIM_OCIdleState_Reset;
	t.TIM_OutputState = TIM_OutputState_Enable;
	t.TIM_OutputNState = TIM_OutputNState_Disable;
	t.TIM_OCPolarity = TIM_OCPolarity_High;
	t.TIM_Pulse = 0;


	TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);
	TIM_OC2Init(TIM3, &t); //left

	TIM_OC3PreloadConfig(TIM3, TIM_OCPreload_Enable);
	TIM_OC3Init(TIM3, &t);//right
}

extern "C"
{
	void TIM4_IRQHandler(void)
	{
		if (TIM_GetITStatus(TIM4, TIM_IT_Update)!=RESET)
		{
			loopCounter();
			TIM4->SR = (uint16_t)~TIM_IT_Update;
		}
	}
}
