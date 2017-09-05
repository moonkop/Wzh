#ifndef __TRACK_H
#define __TRACK_H

#include "../Driver/stm32f4xx.h"

extern int currentSpeed;
extern int straightSpeed;

extern int Track_Kd;
extern int Track_Kp;
extern int Track_kkp;
extern int Track_kkd;

extern int Bridge_kp;
extern int Bridge_kd;

extern int bridgeSpeed;

extern int D_Out_Period;

extern u8 lightCount;

extern int Encoder_rfpulse;//外部中断产生脉冲
extern int Encoder_lfpulse;
extern int Encoder_rbpulse;
extern int Encoder_lbpulse;
extern int Encoder_pulseOnFlag;//外部中断使能
extern int Test_Param_Go_length;//goWithPulse目标距离（cm）

extern int widthMinus;
extern int pido;


extern int currentMotorRout;
extern int currentMotorLout ;
extern u8 linecount;

extern int difSpeedLength;
extern int difLeftSpeed;
extern int difRightSpeed;

void getLines(u8* sensers);
void turnByAnglePulseReset();



int getoffset_Index(int lineIndex);

int getoffset_mid(int);

int getPIDout(int offset);

int getStaticPIDout(int offset);

int getDynamicPIDOut(int offset, int speed);

void goWithPulseWithDifSpeedByLbCoderTest();

void goWithPulseWithDifSpeedByLbCoder(int ls, int rs, int dis);

void getToLine_std(int);

void getToLine_Mixed(int);

void getToLine_Index(int index);




void TrackSpeedOut(int kslowOut, int PID_OUT);

void track_on_bridge();

void trackToLine(int cm, int lineindex);

void TrackNoExceptionForLength(int cm, int lineIndex);

void AdjToLineByLaser();

void Test_Track();


void goWithPulse(int dis,u8 dir);
void getToLine_IndexTest();
void Test_goWithPulse();

int linecountAfterFitter();

void turnRadiusTillLine(int left, int right);

void goStraightTillLine(int speed);

void motorBlockPrevent();
void Test_TrackNoExceptionForLength();
#endif // !__TRACK_H
