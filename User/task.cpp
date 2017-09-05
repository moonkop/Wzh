#include "preProcesser.h"
#include "main.h"
int Count_1ms;
int Count_2ms;
int Count_4ms;
int Count_20ms;
int Count_50ms;
int Count_1s;
u8 Task_check_flag;
extern u8 SEN2020Array[8];

extern int Track_Kp;
extern int Track_Kd;

extern int lfEncoderCount;
extern int rfEncoderCount;
extern int lfCurrentEncoderCount;
extern int rfCurrentEncoderCount;

void MainLoop()
{
 	if (Task_check_flag)
	{

		if (Count_1ms >= 1)
		{
			Count_1ms = 0;
			Task_1000HZ();
		}
		if (Count_2ms >= 2)
		{
			Count_2ms = 0;
			Task_500HZ();
		}
		if (Count_4ms >= 4)
		{
			Count_4ms = 0;
			Task_250HZ();
		}
		if (Count_20ms >= 20)
		{
			Count_20ms = 0;
			Task_50HZ();
		}
		if (Count_50ms >= 50)
		{
			Count_50ms = 0;
			Task_20HZ();
		}
		if (Count_1s >= 1000)
		{
			Count_1s = 0;
			Task_1HZ();
		}
		Task_check_flag = 0;
	}
}


void loopCounter()
{
	Count_1ms++;
	Count_2ms++;
	Count_4ms++;
	Count_20ms++;
	Count_1s++;
	Count_50ms++;

	Task_check_flag = 1;
	MainLoop();

}

void  Task_1000HZ(void)
{

}
extern bool TrackTestFlag;
void Task_500HZ(void)
{

}

void Task_250HZ(void)
{
}

void Task_50HZ(void)
{	

}

int i=0;

int pre = 83;
void Task_20HZ(void)
{
	motorBlockPrevent();
	getEncoderCount();
	//MPU_Update_Angle();
	//getMotorPitchOffset();
	beepCheck();
	KeyFitterClear();
	LCD_Show();
	WS2811_Update_Color();

}

void Task_1HZ(void)
{
	//getButtonIRdata();
	//getFrontIRData();
	
	USART_SendData(USART2, '*');
	//getEncoderCount();
}
