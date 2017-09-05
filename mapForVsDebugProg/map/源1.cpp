#include <iostream>  
#include <cstdio>  
#include <cstring>  
#include<algorithm>
#include<fstream>
using namespace std;
#define count1 80

int main1()
{

	int i, j, pcount, scount, p1, p2, length, u, v, min, startPoint, endPoint, inf = 999999, order[count1], Count = 0;
	int e[count1][count1], dis[count1], book[count1], before[count1];
	for (int i = 0; i < count1; i++)
	{
		before[i] = 0;
	}
	ifstream ifile;
	ifile.open("c://short_path.txt");
	ifile >> pcount >> scount;
	for (i = 1; i <= pcount; i++)
	{
		for (j = 1; j <= pcount; j++)
		{
			if (i == j)
				e[i][j] = 0;
			else
				e[i][j] = inf;
		}
	}
	for (int i = 1; i <= scount; i++)
	{
		ifile >> p1 >> p2 >> length;
		//cout << p1 << p2 << length<<endl;
		e[p1][p2] = length;
		e[p2][p1] = length;
	}
	printf("请输入起始点\n");
	cin >> startPoint;
	for (i = 1; i <= pcount; i++)
	{
		dis[i] = e[startPoint][i];
	}
	for (i = 1; i <= pcount; i++)
	{
		book[i] = 0;
	}
	book[startPoint] = 1;
	for (i = 1; i <= pcount - 1; i++)
	{
		min = inf;
		for (j = 1; j <= pcount; j++)
		{
			if (book[j] == 0 && dis[j] <min)
			{
				min = dis[j];
				u = j;
			}
		}
		book[u] = 1;
		for (v = 1; v <= pcount; v++)
		{
			if (e[u][v] < inf)
			{
				if (dis[v]>dis[u] + e[u][v])
				{
					dis[v] = dis[u] + e[u][v];
					before[v] = u;
					//cout << "u " << u << "v " << v << endl;
				}
			}
		}
	}
	printf("请输入结束点\n");

	cin >> endPoint;
	while (endPoint != 0)
	{

		order[Count++] = endPoint;
		endPoint = before[endPoint];
	}
	order[Count] = startPoint;
	for (i = Count; i >= 0; i--)
	{
		printf("%d ", order[i]);
	}
	ifile.close();
	return 0;
}