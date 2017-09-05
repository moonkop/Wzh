
#include "Beep.h"
#include "../../Driver/stm32f4xx.h"
int beepTime = 0;
void Beep_init()
{
	GPIO_InitTypeDef g;
	g.GPIO_Mode = GPIO_Mode_OUT;
	g.GPIO_OType = GPIO_OType_PP;
	g.GPIO_Pin = GPIO_Pin_7;
	g.GPIO_PuPd = GPIO_PuPd_DOWN;

	g.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(GPIOG, &g);
}

void BeepOn()
{
	GPIO_SetBits(GPIOG, GPIO_Pin_7);
}
void BeepOff()
{
	GPIO_ResetBits(GPIOG, GPIO_Pin_7);
}
void beepCheck()
{
	if (beepTime)
	{
		beepTime--;
	}
	else
	{
		BeepOff();

	}
}
void beepWaiting(int time)
{
	time /= 50;

	beepTime = time;
	BeepOn();
}