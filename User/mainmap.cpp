
#include "maincpp.h"
#include "MAP\map.h"//"map.h"
#include "track.h"
#include "myMath.h"
extern u8 SEN2020Array[8];
extern u8 linecount;
extern u8 lines[8];
extern int currentSpeed;
u8 flatSceneIdArray[] = { 5,13,1,12,15,28,41,51 };
u8 flatSceneIdArrayLen = 8;
u8 vertialIdarray[] = { 7,11,31,32,34 };
u8 vertialSceneIdArrayLen = 5;
u8 dumbNodeArray[] = { 54,55,56,57,58 };
u8 dumbNodeArrayLen = 5;
u8 singleLineBridgeArray[] = { 21,44 };
u8 singleLineBridgeArrayLen = 2;
u8 flatSceneToTreasure[] = { 1,5,13,12,28,15,51,41 };
u8 flatSceneToTreasureLen = 8;
u8 doorArrayPos[] = { 17,18,19,20 };

u8 doorArrayLen = 4;
bool stopRouteFlag = 0;

u8 travelSceneArray[] = {1,5,7,13,11,12,28,34,51,41,32,1};

int Nodeid1 = 45;
int Nodeid2 = 43;

MapNode* nextNode;
ExceptionFunction_t exceptionFunction;
TrackFucntion_t trackfunction;
MapNode* currentNode = 0;
int currentDirection = 180;
int RouteIndex;
int Speed_VeryHigh = 200;
int Speed_High = 100;
int Speed_Mid = 70;
int Speed_Low = 50;






void setFunctions()
{
	MapNode* node;

	for (int i = 0; i < flatSceneIdArrayLen; i++)
	{
		node = SearchForNodeByID(flatSceneIdArray[i]);
		node->processFunction = PF_Flat_scene;
		node->exceptionFunction = _ExceptionFunction_NoLine;
		node->paths[0]->specifiedTrackFunction = getToLine_Mixed;
	}
	for (int i = 0; i < vertialSceneIdArrayLen; i++)
	{
		node = SearchForNodeByID(vertialIdarray[i]);
		node->processFunction = PF_normal_scene;
		node->exceptionFunction = _ExceptionFunction_NoLine;
		node->paths[0]->specifiedTrackFunction = getToLine_Mixed;

	}

	for (int i = 0; i < dumbNodeArrayLen; i++)
	{
		node = SearchForNodeByID(dumbNodeArray[i]);
		node->donotTurn = true;
		node->exceptionFunction = _ExceptionFunction_OneLine;
	}
	for (int i = 0; i < singleLineBridgeArrayLen; i++)
	{ 
		node = SearchForNodeByID(singleLineBridgeArray[i]);
		node->donotTurn = true;
		node->exceptionFunction = _ExceptionFunction_NoLine;
		node->processFunction = PF_SingleSideBridge;
	}
#ifdef TRAVELCAR
	for (int i = 0; i < doorArrayLen; i++)
	{
		node = SearchForNodeByID(doorArrayPos[i]);
		node->exceptionFunction = _ExceptionFunction_ArriveDoor;
		node->processFunction = PF_Door;
	}
#endif // TRAVELCAR

	node = SearchForNodeByID(42);
	node->exceptionFunction= _ExceptionFunction_NoLine;
	node->processFunction = PF_Flat_450_scene;

	node = SearchForNodeByID(14);
	node->donotTurn = true;
	node->exceptionFunction = _ExceptionFunction_OneLine;


	node = SearchForNodeByID(16);
	node->donotTurn = true;
	node->exceptionFunction = _ExceptionFunction_NoLine;
	node->processFunction = PF_seesawOnCircle;

	node = SearchForNodeByID(23);
	node->processFunction=PF_CircleEnter;
}

