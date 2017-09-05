#ifndef __MAP_H
#define __MAP_H
#include "mappath.h"
#include "mapNode.h"
#include "LCD_print.h"
#define LCD_printf LCD_printf
#define INT_MAX 2047483647
#define NULL 0

MapNode * SearchForNodeByID(int id);
Path * SearchForPathByID(int id);
void addNodeToAllnode(MapNode * node);
void addPahToAllPath(Path * path);

Path * CreatePathBetweenNode(int nodeID1, int nodeID2, int angle, int weight, int length, int speed=0);


int turnToDirection(int currentDirection, int targetDirection);
void PrintGoPath(Path * path, MapNode * currentNode);

int limit0360(int angle);

int getAngleBetweenPath(Path * path1, Path * path2);


bool getRouteByID(int startID, int targetID);

bool getRoute(MapNode * start, MapNode * target);

void convertRouteToPath();

void PrintGoRoute(int startNodeID, int targetNodeID);

void test();


extern Path *allPath[100];
extern int pathcount;
extern int pathAutoIncreaseID;

//===============CAR current 
extern MapNode* currentNode ;
extern int currentDirection ;
//===============CAR current 



extern MapNode *allNode[100];
extern int nodecount;


extern MapNode* nodeRoute[100];
extern int nodeRouteCount ;


extern Path* pathRoute[100];
extern int pathRouteCount ;


#endif
