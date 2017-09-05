#include "../preProcesser.h"
#include "mappath.h"
#include "map.h"
Path::Path(int id, int angle, int weight)
{
	this->weight = weight;
	this->id = id;
	this->angle = angle;
	this->_currentNodeCount = 0;
	this->SingeDirectionOnly = false;
	allPath[pathcount++] = this;
}
Path::Path(int id, int angle, int weight, char * name)
{
	this->weight = weight;
	this->id = id;
	this->angle = angle;
	this->SingeDirectionOnly = false;
	this->_currentNodeCount = 0;
	allPath[pathcount++] = this;
	//strcpy(this->name, name);
}

int Path::GetWeightFromNode(MapNode* node)
{
	if (!this->SingeDirectionOnly)
	{
		return weight;
	}
	else
	{
		if (this->node[1] == node)
		{
			return weight;
		}
		else
		{
			return 10000;
		}
	}
}
void Path::bindNodeById(int id1, int id2)
{

	MapNode * node1 = SearchForNodeByID(id1);
	MapNode * node2 = SearchForNodeByID(id2);
	if (!node1)
	{
		LCD_printf("node1 is null id =%d", id1);
	}
	else
	{
		this->setOneNode(node1);
	}
	if (!node2)
	{
		LCD_printf("node2 is null id =%d", id1);
	}
	else
	{
		this->setOneNode(node2);
	}

}
MapNode * Path::getAnotherNode(MapNode* self)
{
	if (self == this->node[0])
	{
		return this->node[1];
	}
	else 
	{
		return this->node[0];
	}

}
void Path::setOneNode(MapNode * node)
{
	if (_currentNodeCount >= 2)
	{
		LCD_printf("node in path is  too much path id =%d node id =%d", this->id, node->id);
		return;
	}
	this->node[_currentNodeCount++] = node;
	node->tryAddPath(this);

}
int Path::getDirFromNode(MapNode * node)
{
	int pathdir = 0;
	if (this->node[0] == node)
	{
		pathdir = this->angle;
	}
	else if (this->node[1]==node)
	{
		pathdir = this->angle + 180;
	}
	else{
	LCD_printf("path %d not include node %d",this->id,node->id);
	
	}
	return pathdir;

}

//bool isOneLine(Path Path1, Path Path2) {
//	if (getAngleBetweenPath(&Path1, &Path2) == 180) {
//		return 1;
//	}
//	return 0;
//}
//Path getUnionPath(Path Path1, Path Path2) {
//	Path *tempPath=new Path(0,0,0);
//	tempPath->id = Path1.id;
//	tempPath->angle = Path1.angle;
//	tempPath->length = Path1.length + Path2.length;
//	return *tempPath;
//}