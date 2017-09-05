#include "mapNode.h"
#include "main.h"
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

MapNode::MapNode(int id)
{
	this->id = id;
	this->pathCount = 0;
	addNodeToAllnode(this);
}

void MapNode::tryAddPath(Path * path)
{
	if (this->searchPathByid(path->id))
	{
		printf("path id = %d is already in node %d", path->id, this->id);

	}
	else
	{
		this->paths[this->pathCount++] = path;

	}
}