void MAP_Init()
{
	MapNode *node = new MapNode[60];

	CreatePathBetweenNode(2, 1, 0, 10, 100,Speed_High);  //100


	CreatePathBetweenNode(3, 2, 0, 2, 10, Speed_High)->specifiedTrackFunction = getToLine_Mixed;
	CreatePathBetweenNode(4, 3, 0, 2, 50, Speed_Mid);
	node[3].processFunction = PF_Bridge;
	CreatePathBetweenNode(5, 4, 0, 2, 150,Speed_High)->specifiedTrackFunction = getToLine_Mixed;

	CreatePathBetweenNode(4, 6, -35, 2, 220, Speed_Low);
	CreatePathBetweenNode(6, 2, 35, 2, 225, Speed_Mid);
	CreatePathBetweenNode(7, 8, -20, 2,300, Speed_High);

	CreatePathBetweenNode(8, 6, 0, 2, 150, Speed_High);
	CreatePathBetweenNode(6, 9, 0, 2, 150, Speed_High);
	CreatePathBetweenNode(9, 10, 0, 2, 130, Speed_VeryHigh);
	CreatePathBetweenNode(10, 12, 0, 2,195, Speed_VeryHigh);
	CreatePathBetweenNode(10, 11, 35, 2, 200, Speed_VeryHigh);
	CreatePathBetweenNode(13, 8, 0, 2, 300, Speed_VeryHigh);
	
	CreatePathBetweenNode(24, 25, 0, 2, 130, Speed_High);
	CreatePathBetweenNode(25, 26, 0, 2, 130, Speed_High);


	CreatePathBetweenNode(17, 8, 90, 30, 100, Speed_High);//100
	CreatePathBetweenNode(24, 17, 90, 30, 135, Speed_High);//135
	CreatePathBetweenNode(26, 20, 90, 30, 135, Speed_High);//135
	CreatePathBetweenNode(20, 9, 90, 30, 100, Speed_High);//100
	CreatePathBetweenNode(8, 18, -35, 30, 50, Speed_High);//50
	CreatePathBetweenNode(18, 52, -35, 30, 45, Speed_High);//45
	CreatePathBetweenNode(52, 19, 35, 30, 70, Speed_High);//45
	CreatePathBetweenNode(19, 9, 35, 30, 70, Speed_High);//50

	CreatePathBetweenNode(52, 26, -35, 2, 95, Speed_High);//95
	CreatePathBetweenNode(24, 52, 35, 2, 95, Speed_High);//95
	

	CreatePathBetweenNode(24, 33, -90, 2, 60, Speed_High);
	CreatePathBetweenNode(33, 32, -180, 2, 0, Speed_High);
	CreatePathBetweenNode(33, 36, -90, 2, 60, Speed_High);
	CreatePathBetweenNode(36, 37, 0, 2, 130, Speed_High);
	CreatePathBetweenNode(37, 25, 90, 2, 100, Speed_High);
	CreatePathBetweenNode(37, 38, 0, 2, 75, Speed_High);
	CreatePathBetweenNode(38, 34, 90, 2, 30, Speed_High);
	CreatePathBetweenNode(38, 39, 0, 2, 75, Speed_High);
	CreatePathBetweenNode(39, 26, 90, 2, 120, Speed_High);


	//CreatePathBetweenNode(39, 40, 0, 2, 50, Speed_High);     //
	CreatePathBetweenNode(39, 57, 0, 2, 200, Speed_High);//
	CreatePathBetweenNode(57, 58, 45, 2, 20, Speed_High);//
	CreatePathBetweenNode(58, 40, 85, 2, 20, Speed_High);//


	//CreatePathBetweenNode(27, 40, -90, 2, 50, Speed_High);    //
	CreatePathBetweenNode(27, 56, -30, 2, 20, Speed_High);//
	CreatePathBetweenNode(56, 40, -90, 2, 20, Speed_High);//

	CreatePathBetweenNode(26, 27, 0, 2, 60, Speed_High);
	CreatePathBetweenNode(27, 28, 0, 2, 280, Speed_High);
	CreatePathBetweenNode(10, 21, -90, 100, 50, Speed_High);//
	CreatePathBetweenNode(21, 22, 0, 10, 50, Speed_High);//

	//CreatePathBetweenNode(22, 27, -135, 2, 50, Speed_High);  //
	CreatePathBetweenNode(54, 22, 10, 1, 20, Speed_High);//
	CreatePathBetweenNode(55, 54, 60, 1, 20, Speed_High);//
	CreatePathBetweenNode(27, 55, 75, 0, 20, Speed_High);//


	//圆
	CreatePathBetweenNode(15, 29, 90, 2, 96, Speed_Mid);
	CreatePathBetweenNode(14, 29, 5, 2, 150, Speed_Mid);   //
	CreatePathBetweenNode(29, 16, -5, 2, 20, Speed_Mid);   //
	CreatePathBetweenNode(14, 23, -30, 200, 180, Speed_Mid)->SingeDirectionOnly = true;   //
	CreatePathBetweenNode(23, 16, 5, 2, 70, Speed_Mid)->SingeDirectionOnly = true;   //



	CreatePathBetweenNode(30, 31, 0, 2, 30, Speed_High);//
	CreatePathBetweenNode(41, 42, 0, 2, 0, Speed_Low);
	CreatePathBetweenNode(49, 35, 90, 2, 50, Speed_High);//
	CreatePathBetweenNode(42, 43, 0, 2, 170, Speed_High);
	CreatePathBetweenNode(35, 43, -35, 2, 50, Speed_High);//
	CreatePathBetweenNode(43, 44, 0, 2, 77, Speed_High);
	CreatePathBetweenNode(23, 24, 0, 2, 180, Speed_Mid);
	CreatePathBetweenNode(30, 48, -90, 2, 50, Speed_High);//
	CreatePathBetweenNode(48, 49, 0, 2, 50, Speed_High);//
	CreatePathBetweenNode(44, 37, 90, 2, 80, Speed_High);
	CreatePathBetweenNode(44, 45, 0, 2, 70, Speed_Mid);
	CreatePathBetweenNode(40, 47, -90, 2, 50, Speed_High);//
	CreatePathBetweenNode(47, 46, -180, 2, 50, Speed_High);//
	CreatePathBetweenNode(45, 46, 0, 2, 50, Speed_High);//
	CreatePathBetweenNode(45, 50, -90, 2, 60, Speed_High);
	CreatePathBetweenNode(50, 51, 0, 2, 250, Speed_Mid);
	CreatePathBetweenNode(30, 53, 90, 2, 10, Speed_High);//
	CreatePathBetweenNode(53, 23, 0, 2, 50, Speed_High);//
	setFunctions();
	currentNode = &node[1];
}

