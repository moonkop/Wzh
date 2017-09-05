#ifndef __MAPNODE_H
#define __MAPNODE_H

#include "map.h"
class Path;
typedef bool (*ExceptionFunction_t)();
typedef void(*ProcessFunction_t)();
class MapNode
{
public:
	int id;
	int pathCount;
	int _dis;
	MapNode * _prevNode;
	Path* paths[8];
	char  name[10];
	ProcessFunction_t processFunction;
	ExceptionFunction_t exceptionFunction;
	int donotTurn;

	int weight;
	
	Path* searchPathByid(int id);
	MapNode();
	MapNode(int id);
	void tryAddPath(Path* path);
	bool _booked;
	
	
};

#endif
