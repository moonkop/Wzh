#include "CameraFlash.h"

void CameraFlash_Init() {
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOG, ENABLE);
	GPIO_InitTypeDef a;
	a.GPIO_Mode = GPIO_Mode_OUT;
	a.GPIO_OType = GPIO_OType_PP;
	a.GPIO_Speed = GPIO_Speed_100MHz;
	a.GPIO_Pin = GPIO_Pin_4;
	GPIO_Init(GPIOG, &a);
	GPIO_SetBits(GPIOG, GPIO_Pin_4);
}

void FlashOn() {
	GPIO_ResetBits(GPIOG, GPIO_Pin_4);
}
void FlashOff() {
	GPIO_SetBits(GPIOG, GPIO_Pin_4);
}