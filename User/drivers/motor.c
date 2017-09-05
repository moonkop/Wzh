#include "motor.h"
#include "../devices/TIM.h"//"TIM.h"
#include "../preProcesser.h"//preProcesser.h"
#include "../LCD_driver/LCD_print.h"
#include "../common.h"
#include "../track.h"
#include "../devices/PhotoSwitch.h"
#include "../devices/WS2811.h"
extern int currentMotorRout;
extern int currentMotorLout;

int turnByAngle_Speed = 40;

int lfEncoderCount = 0;
int rfEncoderCount = 0;
int lbEncoderCount = 0;
int rbEncoderCount = 0;

int lfCurrentEncoderCount = 0;
int rfCurrentEncoderCount = 0;
int lbCurrentEncoderCount = 0;
int rbCurrentEncoderCount = 0;

extern int Encoder_rfpulse;
extern int Encoder_lfpulse;
extern int Encoder_rbpulse;
extern int Encoder_lbpulse;

int Test_Param_Turn_Angle = 180;
int TurnByPulsePremeterL = 460;
int TurnByPulsePremeterR = 494;

int aimAngle = 90;

#ifdef TRASURECAR

#endif // TRASURECAR

extern int motorNospeedCompensate;

int motorPitchOffset;
extern int straightSpeed;


void setSpeed(s16 left, s16 right)
{
	if (left == 0 && right == 0)
	{

	}
	else
	{
		//left += motorPitchOffset;
		//right += motorPitchOffset;
		left += motorNospeedCompensate;
		right += motorNospeedCompensate;
	}

	currentMotorLout = left;
	currentMotorRout = right;

	GPIO_ResetBits(GPIOG, GPIO_Pin_15);

	GPIO_ResetBits(GPIOA, GPIO_Pin_4);

	GPIO_ResetBits(GPIOC, GPIO_Pin_6);

	GPIO_ResetBits(GPIOD, GPIO_Pin_7);


	if (left > 0)
	{
		GPIO_SetBits(GPIOA, GPIO_Pin_4);
	}
	else
	{
		GPIO_SetBits(GPIOG, GPIO_Pin_15);
		left = -left;
	}
	if (right > 0)
	{
		GPIO_SetBits(GPIOD, GPIO_Pin_7);
	}
	else
	{
		GPIO_SetBits(GPIOC, GPIO_Pin_6);

		right = -right;
	}

	TIM_SetCompare2(TIM3, left);//根据寻迹算法设置速度
	TIM_SetCompare3(TIM3, right);
}


void motorTest()
{
	setSpeed(straightSpeed, straightSpeed);
}
void getEncoderCount()
{
	lfEncoderCount = lfCurrentEncoderCount;
	rfEncoderCount = rfCurrentEncoderCount;
	lbEncoderCount = lbCurrentEncoderCount;
	rbEncoderCount = rbCurrentEncoderCount;
	lfCurrentEncoderCount = 0;
	rfCurrentEncoderCount = 0;
	lbCurrentEncoderCount = 0;
	rbCurrentEncoderCount = 0;
}


extern int Encoder_rfpulse;
extern int Encoder_pulseOnFlag;


int turnByAngleFlag = 0;
int turnByAngleExtiFlag = 0;



int angleArray[20][2]
= {
	{0,0},
	{10,7},
	{20,10},
	{35,15},
	{55,21},
	{70,30},
	{80,33},
	{90,38},
	{145,55},
	{160,60},
	{180,70},
	{360,125}
};

int  getTurnTime(int angle) //return ms
{
	int bigTime;
	int smallTime;
	int bigAngle;
	int smallAngle;
	int res = 0;
	float k = 0;
	for (int i = 0; i < 11; i++)
	{
		smallTime = angleArray[i][1];
		smallAngle = angleArray[i][0];
		bigAngle = angleArray[i + 1][0];
		bigTime = angleArray[i + 1][1];
		if (angle < bigAngle)
		{
			break;
		}

	}

	res = (bigTime - smallTime) * 10 * (angle - smallAngle) / (bigAngle - smallAngle) + smallTime * 10;
	//LCD_printf("res=%d", res);

	return res;

}

int turnByAngleTest_Speed = 65;

void turnByAngleByTime(int angle)
{
	if (angle == 0)
		return;

	if (angle < 0)
	{
		setSpeed(turnByAngle_Speed, -turnByAngle_Speed);
		angle = -angle;

	}
	else
	{
		setSpeed(-turnByAngle_Speed, turnByAngle_Speed);
	}
	int time = getTurnTime(angle);
	delay_ms(time);
	setSpeed(0, 0);
}

