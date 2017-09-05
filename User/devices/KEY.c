
#include "KEY.h"	
#include "track.h"
#include "LCD_show.h"
#include "preProcesser.h"
#include "USART.h"
extern int turnByAngleFlag;
extern int straightSpeed;
extern int Track_Kd;
extern int Track_Kp;

int Click_Is_Down = 0;

void KEY_IT_init()
{
	GPIO_InitTypeDef  g;

	g.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9; //KEY0 KEY1 KEY2 KEY3对应引脚
	g.GPIO_Mode = GPIO_Mode_IN;             //普通输入模式
	g.GPIO_Speed = GPIO_Speed_100MHz;       //100M
	g.GPIO_PuPd = GPIO_PuPd_UP;             //上拉
	GPIO_Init(GPIOF, &g);

	EXTI_InitTypeDef e;
	e.EXTI_Line = EXTI_Line6 | EXTI_Line7 | EXTI_Line8 | EXTI_Line9;
	e.EXTI_LineCmd = ENABLE;
	e.EXTI_Mode = EXTI_Mode_Interrupt;
	e.EXTI_Trigger = EXTI_Trigger_Falling;

	EXTI_Init(&e);

	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOF, EXTI_PinSource6);
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOF, EXTI_PinSource7);
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOF, EXTI_PinSource8);
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOF, EXTI_PinSource9);

	NVIC_InitTypeDef n;
	n.NVIC_IRQChannel = EXTI9_5_IRQn;
	n.NVIC_IRQChannelCmd = ENABLE;
	n.NVIC_IRQChannelPreemptionPriority = 8;
	n.NVIC_IRQChannelSubPriority = 0;
	NVIC_Init(&n);
}


u8 KeyFitterFlag = 0;

u8 KeyFitter()
{
	if (KeyFitterFlag)
	{
		return 0;
	}
	else
	{
		KeyFitterFlag = 1;
		return 1;
	}
}
void KeyFitterClear()
{
	KeyFitterFlag = 0;
}


void Click_Switch_Init()
{
	GPIO_InitTypeDef g;
	g.GPIO_Mode = GPIO_Mode_IN;
	g.GPIO_OType = GPIO_OType_PP;
	g.GPIO_PuPd = GPIO_PuPd_UP;
	g.GPIO_Pin = GPIO_Pin_13;
	g.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(GPIOC, &g);
}
u8 Click_Triggered()
{
	return !GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_13);
}
void Test_getClick_TriggeredData() {
	Click_Is_Down = Click_Triggered();
}




#ifdef __cplusplus
extern "C"
{

#endif // __cplusplus




	void EXTI9_5_IRQHandler(void)
	{
		if (EXTI_GetITStatus(EXTI_Line6) != RESET)//3   右
		{
			EXTI_ClearITPendingBit(EXTI_Line6);
			if (KeyFitter())
			{
				_LCD_DEBUG_KEY_LEFT();
			}
			EXTI_ClearITPendingBit(EXTI_Line6);
		}
		else if (EXTI_GetITStatus(EXTI_Line7) != RESET)//2  下
		{
			EXTI_ClearITPendingBit(EXTI_Line7);
			if (KeyFitter())
			{
				_LCD_DEBUG_KEY_DOWN();
			}
			EXTI_ClearITPendingBit(EXTI_Line7);

		}
		else if (EXTI_GetITStatus(EXTI_Line8) != RESET)//1  左
		{
			EXTI_ClearITPendingBit(EXTI_Line8);
			if (KeyFitter())
			{
				_LCD_DEBUG_KEY_RIGHT();
			}
			u8 data = 1;
			USART_SendData(USART2, data);
			EXTI_ClearITPendingBit(EXTI_Line8);
		}
		else if (EXTI_GetITStatus(EXTI_Line9) != RESET)//0  上
		{
			EXTI_ClearITPendingBit(EXTI_Line9);
			if (KeyFitter())
			{
				_LCD_DEBUG_KEY_UP();
			}
			EXTI_ClearITPendingBit(EXTI_Line9);

		}

	}



#ifdef __cplusplus
	}

#endif // __cplusplus

