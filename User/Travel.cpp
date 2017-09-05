#include "Travel.h"	
#include "main.h"
#include "mainmap.h"

int PausedBydoorFlag = 0;
u8 beginTravelFlag = 0;
int doorStatus[4];
int doorIndex;
int status;

void Travel_Begin()
{
	beginTravelFlag = 1;
}
void Travel_Init()
{
	Travel_Read_Door_Status();
	LCD_Show_Structure_Typedef* TravelDebug = LCD_DEBUG_Node_Add("TravelDebug", 10, NULL);

	for (int i = 0; i < 4; i++)
	{
		int doorPos = getDoorPos(i);
		LCD_DEBUG_Premeter_Add(&(allNode[doorPos]->paths[0]->weight), "D0", ACCESS_LVL_READ, TravelDebug);
		LCD_DEBUG_Premeter_Add(&(allNode[doorPos]->paths[1]->weight), "D1", ACCESS_LVL_READ, TravelDebug);

		allNode[doorPos]->paths[0]->weight = 0;
		allNode[doorPos]->paths[0]->weight = 0;
		if (doorStatus[i] == DOOR_STATUS_OPEN)
		{
			allNode[doorPos]->paths[0]->weight = 0;
			allNode[doorPos]->paths[1]->weight = 0;
			allNode[doorPos]->processFunction = NULL;
			
		}
		else if (doorStatus[i] == DOOR_STATUS_CLOSED)
		{
			allNode[doorPos]->paths[0]->weight = 100;
			allNode[doorPos]->paths[1]->weight = 100;
		}
		else if(doorStatus[i]==DOOR_STATUS_UNKNOWN)
		{
			allNode[doorPos]->paths[0]->weight = 30;
			allNode[doorPos]->paths[1]->weight = 30;
		}
		else
		{
			printf("door status error %d",i);
		}
	}
}

void Travel_Main()
{
	Travel_Init();

	waitingForBegin();

	//int targetArray[] = { 5,7,13,11,12,34,51,41,32,1 };
	int targetArray[] = { 41,51,1 };
	int targetArrayLen = 3;
	int currentTarget = 0;
	int currentNodeId = 1;
	currentNode = SearchForNodeByID(currentNodeId);

	for (int i = 0; i < targetArrayLen; i++)
	{
		PausedBydoorFlag = 1;
		while (PausedBydoorFlag == true)
		{
			PausedBydoorFlag = false;
			MAP_goRoute(currentNode->id, targetArray[i]);
		}
	}
	setSpeed(0, 0);

}

void Travel_Test()
{
	Travel_Init();

	waitingForBegin();

	int targetArray[] = { 9,26,24,8 };
	int targetArrayLen = 4;
	int currentNodeId = 9;
	currentNode = SearchForNodeByID(currentNodeId);
	currentDirection = -90;
	for (int i = 0; i < targetArrayLen; i++)
	{
		PausedBydoorFlag = 1;
		while (PausedBydoorFlag == true)
		{
			PausedBydoorFlag = false;
			MAP_goRoute(currentNode->id, targetArray[i]);
		}
	}
	setSpeed(0, 0);

}

void Travel_Reset()
{
	FLASH_Clear(TRAVEL_FIRST_ADDRESS);
}
void Travel_Write_Door_Status()
{
	Travel_Write_Door_Status(doorIndex, status);
}
void Travel_Write_Door_Status(int doorIndex, int status)
{
	
	Flash_Write_One_Data(status, TRAVEL_FIRST_ADDRESS, doorIndex);
	doorStatus[doorIndex] = status;

}
void Travel_Read_Door_Status()
{
	int value;
	for (int i = 0; i < 4; i++)
	{
		value = FLASH_READ_ONEDATA(i, TRAVEL_FIRST_ADDRESS);
		if (value > 2||value <0)
		{
			value = 0;
		}
		doorStatus[i] = value;
	}
}
int getDoorPos(int doorIndex)
{
	if (doorIndex > 3)
	{
		printf("getDoorArrayPos error");
		while (1)
		{
			;
		}
	}
	return doorArrayPos[doorIndex];

}
int getDoorId(int pos)
{
	for (int i = 0; i < 4; i++)
	{
		if (doorArrayPos[i]==pos)
		{
			return i;
		}
	}
	printf("door pos error");
	while (1)
	{
		;
	}
	return 100;
}