void turnToOnLineTest()
{
	turnToOnLine(aimAngle, 0);
}


int turnToOnLine1(int angle, int switchIndex)
{
	int pul;
	Encoder_pulseOnFlag = 1;

	if (angle > 0)
	{
		pul = angle *TurnByPulsePremeterL / 100;
		setSpeed(-50, 50);
		turnByAnglePulseReset();
		while (Encoder_lbpulse < pul&&laserIsOnLine(switchIndex) == 1);
		if (laserIsOnLine(switchIndex) == 0)
		{
			setSpeed(0, 0);
			return 1;
		}
	}
	else
	{
		pul = -angle *TurnByPulsePremeterR / 100;
		setSpeed(50, -50);
		turnByAnglePulseReset();
		while (Encoder_rbpulse < pul&&laserIsOnLine(switchIndex) == 1);
		if (laserIsOnLine(switchIndex) == 0)
		{
			setSpeed(0, 0);
			return 1;
		}
	}
	setSpeed(0, 0);
	return 0;

}
int turnToOnLine(int angle, int switchIndex)
{
	int pul;
	Encoder_pulseOnFlag = 1;

	if (angle > 0)
	{
		pul = angle *TurnByPulsePremeterL / 100;
		setSpeed(-50, 50);
		turnByAnglePulseReset();
		while (Encoder_lbpulse < pul&&laserIsOnLine(switchIndex) == 0);
		if (laserIsOnLine(switchIndex) == 1)
		{
			setSpeed(0, 0);
			return 1;
		}
	}
	else
	{
		pul = -angle *TurnByPulsePremeterR / 100;
		setSpeed(50, -50);
		turnByAnglePulseReset();
		while (Encoder_rbpulse < pul&&laserIsOnLine(switchIndex) == 0);
		if (laserIsOnLine(switchIndex) == 1)
		{
			setSpeed(0, 0);
			return 1;
		}
	}
	setSpeed(0, 0);
	return 0;

}
void turnAngleWithException(int angle)
{

}
void turnAngleByPulse(int aA)
{
	setPixelColor(Color_purple);
	if (aA == 0)
		return;
	setSpeed(0, 0);
	delay_ms(300);
	int pul;
	Encoder_pulseOnFlag = 1;
	turnByAnglePulseReset();
	if (aA > 0)
	{
		pul = aA *TurnByPulsePremeterL / 100;
		setSpeed(-straightSpeed, straightSpeed);
		while (Encoder_lbpulse < pul);
	}
	else
	{
		pul = -aA *TurnByPulsePremeterR / 100;
		setSpeed(straightSpeed, -straightSpeed);
		while (Encoder_rbpulse < pul);
	}

	Encoder_pulseOnFlag = 0;
	turnByAnglePulseReset();
	setSpeed(0, 0);


}

bool goWithPulseCompleteFlag = 0;
int	gowithPulseLeftCount;

void Test_turnToOnLine()
{
	turnToOnLine(Test_Param_Turn_Angle, 1);
}
void Test_turnAngleByPulse()
{
	turnAngleByPulse(Test_Param_Turn_Angle);
}
void Test_turnByAngle()
{
	turnByAngleByTime(Test_Param_Turn_Angle);
}

/*

TIM3
//C6 tim3 ch1
C7 tim3 ch2 left
C8 tim3 ch3 right
//C9 tim3 ch4

G15 	L F
A4		L B

C6		R F
D7		R B


*/


void _motor_gpio_init(GPIO_TypeDef * GPIOx, int GPIO_Pin)
{

	GPIO_InitTypeDef g;

	g.GPIO_Mode = GPIO_Mode_OUT;
	g.GPIO_OType = GPIO_OType_PP;
	g.GPIO_Speed = GPIO_Speed_100MHz;
	g.GPIO_PuPd = GPIO_PuPd_DOWN;
	g.GPIO_Pin = GPIO_Pin;
	GPIO_Init(GPIOx, &g);
}

void motor_init()
{
	TIM3_init(200);
	_motor_gpio_init(GPIOG, GPIO_Pin_15); //LF

	_motor_gpio_init(GPIOA, GPIO_Pin_4);  //LB

	_motor_gpio_init(GPIOC, GPIO_Pin_6);  //RF

	_motor_gpio_init(GPIOD, GPIO_Pin_7);  //RB
}
