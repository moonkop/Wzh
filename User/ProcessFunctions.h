
#ifndef __PROCESSFUNCTION_H
#define __PROCESSFUNCTION_H

#include "stm32f4xx.h"


extern int bridgeLeftSpeed;
extern int bridgeRightSpeed;
extern int bridgeAngle;

extern int ls ;
extern int rs;
void PF_Bridge();

void PF_seesaw();

void PF_seesawOnCircle();

void PF_normal_scene();

void PF_Flat_scene();

int AdjTillGetQrCode();

void PF_testIR();

void PF_SingleSideBridge();

void SetSpeed();

void testGodown();

void SetSpeed(int ls, int rs);

void TreasureCar();

void PF_Door();

void PF_CircleEnter();

void PF_Flat_450_scene();

void hit(int speed, int time);

#endif // !__PROCESSFUNCTION_H
