#include "PhotoSwitch.h"
#include "Beep.h"
int PhotoSwitchData=0;
int LaserFrontIsOnline=0;
int LaserLeftIsOnline=0;



void PhotoSwitchInit() 
{
	GPIO_InitTypeDef a;
	a.GPIO_Mode = GPIO_Mode_IN;
	a.GPIO_PuPd = GPIO_PuPd_UP;
	a.GPIO_Speed = GPIO_Speed_100MHz;
	a.GPIO_Pin = GPIO_Pin_0;
	GPIO_Init(GPIOB, &a);
	a.GPIO_Pin = GPIO_Pin_4|GPIO_Pin_5;
	GPIO_Init(GPIOC, &a);
	a.GPIO_Pin = GPIO_Pin_12| GPIO_Pin_13;
	GPIO_Init(GPIOD, &a);
}

//0 is Forward_left
//1 is ForWard_mid
int laserIsOnLine(int switchIndex) 
{
	switch (switchIndex)
	{
	case 0: 
		return  Laser_LeftIsOnLine();
		break;
	case 1:
		return Laser_FrontIsOnLine();
		break;
	}
}

bool Laser_FrontIsOnLine()
{
	return LaserFrontIsOnline=!GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_0);
}
bool Laser_LeftIsOnLine()
{
	return LaserLeftIsOnline=!GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_13);
}
void Laser_Check() 
{
	LaserFrontIsOnline=Laser_FrontIsOnLine();
	LaserLeftIsOnline=Laser_LeftIsOnLine();
}