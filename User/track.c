#include "stm32f4xx.h"
#include "main.h"
#include "myMath.h"
#include "preProcesser.h"

int difSpeedLength = 100;
int difLeftSpeed = 60;
int difRightSpeed = 60;

int bridgeSpeed = 60;

int Kd = 4;
int Kp = 2;

int D_Out_Period=500;

int pido;
u8 linecount = 0;
u8 lightCount = 0;
int  lines[8];
int lineWidth[8];
u8*	sensers = 0;


int currentSpeed = 0;
int straightSpeed = 70;

int Track_Kd = 4;
int Track_Kp = 2;
int Track_kkp = 40;
int Track_kkd = 80;
int Track_Last_Offset = 0;
int Track_PidCount = 0;
int Track_Dout = 0;

int Bridge_kp = 2;
int Bridge_kd = 4;
int Bridge_Last_Offset = 0;
int Bridge_Dout = 0;
int Bridge_PidCount = 0;


int Encoder_rfpulse = 0;//外部中断产生脉冲
int Encoder_lfpulse = 0;
int Encoder_rbpulse = 0;
int Encoder_lbpulse = 0;
int Encoder_pulseOnFlag = 0;

int speedCompensate = 20;
int currentMotorRout = 0;
int currentMotorLout = 0;


int motorNospeedCompensate = 0;//motor compensate
int compensateFlag = 0;//motorNospeedCompensate plus flag or minus to 0
u8 lineWitdh[8] = { 0 };

int lineindex = 0;
int Test_Param_turnByAngle_angle = 50;
int Test_Param_Go_length=100;//goWithPulse目标距离（cm）


extern int lfEncoderCount;
extern int rfEncoderCount;
extern int lfCurrentEncoderCount;
extern int rfCurrentEncoderCount;

 void turnByAnglePulseReset() {
 	Encoder_rfpulse = 0;//外部中断产生脉冲
	Encoder_lfpulse = 0;
	Encoder_rbpulse = 0;
	Encoder_lbpulse = 0;
}
//be used in the mainloop
void motorBlockPrevent()
{
	if (currentMotorLout == 0 && currentMotorRout == 0)
	{
		motorNospeedCompensate = 0;
		return;

	}
	if (rfEncoderCount < 20)
	{
		int kp = 3;

		int E = 20 - rfEncoderCount;
		motorNospeedCompensate = E*kp;



	}
	else
	{
		motorNospeedCompensate /= 2;

	}

}
void getLines(u8* sensers)
{

	linecount = 0;			//lines under the senser
	lightCount = 0;			//lights off count
	u8 currentLineCount = 0; //current sensers count actived by line
	u8 currentLineSum = 0;	//current sensers Number sum 
	u8 lineFlag = 0;				// current itearter is under the line 
									//	ConvertToArray(); //Convert senser data to senser[8] array

	for (int i = 0; i < 8; i++)
	{
		if (lineFlag == 1)
		{
			if (sensers[i] == 0)
			{
				lines[linecount] = currentLineSum * 10 / currentLineCount;
				lineWidth[linecount] = currentLineCount;
				linecount++;
				currentLineCount = 0;
				currentLineSum = 0;
				lineFlag = 0;
			}
			else if (sensers[i] == 1)
			{
				currentLineCount++;
				lightCount++;
				currentLineSum += i;
			}
		}
		else if (lineFlag == 0)
		{
			if (sensers[i] == 0)
			{
				continue;
			}
			else if (sensers[i] == 1)
			{
				lineFlag = 1;
				lightCount++;
				currentLineCount++;
				currentLineSum += i;
			}
		}
	}


	if (lineFlag == 1)
	{
		lines[linecount] = currentLineSum * 10 / currentLineCount;
		lineWidth[linecount] = currentLineCount;
		linecount++;

		currentLineCount = 0;
		currentLineSum = 0;
		lineFlag = 0;
	}
}

