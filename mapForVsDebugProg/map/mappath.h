#ifndef __MAPPATH_H
#define __MAPPATH_H
 
class MapNode;


class Path
{
public:
	int weight;
	Path(int id, int angle, int weight);
	Path(int id, int angle, int weight, char * name);
	void bindNodeById(int id1, int id2);
	MapNode* getAnotherNode(MapNode* self);
	void setOneNode(MapNode* node);
	char  name[10];
	int id;
	MapNode* node[2];
	int _currentNodeCount;
	int length;
	
	int angle;
};

#endif