#include "Treasure.h"
#include "main.h"
#include "mainmap.h"
bool beginTreasureFlag = 0;
int nextTreasure = 0;
int TreasureIndex[3] = { 0 };
int TreasureCount;
int treasurePos = 0;
int treasureIndex = 0;

void Treasure_Begin()
{
	beginTreasureFlag = 1;
}

void Treasure_Main()
{
	int next = 0;
	waitingForBegin();

	Treasure_Read_Treasure_Index();
	//nextTreasure = 5;
	if (TreasureIndex[0] > 10)
	{
		MAP_goRoute(1, 5);
	}

	for (int i = 0; i < 3; i++)
	{
		if (TreasureIndex[i] > 10)
		{
			next = getTreasurePos(nextTreasure);
			TreasureIndex[i] = nextTreasure;
			Treasure_Write_Treasure_Index(nextTreasure,i);

		}
		else
		{
			next = getTreasurePos(TreasureIndex[i]);
		}
		MAP_goRoute(currentNode->id, next);
	}
	MAP_goRoute(currentNode->id, 32);
	MAP_goRoute(currentNode->id, 1);
}

void  Treasure_Reset()
{
	FLASH_Clear(TREASURE_FIRST_ADDRESS);
}

void Treasure_Write() {
	Flash_Write_One_Data(treasureIndex, TREASURE_FIRST_ADDRESS, treasurePos);
}

// TreasurePos ±¶≤ÿŒª÷√
//Treasure Index ±¶≤ÿ–Ú∫≈
void Treasure_Write_Treasure_Index(int TreasurePos, int TreasureIndex)
{
	Flash_Write_One_Data(TreasurePos, TREASURE_FIRST_ADDRESS, TreasureIndex);
}

void Treasure_Read_Treasure_Index()
{
	for (int i = 0; i < 3; i++)
	{
		int value = FLASH_READ_ONEDATA(i, TREASURE_FIRST_ADDRESS);
		//if (value>10)
		//{
		//	value = 0;
		//}
		TreasureIndex[i] = value;
	}
}

int getTreasurePos(int treasure)
{
	if (treasure == 0 || treasure>8)
	{
		LCD_printf("treasure pos error aim = %d", treasure);
	}
	return flatSceneToTreasure[treasure - 1];
}