int getoffset_Index(int lineIndex)
{
	if (linecount == 0)
	{
		return 0;
	}
	if (linecount > lineIndex)
	{
		return lines[lineIndex] - 35;
	}
	if (linecount <= lineIndex)
	{
		return getoffset_mid(0);
	}
	return lines[0] - 35;
}
int getoffset_mid(int)
{
	if (linecount == 0)
	{
		return 0;
	}
	int minOffset = 255;
	int minindex = 0;
	for (int i = 0; i < linecount; i++)
	{
		int currentOffset = abs(lines[i] - 35);
		if (minOffset > currentOffset)
		{
			minOffset = currentOffset;
			minindex = i;
		}
	}
	return lines[minindex] - 35;

}
int getoffset_WidthLimit(int width)
{
	if (linecount == 0)
	{
		return 0;
	}
	int minOffset = lines[0] - 35;
	int minindex = 0;
	for (int i = 0; i < linecount; i++)
	{
		if (minOffset > lines[i] - 35)
		{
			minOffset = lines[i] - 35;
			minindex = i;
		}
	}
	if (lineWidth[minindex] > width)
	{
		return 0;
	}
	return minOffset;
}
typedef int(*offsetFunction)(int);
int getPIDout(int offset)
{
	getDynamicPIDOut(offset, currentSpeed);
}

int getStaticPIDout(int offset)
{
	int PID_out = 0;
	int P_Out = 0;

	P_Out = Track_Kp*offset;
	PID_out += P_Out;
	if (Track_PidCount++ > D_Out_Period)
	{
		Track_PidCount = 0;
		int d = 0;
		d = offset - Track_Last_Offset;
		Track_Last_Offset = offset;
		Track_Dout = Track_Kd*d;
	}
	PID_out += Track_Dout;
	return PID_out;
}

int getDynamicPIDOut(int offset,int speed)
{
	int PID_out = 0;
	int P_Out = 0;
	int kp;
	int kd;
	if (speed < 40)
	{
		kp = 2;
		kd = 4;
	}
	else
	{
		kp = speed*Track_kkp / 1000;
		kd = speed*Track_kkd / 1000;
	}

	P_Out = kp*offset;
	PID_out += P_Out;
	if (Track_PidCount++ > 500)
	{
		Track_PidCount = 0;
		int d = 0;
		d = offset - Track_Last_Offset;
		Track_Last_Offset = offset;
		Track_Dout = kd*d;
	}
	PID_out += Track_Dout;
	return PID_out;
}
int getDynamicPidByEncoder(int offset,int EncoderSpeed)
{

}
#define NoLineAction_Continues 0
#define NoLineAction_Straight 1
void getToLine(offsetFunction offsetfun, int index, int widthLimit, int NoLineAction)
{
	if (currentSpeed == 0)
	{
		currentSpeed = straightSpeed;
	}

	int offset;
	if (!offsetfun)
	{
		offsetfun = getoffset_mid;
	}
	if (widthLimit == 0)
	{
		widthLimit = 3;
		offset = offsetfun(index);
	}
	else
	{
		offset = offsetfun(widthLimit);
	}
	//float kslow = currentSpeed*1.0 / 35;
	int PID_OUT = getPIDout(offset);
	int kslowOut = abs((int)(offset*currentSpeed / 35));

	switch (NoLineAction)
	{
	case NoLineAction_Continues:

		break;
	case NoLineAction_Straight:
		setSpeed(currentSpeed, currentSpeed);
		break;
	}
	TrackSpeedOut(kslowOut, PID_OUT);
}
void getToLine_WidthLimit(int width)
{
	getToLine(getoffset_WidthLimit, 0, width, NoLineAction_Continues);
}
void getToLine_std(int)   //revise to line 
{
	getToLine(getoffset_WidthLimit, 0, 2, NoLineAction_Straight);
}
void getToLine_Mixed(int)   //revise to line 
{
	getToLine(getoffset_mid, 0, 0, NoLineAction_Straight);
}
void getToLine_Index(int index)
{
	getToLine(getoffset_Index, index, 0, NoLineAction_Straight);
}

