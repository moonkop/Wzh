

#include "main.h"
#define DEBUG	
#ifdef DEBUG
#define private public
#endif // DEBUG


Path *allPath[100];
int pathcount = 0;
int pathAutoIncreaseID = 100;



MapNode *allNode[100];
int nodecount = 0;


//===============CAR current 
extern MapNode* currentNode;
extern  int currentDirection;




MapNode* SearchForNodeByID(int id)
{
	for (int i = 0; i < nodecount; i++)
	{
		if (allNode[i]->id==id)
		{
			return allNode[i];
		}
	}
	return NULL;
}
Path* SearchForPathByID(int id)
{
	for (int i = 0; i < pathcount; i++)
	{
		if (allPath[i]->id == id)
		{
			return allPath[i];
		}
	}
	return NULL;
}
void addNodeToAllnode(MapNode * node)
{
	
	if (SearchForNodeByID(node->id) != NULL)
	{
		printf("Node id%d is already existed", node->id);
	}
	allNode[nodecount++] = node;
}
void addPahToAllPath(Path* path)
{
	if (SearchForPathByID(path->id) != NULL)
	{
		printf("Path id%d is already existed", path->id);
	}
	allPath[pathcount++] = path;
}
Path* CreatePathBetweenNode(int nodeID1,int nodeID2,int angle, int weight,char* name=NULL)
{
	Path* path= new Path(pathAutoIncreaseID++, angle,weight, name);
	path->bindNodeById(nodeID1, nodeID2);
	return path;
}
int  turnToDirection(int currentDirection,int targetDirection)
{
	currentDirection=	limit0360(currentDirection);
	targetDirection=	limit0360(targetDirection);


	int turnangle= targetDirection - currentDirection;
	turnangle=	limit0360(turnangle);

	if (turnangle>180)
	{
		turnangle -= 360;

		printf("turn right %d deg\n",-turnangle);
	}
	else
	{
		printf("turn left %d deg\n", turnangle);
	}
	return turnangle;
}
void goPath(Path* path,MapNode* currentNode)
{
	if (currentNode->searchPathByid(path->id)==NULL)
	{
		printf("invalid conn");
		return;
	}
	
	int pathdir=0;

	if (path->node[0]==currentNode)
	{
		pathdir = path->angle;
	}
	else
	{
		pathdir = path->angle + 180;

	}

	pathdir = limit0360(pathdir);

	turnToDirection(currentDirection, pathdir);
	currentDirection = pathdir;

	if (path->node[0] == currentNode)
	{
		printf("go through node%d node%d\n", path->node[0]->id, path->node[1]->id);
		::currentNode = path->node[1];

	}
	else
	{
		printf("go through node%d node%d\n", path->node[1]->id, path->node[0]->id);
		::currentNode = path->node[0];

	}

	printf("arrive node%d\n\n", currentNode->id);

}
int limit0360(int angle)
{
	if (angle>360)
	{
		angle -= 360;
	}
	else if (angle<0)
	{
		angle += 360;
	}
	if (angle>360||angle<0)
	{
		printf("invalid angle");
	}
	return angle;

}
int getWeightBetweenNodeByID(int nodeid1,int nodeid2)
{
	MapNode * node1 = SearchForNodeByID(nodeid1);
	MapNode * node2 = SearchForNodeByID(nodeid2);

	if (!node1)
	{
		printf("cant find node id=%d", nodeid1);
		return INT_MAX;
	}
	if (!node2)
	{
		printf("cant find node id=%d", nodeid2);
		return INT_MAX;
	}


	return getWeightBetweenNode(node1,node2);
}
int getWeightBetweenNode(MapNode* node1, MapNode* node2)
{

	for (int i = 0; i < node1->pathCount; i++)
	{
		if (node1->paths[i]->getAnotherNode(node1) == node2)
		{
			return node1->paths[i]->weight;
		}
	}
	return INT_MAX;

}
Path* route[20];
int pathRouteLength = 0;

MapNode* nodeRoute[100];
int nodeRouteCount=0;



Path* pathRoute[100];
int pathRouteCount = 0;