void MAP_getPathRoute(int nodeid1, int nodeid2)
{
	nodeRouteCount = 0;
	pathRouteCount = 0;
	currentNode = SearchForNodeByID(nodeid1);
	getRouteByID(nodeid1, nodeid2);
	//PrintGoRoute(nodeid1, nodeid2);
	currentNode = SearchForNodeByID(nodeid1);
	convertRouteToPath();

}

Path* currentPath = 0;
void MAP_goRoute(int Nodeid1, int Nodeid2)
{
	stopRouteFlag = 0;
	MAP_getPathRoute(Nodeid1, Nodeid2);

	//Path NewPath[100];
	//int NewPathCount = 0;
	//for (int i = 0; i < pathRouteCount; i++) {
	//	if(isOneLine(pathRoute[i], pathRoute[i+1]))
	//}
	for ( RouteIndex = 0; RouteIndex < pathRouteCount; RouteIndex++)
	{
		currentPath = pathRoute[RouteIndex];
		
		MAP_goPath(currentPath);
		if (stopRouteFlag)
		{
			break;
		}
	}
	setSpeed(0, 0);
}

void MAP_goRoute_Test()
{
	MAP_goRoute(Nodeid1, Nodeid2);
}
bool rapidFlag = 0;
int defaultRapidSpeed = 100;
void MAP_goPath(Path* path)
{
	LCD_printf("currentNode:%d\t", currentNode->id);
	LCD_printf("direction:%d\n", currentDirection);
	if (!currentNode->searchPathByid(path->id))
	{
		LCD_printf("current Node error\n");
		while (1)
		{
			;
		}
		return;
	}
	currentSpeed = 60;
	//到达节点后往前走15cm到达节点中心
	if (rapidFlag==0)
	{
		goWithPulse(12, FORWORD);
	}
	rapidFlag = 0;

	beepWaiting(100);
	nextNode = path->getAnotherNode(currentNode);
	int pathdir = path->getDirFromNode(currentNode);//turn before track on path

	if (!nextNode->exceptionFunction)
	{
		exceptionFunction = GetExceptionFunction(path, nextNode);
	}
	else
	{
		exceptionFunction = nextNode->exceptionFunction;
	}
	//如果设置在这个节点不转弯 则跳过转弯

	if (currentNode->donotTurn == true)
	{
		LCD_printf("Dont wanna turn at node %d", nextNode->id);
	}
	else
	{
		int angle = turnToDirection(currentDirection, pathdir);//get turn angle
		turnAngleByPulse(angle);
		}
	//在转弯后 将目前的方向设置为道路的方向
	currentDirection = pathdir;
	LCD_printf("goPath currentdir=%d\n currentNode=%d nextNode=%d\n", currentDirection, currentNode->id, nextNode->id);
	//获得传感器中目标线的序号
	int lineIndex= GetLineIndexToGo();
	LCD_printf("LINEINDEX=%d\n", lineIndex);

	
	/*
	路程控制
	在不跳过节点时，不走完全部节点路程 进入判断阶段
	在跳过节点时，走完节点全部路程 不进入判断阶段直接进入下一个节点
	所以加速时间有区别
	*/
	
	GetRapidFlag();
	int RapidLength = path->length;

	if (rapidFlag != true)
	{
		//在不跳过节点时 留30cm作判断使用
		RapidLength -= 30;
		printf("cant skip at node%d\n", nextNode->id);
	}
	else
	{

		printf("Skip dect at node%d\n", nextNode->id);

	}


	if(RapidLength<40)
	{
		trackToLine(RapidLength, lineIndex);
	}
	else
	{
		trackToLine(40, lineIndex);
		//40cm后正常巡线，并加速
		int rapidSpeed = path->speed;

		if (rapidSpeed==0)
		{
			rapidSpeed = defaultRapidSpeed;
		}
		TrackNoExceptionForLength(RapidLength - 40, rapidSpeed);
	}
	
	//忽略节点
	if (rapidFlag == true)
	{
		return;
	}
	
	
	LCD_printf("trackLen %d end\n detecting", path->length);
	//加速行驶完成 开始检测路口 

	beepWaiting(100);

	trackfunction = getToLine_Mixed;

	if (path->specifiedTrackFunction)
	{
		trackfunction = path->specifiedTrackFunction;
	}

	FillFitter(1, 0);
	FillFitter(0, 1);
	//寻迹并判断路口

	setPixelColor(Color_yellow);
	while (!exceptionFunction())
	{
		getSEN2020DigitalData();
		getLines(SEN2020Array);
		//getToLine(); //track till crossroad
		trackfunction(0);
	}
	LCD_printf(" ExceptionFunction  Triggered!\n");

	currentNode = nextNode;
	setPixelColor(Color_pink);

	if (nextNode->processFunction)
	{
		printf("proceeding nextNode=%d ProcessFunction ", nextNode->id);
		nextNode->processFunction();
	}
	LCD_printf("\n\n\n\n\n\n");
}
bool GetRapidFlag()
{
	if (RouteIndex+1>=pathRouteCount)
	{
		printf("cant rapid Last node\n");
		return	rapidFlag = false;
	}
	Path* nextPath = pathRoute[RouteIndex + 1];
	int nextAngle = getAngleBetweenPath(currentPath, nextPath);

	if (nextAngle!=0||nextNode->processFunction!=NULL)
	{
		printf("cant rapid angle!=0 or has pf\n");
		return	rapidFlag = false;
	}
	
	for (int i = 0; i < nextNode->pathCount; i++)
	{
		int angle = abs(getAngleBetweenPath(currentPath, nextNode->paths[i]));
		if (angle > 135 && angle != 180)
		{
			printf("cant rapid next node dirty");
			return	rapidFlag = false;

		}
	}
	printf("Rapiding in nextNode=%d",nextNode->id);
	return	rapidFlag = true;
}
ExceptionFunction_t GetExceptionFunction(Path* p, MapNode* n)
{
	if (n->searchPathByid(p->id) == NULL)
	{
		LCD_printf("GetExceptionFunctionError\n");
		while (1)
		{
			;
		}
		return NULL;
	}
	//vertical
	MapNode *node2 = p->getAnotherNode(n);

	int angle = 0;
	int i = 0;
	if (n->pathCount == 1)
	{
		LCD_printf("GetException pathcount=1 from node%d to node%d\n", node2->id, n->id);
		return NULL;
	}
	//getAngleBetweenPath 返回角度与实际角形状相同，锐角弯返回锐角


	//遇到100度到80度的弯道采用直角判断条件
	for (i = 0; i < n->pathCount; i++)
	{
		int angle = abs(getAngleBetweenPath(p, n->paths[i]));
		if (angle >= 80 && angle <= 100)
		{
			LCD_printf("GetException Vertial from node%d to node%d\n", node2->id, n->id);
			return _ExceptionFunction_vertial;
		}

	}

	//遇到0-75度的弯道采用多变一判断条件
	for (i = 0; i < n->pathCount; i++)
	{
		angle = abs(getAngleBetweenPath(p, n->paths[i]));
		if (angle < 80)//错误
		{
			LCD_printf("GetException MutiToOneLine from node%d to node%d\n", node2->id, n->id);
			return _ExceptionFunction_MutiToOneLine;
		}
	}

	//遇到两条以上100-180的弯道采用一变多判断条件
	int mutiLineCount = 0;
	for (i = 0; i < n->pathCount; i++)
	{
		angle = abs(getAngleBetweenPath(p, n->paths[i]));
		if (angle > 100 && angle <= 180)
		{
			mutiLineCount++;
		}
		if (mutiLineCount > 1)
		{
			LCD_printf("GetException ToMutiline from node%d to node%d\n", node2->id, n->id);
			return _ExceptionFunction_ToMutiline;
		}
	}

	LCD_printf("GetException OneLine from node%d to node%d\n", node2->id, n->id);


	return  _ExceptionFunction_OneLine;


	//TomutiLine
}

