#ifndef __TREASURE_H
#define __TREASURE_H
#include "stm32f4xx.h"
extern bool beginTreasureFlag;
extern int nextTreasure;
extern int TreasureIndex[3];
extern int TreasureCount;
extern int treasurePos;
extern int treasureIndex;



void Treasure_Begin();

void Treasure_Main();

void  Treasure_Reset();

void Treasure_Write();

void Treasure_Write_Treasure_Index(int TreasurePos, int TreasureIndex);

void Treasure_Read_Treasure_Index();


#endif