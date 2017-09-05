#ifndef __PHOTOSWITCH_H
#define __PHOTOSWITCH_H
#include "../../Driver/stm32f4xx.h"

extern int PhotoSwitchData;

extern int LaserFrontIsOnline;
extern int LaserLeftIsOnline;


void PhotoSwitchInit();

int laserIsOnLine(int switchIndex);

int getFrontPhotoSwitchData();

bool Laser_FrontIsOnLine();

bool Laser_LeftIsOnLine();

void		Laser_Check();

#endif