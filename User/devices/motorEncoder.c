#include "../main.h"
#include "../preProcesser.h"

extern int lfEncoderCount;
extern int rfEncoderCount;
extern int lfCurrentEncoderCount;
extern int rfCurrentEncoderCount;
extern int lbCurrentEncoderCount;
extern int rbCurrentEncoderCount;
extern int Encoder_rfpulse;
extern int Encoder_lfpulse;
extern int Encoder_rbpulse;
extern int Encoder_lbpulse;
extern int Encoder_pulseOnFlag;


void motorEncoder_init()
{
	GPIO_InitTypeDef g;
	g.GPIO_Mode = GPIO_Mode_IN;
	g.GPIO_OType = GPIO_OType_PP;
	g.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14;
	g.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOF, &g);

	g.GPIO_Pin = GPIO_Pin_15;
	GPIO_Init(GPIOE, &g);

	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOF, EXTI_PinSource12);
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOF, EXTI_PinSource13);
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOF, EXTI_PinSource14);
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE, EXTI_PinSource15);

	EXTI_InitTypeDef e;
	e.EXTI_Line = EXTI_Line12 | EXTI_Line13 | EXTI_Line14 | EXTI_Line15;
	e.EXTI_LineCmd = ENABLE;
	e.EXTI_Mode = EXTI_Mode_Interrupt;
	e.EXTI_Trigger = EXTI_Trigger_Falling;
	EXTI_Init(&e);

	NVIC_InitTypeDef n;
	n.NVIC_IRQChannel = EXTI15_10_IRQn;
	n.NVIC_IRQChannelCmd = ENABLE;
	n.NVIC_IRQChannelPreemptionPriority = 1;
	n.NVIC_IRQChannelSubPriority = 0;

	NVIC_Init(&n);
}

int * leftCounters[10] = {0};
u8 leftCounterNum = 0;
int * rightCounters[10] = {0};
u8 rightCounterNum = 0;

void attachCounterToEncoder(int * leftCounter,int * rightCounter)
{
	if (leftCounter)
	{
		leftCounters[leftCounterNum++] = leftCounter;
	}
	if (rightCounter)
	{
		rightCounters[rightCounterNum++] = rightCounter;
	}
}

void deattchCounterFromEncoder(int * leftCounter,int * rightCounter)
{
	if (leftCounter)
	{
		deleteLeftCounter(leftCounter);
	}
	if (rightCounter)
	{
		deleteRightCounter(rightCounter);
	}
}

void deleteLeftCounter(int * counter)
{
	for (int i = 0; i < leftCounterNum; i++)
	{
		if (leftCounters[i]==counter)
		{
			leftCounters[i] = NULL;
			leftCounters[i] = leftCounters[leftCounterNum - 1];
			leftCounterNum--;

		}	
	}
}
void deleteRightCounter(int * counter)
{
	for (int i = 0; i < rightCounterNum; i++)
	{
		if (rightCounters[i] == counter)
		{
			rightCounters[i] = NULL;
			rightCounters[i] = rightCounters[rightCounterNum - 1];
			rightCounterNum--;

		}
	}
}

void RightEncoderHandler(int num)
{
	for (int i = 0; i < rightCounterNum; i++)
	{
		rightCounters[i] += num;
	}
}
void LeftEncoderHandler(int num)
{
	for (int i = 0; i < leftCounterNum; i++)
	{
		leftCounters[i] += num;
	}
}



#ifdef __cplusplus
extern "C"
{

#endif // __cplusplus

void EXTI15_10_IRQHandler(void)
	{
		if (EXTI_GetITStatus(EXTI_Line12) != RESET)
		{
			EXTI_ClearITPendingBit(EXTI_Line12);
			lfCurrentEncoderCount++;
			LeftEncoderHandler(1);
			if (Encoder_pulseOnFlag == 1)
				Encoder_lfpulse++;
		}
		if (EXTI_GetITStatus(EXTI_Line13) != RESET)
		{
			EXTI_ClearITPendingBit(EXTI_Line13);
			rfCurrentEncoderCount++;
			if(Encoder_pulseOnFlag)
				Encoder_rfpulse++;
			RightEncoderHandler(1);
		}
		if (EXTI_GetITStatus(EXTI_Line14) != RESET)
		{
			EXTI_ClearITPendingBit(EXTI_Line14);
			lbCurrentEncoderCount++;
			if (Encoder_pulseOnFlag)
				Encoder_lbpulse++;
		}
		if (EXTI_GetITStatus(EXTI_Line15) != RESET)
		{
			EXTI_ClearITPendingBit(EXTI_Line15);
			rbCurrentEncoderCount++;
			if (Encoder_pulseOnFlag)
				Encoder_rbpulse++;
		}

	}

#ifdef __cplusplus
}

#endif // __cplusplus

