#ifndef __MOTOR_H
#define __MOTOR_H

#define FORWORD 0x01
#define BACKWORD 0x02
#define LEFT 0x03
#define RIGHT 0x04

#include "../../Driver/stm32f4xx.h"

extern int Test_Param_Turn_Angle;
extern int turnByAngleFlag;
extern int aimAngle;



void setSpeed(s16 left, s16 right);
void motorTest();
void getEncoderCount();
void turnByAngle(int angle);
void motor_init();
int getTurnTime(int angle);

void turnAngleByPulse(int aA);
void turnByAngleByTime(int angle);

int turnToOnLine1(int angle, int switchIndex);
int turnToOnLine(int angle, int switchIndex);


void Test_turnToOnLine();
void Test_turnAngleByPulse();
void Test_turnByAngle();
#endif // !__MOTOR_H

