#ifndef __MAIN_MAP_H

#define __MAIN_MAP_H

#include "stm32f4xx.h"

#include "ExceptionFunction.h"
#include "map.h"


extern u8 flatSceneIdArray[];
extern u8 flatSceneIdArrayLen;
extern u8 vertialIdarray[];
extern u8 vertialSceneIdArrayLen;
extern u8 dumbNodeArray[];
extern u8 dumbNodeArrayLen;
extern u8 singleLineBridgeArray[];
extern u8 singleLineBridgeArrayLen;
extern u8 flatSceneToTreasure[];
extern u8 flatSceneToTreasureLen;
extern u8 doorArrayPos[];

extern u8 doorArrayLen;
extern bool stopRouteFlag;

extern u8 travelSceneArray[];

extern int Nodeid1;
extern int Nodeid2;

extern MapNode* nextNode;
extern ExceptionFunction_t exceptionFunction;
extern TrackFucntion_t trackfunction;
extern MapNode* currentNode;
extern int currentDirection;
extern int RouteIndex;

extern int Speed_High;
extern int Speed_Mid;
extern int Speed_Low;
extern int Speed_VeryHigh;

int getTreasurePos(int treasure);

void MAP_Init();

void MAP_getPathRoute(int nodeid1, int nodeid2);

void MAP_goRoute(int Nodeid1, int Nodeid2);


void MAP_goRoute(int Nodeid1, int Nodeid2);

void MAP_goRoute_Test();

void MAP_goPath(Path * path);

bool GetRapidFlag();

ExceptionFunction_t GetExceptionFunction(Path * p, MapNode * n);

int GetLineIndexToGo();





#endif // !__MAIN_MAP_H