void TrackSpeedOut(int kslowOut, int PID_OUT)
{

	int lspeed = currentSpeed - PID_OUT - kslowOut;
	int rspeed = currentSpeed + PID_OUT - kslowOut;
	setSpeed(lspeed, rspeed);
}
void track_on_bridge()
{
	delay_ms(1);
	pido = 0;
	int bridgeOffset = IR_button_right - IR_button_left;
	if (Bridge_PidCount++ > 10)
	{
		Bridge_PidCount = 0;
		Bridge_Dout = (bridgeOffset - Bridge_Last_Offset)*Bridge_kd/100;
		Bridge_Last_Offset = bridgeOffset;
	}

	int com = bridgeOffset *Bridge_kp / 100;
	setSpeed(bridgeSpeed - pido - com- Bridge_Dout, bridgeSpeed + com + pido+ Bridge_Dout);
}

void trackToLine(int cm ,int lineindex)
{
	setPixelColor(Color_green);

	int pul = cm * 1633 / 100;
	turnByAnglePulseReset();
	Encoder_pulseOnFlag = 1;
	while (Encoder_rfpulse < pul)
	{
		getSEN2020DigitalData();
		getLines(SEN2020Array);
		getToLine_Index(lineindex);
	}
	//setSpeed(0, 0);
	Encoder_pulseOnFlag = 0;
	setPixelColor(Color_white);

}

void TrackNoExceptionForLength(int cm, int speed)
{
	setPixelColor(Color_cyan);
	if (speed == 0)
	{
		speed = 60;
	}
	currentSpeed = speed;
	int pul = cm * 1633 / 100;
	turnByAnglePulseReset();
	Encoder_pulseOnFlag = 1;
	while (Encoder_rfpulse < pul)
	{
		getSEN2020DigitalData();
		getLines(SEN2020Array);
		getToLine_Mixed(0);
	}
	setSpeed(0, 0);
	Encoder_pulseOnFlag = 0;
	setPixelColor(Color_white);

}
bool TrackTestFlag = 0;
void goWithPulse(int  dis, u8 dir)
{
	setPixelColor(Color_red);
	int pul = dis * 1633 / 100;
	turnByAnglePulseReset();
	Encoder_pulseOnFlag = 1;
	if (dir == FORWORD)
		setSpeed(straightSpeed, straightSpeed);
	else
	{
		setSpeed(straightSpeed, straightSpeed);
	}
	while (Encoder_rfpulse < pul);
	//setSpeed(0, 0);

	Encoder_pulseOnFlag = 0;
	setPixelColor(Color_white);
}
void goWithPulseWithDifSpeedByLbCoderTest() 
{
	goWithPulseWithDifSpeedByLbCoder(difLeftSpeed,difRightSpeed,difSpeedLength);
	
}
void goWithPulseWithDifSpeedByLbCoder(int ls, int rs, int dis)
{
	int pul = dis * 1633 / 100;
	turnByAnglePulseReset();
	Encoder_pulseOnFlag = 1; 
	setSpeed(ls, rs);
	LCD_printf("goWithPulseWithDifSpeedByLbCoder\n");
	while (Encoder_lbpulse < pul);
	setSpeed(0, 0);
	Encoder_pulseOnFlag = 0;
}
void turnRadiusTillLine(int left, int right)
{
	FillFitter(0, 0);
	while (linecountAfterFitter() == 0)
	{
		getSEN2020DigitalData();
		getLines(0);
		setSpeed(left, right);

	}
	//setSpeed(0, 0);
}
void goStraightTillLine(int speed)
{
	FillFitter(0, 0);
	while (linecountAfterFitter() == 0)
	{
		getSEN2020DigitalData();
		getLines(0);
		setSpeed(speed, speed);
	}
	setSpeed(0, 0);
}
void AdjToLineByLaser()
{
	int tempturnangle = 5;
	while (!turnToOnLine(tempturnangle, 1))
	{
		if (tempturnangle == 0)
			break;
		if (tempturnangle > 0)
		{
			tempturnangle = -tempturnangle - 5;
		}
		else
		{
			tempturnangle = -tempturnangle + 5;
		}
	}
}





int linecountAfterFitter()
{
	return Moving_Median_int(linecount, 0);

}


void Test_TrackNoExceptionForLength()
{
	TrackNoExceptionForLength(Test_Param_Go_length, currentSpeed);
}
void Test_goWithPulse()
{
	goWithPulse(Test_Param_Go_length, FORWORD);
}
void Test_Track()
{
	while (1)
	{
		getSEN2020DigitalData();
		getLines(SEN2020Array);
		getToLine_std(0);
	}
}
