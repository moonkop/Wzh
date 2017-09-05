#include "mapNode.h"
#include "preProcesser.h"
#include "main.h"

extern int NodeAutoincreaseID;



Path * MapNode::searchPathByid(int id)
{
	for (int i = 0; i < this->pathCount; i++)
	{
		if (this->paths[i]->id == id)
		{
			return this->paths[i];
		}
	}
	return NULL;

}

MapNode::MapNode()
{
	//this->name = NULL;
	this->exceptionFunction = NULL;
	this->weight = 0;
	this->id = NodeAutoincreaseID++;
	this->pathCount = 0;
	this->donotTurn = false;

	addNodeToAllnode(this);
}

MapNode::MapNode(int id)
{
	this->id = id;
	this->pathCount = 0;

	addNodeToAllnode(this);
}

//MapNode::MapNode(int id, void processfun)
//{
//	this->id = id;
//	this->pathCount = 0;
//	this->processfun = processfun;
//	addNodeToAllnode(this);
//}

void MapNode::tryAddPath(Path * path)
{
	if (this->searchPathByid(path->id))
	{
		LCD_printf("path id = %d is already in node %d", path->id, this->id);
	}
	else
	{
		this->paths[this->pathCount++] = path;
	}
}