bool getRouteByID(int startID, int targetID)
{
	MapNode * nodeStart = SearchForNodeByID(startID);
	MapNode * nodeTarget = SearchForNodeByID(targetID);

	if (!nodeStart)
	{
		printf("cant find node id=%d", startID);
		return false;
	}
	if (!nodeTarget)
	{
		printf("cant find node id=%d", targetID);
		return false;
	}
	return getRoute(nodeStart, nodeTarget);
}
bool getRoute(MapNode* start, MapNode* target)
{
	for (int i = 0; i < nodecount; i++)
	{
		allNode[i]->_dis = INT_MAX;
		allNode[i]->_prevNode = NULL;
		allNode[i]->_booked = false;
	}
	start->_booked = 1;
	int min=0;
	MapNode * iteraterNode=NULL;

	start->_dis = 0;

	for (int i = 0; i < start->pathCount; i++)
	{
		Path* tempPath = start->paths[i];
		MapNode * tempNode = tempPath->getAnotherNode(start);
		tempNode->_dis = tempPath->weight;
	}

	for (int i = 0; i < nodecount-1; i++)
	{
		min = INT_MAX;
		//找出最小节点并放入路径

		if (iteraterNode==target)
		{
			break;
		}
		for (int j = 0; j < nodecount; j++)
		{
			if (allNode[j]->_booked==0 && allNode[j]->_dis<min)
			{
				min = allNode[j]->_dis;
				iteraterNode = allNode[j];
			}
		}
		iteraterNode->_booked = 1;
		for (int j = 0; j < iteraterNode->pathCount; j++)
		{

			MapNode* tempNode = iteraterNode->paths[j]->getAnotherNode(iteraterNode);
			if (tempNode->_dis>iteraterNode->_dis+ iteraterNode->paths[j]->weight)
			{
				tempNode->_dis = iteraterNode->_dis + iteraterNode->paths[j]->weight;
				tempNode->_prevNode = iteraterNode;
			}
		}
	}
	if (iteraterNode!=target)
	{
		printf("no path found! between %d ,%d",start->id,target->id	);
		return false;
	}
	nodeRouteCount = 0;
	while (iteraterNode!=NULL)
	{
		nodeRoute[nodeRouteCount++] = iteraterNode;
		iteraterNode = iteraterNode->_prevNode;
	}
	nodeRoute[nodeRouteCount++] = start;
	return true;
}
void convertRouteToPath()
{
	pathRouteCount = 0;
	int nodeCount = nodeRouteCount -1;
	
	while (nodeCount>=0)
	{
		MapNode* tempnode = nodeRoute[nodeCount];
		for (int i = 0; i < tempnode->pathCount; i++)
		{
			if (tempnode->paths[i]->getAnotherNode(tempnode)==nodeRoute[nodeCount-1])
			{
				pathRoute[pathRouteCount++] = tempnode->paths[i];
				break;

			}
		}
		nodeCount--;
	}
}
void goRoute(int startNodeID,int targetNodeID)
{
	getRouteByID(startNodeID, targetNodeID);
	convertRouteToPath();
	for (int i = 0; i < pathRouteCount; i++)
	{
		goPath(pathRoute[i], currentNode);
	}
}
void main()
{
	int nodeid = 1;
	MapNode n[9] = {
		MapNode(nodeid++),
		MapNode(nodeid++), 
		MapNode(nodeid++),
		MapNode(nodeid++),
		MapNode(nodeid++),
		MapNode(nodeid++),
		MapNode(nodeid++),
		MapNode(nodeid++),
		MapNode(nodeid++) };
	currentNode = &n[0];

	//Path *p1=	CreatePathBetweenNode(1, 2, 0, "path1 2");
	//Path *p2 = CreatePathBetweenNode(2, 3, 0, "path2 3");
	//Path *p3 = CreatePathBetweenNode(1, 4, 270, "path1 4");




	/*getRouteByID(4, 3);*/
	//goPath(p3, currentNode);


	Path *p1=	CreatePathBetweenNode(1, 2, 0,1, "path1 2");
	Path *p2 = CreatePathBetweenNode(2, 3, -90,2, "path2 3");
	Path *p3 = CreatePathBetweenNode(1, 3, -45,5, "path1 4");
	Path *p4 = CreatePathBetweenNode(2, 4, 0, 4, "path1 4");
	Path *p5 = CreatePathBetweenNode(3, 5, 0, 1, "path1 4");
	CreatePathBetweenNode(2, 5, -45,2, "");
	CreatePathBetweenNode(5, 7, 45,5, "");
	CreatePathBetweenNode(4, 6, 45, 8, "");
	CreatePathBetweenNode(6, 7, -90, 2, "");
	CreatePathBetweenNode(4, 5, -90, 1, "");
	//getRouteByID(1, 6);
	//convertRouteToPath();
	goRoute(1, 6);
}