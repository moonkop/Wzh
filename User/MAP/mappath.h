#ifndef __MAPPATH_H
#define __MAPPATH_H
 
class MapNode;

typedef void(*TrackFucntion_t)(int);
typedef void(*ProcessFunction_t)();

struct PathSpeed
{
	int length;
	int speed;
};

class Path
{
public:

	//void (* processfun)(void);
	Path(int id, int angle, int weight);
	Path(int id, int angle, int weight, char * name);
	int GetWeightFromNode(MapNode * node);
	void bindNodeById(int id1, int id2);
	MapNode* getAnotherNode(MapNode* self);
	void setOneNode(MapNode* node);
	int getDirFromNode(MapNode * node);

	int weight;
	int speed;

	int id;
	bool SingeDirectionOnly;
	MapNode* node[2];
	int _currentNodeCount;
	int length;
	int angle;
	char  name[10];
	TrackFucntion_t specifiedTrackFunction;
	ProcessFunction_t processFunction;

};

#endif
