#ifndef __MAPNODE_H
#define __MAPNODE_H
class Path;

class MapNode
{
public:
	int id;
	int pathCount;
	int _dis;
	MapNode * _prevNode;
	Path* paths[8];
	char  name[10];
	
	
	int weight;
	
	Path* searchPathByid(int id);
	MapNode(int id);
	void tryAddPath(Path* path);
	bool _booked;
	
	
};

#endif