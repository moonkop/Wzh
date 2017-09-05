#include "mappath.h"
#include "main.h"
Path::Path(int id, int angle,int weight)
{
	this->weight = weight;
	this->id = id;
	this->angle = angle;
	allPath[pathcount++] = this;
	_currentNodeCount = 0;

}
Path::Path(int id, int angle, int weight ,char * name)
{
	this->weight = weight;

	this->id = id;
	this->angle = angle;
	allPath[pathcount++] = this;
	_currentNodeCount = 0;
	strcpy(this->name, name);

}
void Path::bindNodeById(int id1, int id2)
{

	MapNode * node1 = SearchForNodeByID(id1);
	MapNode * node2 = SearchForNodeByID(id2);
	if (!node1)
	{
		printf("node1 is null id =%d", id1);
	}
	else
	{
		this->setOneNode(node1);
	}
	if (!node2)
	{
		printf("node2 is null id =%d", id1);
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
		printf("node in path is  too much path id =%d node id =%d", this->id, node->id);
		return;
	}
	this->node[_currentNodeCount++] = node;
	node->tryAddPath(this);

}