#include "maincpp.h"

//#define WO_YAO_ZHUANG_BI




void waitingForBegin()
{
	Action_ShakeHead();
	FillFitter(1000, 1);

	while (getFrontIRData() > 200)
	{
		;
	}
}

int main(void)
{
	RCC_init();
	CameraFlash_Init();
	delay_init();
	USART1_init();
	USART2_init();
	Beep_init();
	PhotoSwitchInit();
	LCD_Init();
	LCD_Print_init();
	LCD_Show_Init();
	KEY_IT_init();
	TIM4_init();
	TIM3_OC_init();
	SEN2020_init();
	LED_init();
	LED_SET(2, 1);
	motor_init();
	ADC1_Init();
	ADC3_init();
	USART3_init();
	motorEncoder_init();
	MAP_Init();
	Click_Switch_Init();

	LCD_printf("Initialize finished\n");
	LCD_printf("\n\n\n\n\n\n");
	LED_SPI_LowLevel_Init();
	setSpeed(0, 0);

	while (beginTravelFlag == 0 && beginTreasureFlag == 0)
	{
		;
	}
	if (beginTravelFlag)
	{
		Travel_Main();
	}
	else
	{
		Treasure_Main();
	}
#ifdef TREASURE

#endif

#ifdef TRAVELCAR

#endif

	while (1)
	{

	}
}