//目前的节点 目前的方向 目的路径
//目前节点 currentNode
//目前方向 currentDirection
//目前路径 currentPath

struct PathNearBy
{
	Path* path;
	int directionOffset;
};
int GetLineIndexToGo()
{
	PathNearBy pathNearBy[4];
	int pathNearByCount = 0;

	//获得与当前路径临近的路径
	for (int i = 0; i < currentNode->pathCount; i++)
	{
		Path* path = currentNode->paths[i];
		int pathdir = path->getDirFromNode(currentNode);
		pathdir = limit0360(pathdir);
		currentDirection = limit0360(currentDirection);
		int directionOffset =   pathdir- currentDirection;
		if(directionOffset>180)
		{
			directionOffset-=360;
		}
		if ( abs(directionOffset)>45)
		{
			continue;
		}
		pathNearBy[pathNearByCount].path = path;
		pathNearBy[pathNearByCount].directionOffset = directionOffset;
		pathNearByCount++;
	}
	
	PathNearBy pathnearbyTemp;
	//进行排序
	for (int i = 0; i < pathNearByCount - 1; i++)
	{
		for (int j = 0; j < (pathNearByCount - 1 - i); j++)
		{
			if (pathNearBy[j].directionOffset > pathNearBy[j + 1].directionOffset)
			{
				pathnearbyTemp = pathNearBy[j];
				pathNearBy[j] = pathNearBy[j + 1];
				pathNearBy[j + 1] = pathnearbyTemp;
			}
		}
	}
	//找出第几个是目前的路径
	int targetIndex = 0;
	for (int i = 0; i < pathNearByCount; i++)
	{
		if (pathNearBy[i].directionOffset==0)
{
			targetIndex = i;
			break;

		}
	}
	//返回路径在传感器中的序号
	return targetIndex;

}
int GetClosetLineIndex(int prevLinePostion)
{
	int minoffset = 100;
	int minIndex = 0;

	if (linecount = 0)
	{
		return 0;
	}

	for (int i = 0; i < linecount; i++)
	{
		if (lines[i] - prevLinePostion < minoffset)
		{
			minIndex = i;
			minoffset = lines[i] - prevLinePostion;
		}
	}
	return minIndex;
}
