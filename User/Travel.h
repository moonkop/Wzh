#ifndef __TRAVEL_H
#define __TRAVEL_H
#include "stm32f4xx.h"

extern int PausedBydoorFlag;
extern u8 beginTravelFlag;
extern int doorStatus[4];
extern int doorIndex;
extern int status;


#define DOOR_STATUS_OPEN 1
#define DOOR_STATUS_CLOSED 2
#define DOOR_STATUS_UNKNOWN 0

void Travel_Write_Door_Status();

void Travel_Write_Door_Status(int doorIndex, int status);

void Travel_Read_Door_Status();

int getDoorPos(int doorIndex);

int getDoorId(int pos);

void  Travel_Reset();

void Travel_Begin();

void Travel_Init();

void Travel_Main();
void Travel_Test();
#endif
