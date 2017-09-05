#pragma once
#define TREASURE
#define _CRT_SECURE_NO_WARNINGS
#include "path.h"
#include "mapNode.h"
#include<iostream>	
MapNode * SearchForNodeByID(int id);
Path * SearchForPathByID(int id);
void addNodeToAllnode(MapNode * node);
void addPahToAllPath(Path * path);
Path * CreatePathBetweenNode(int nodeID1, int nodeID2, int angle, int weight, char * name);
Path * CreatePathBetweenNode(int nodeID1, int nodeID2, int angle, char * name);
int turnToDirection(int currentDirection, int targetDirection);
void goPath(Path * path, MapNode * currentNode);

int limit0360(int angle);

int getWeightBetweenNode(MapNode * node1, MapNode * node2);

bool getRouteByID(int startID, int targetID);

bool getRoute(MapNode * start, MapNode * target);


extern Path *allPath[100];
extern int pathcount;
extern int pathAutoIncreaseID;



extern MapNode *allNode[100];
extern int nodecount;