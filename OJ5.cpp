#include <stdio.h>

#define OUT_STR "OUTPUT: %u\n"

typedef unsigned int uint;
typedef unsigned short ushort;

struct node
{
	// 记录子节点信息
	uint size = 0, *value = NULL, bridge = (uint)-1;
};

uint *dfn = NULL, *low = NULL;
node *graph = NULL;

int num = 0;


void tarjan(uint x, uint prev)
{
	dfn[x] = low[x] = ++num;
	for (uint i = 0; i < graph[x].size; i++)
	{
		int y = graph[x].value[i];
		if (y == prev)
			continue;
		if (!dfn[y])
		{
			tarjan(y, x);
			low[x] = low[x] < low[y] ? low[x] : low[y];
			if (dfn[x] < low[y])
			{
				graph[x].bridge = y;
			}
		}
		else
		{
			low[x] = low[x] < dfn[y] ? low[x] : dfn[y];
		}
	}
}

int main()
{
	uint N, M;
	scanf("%u %u", &N, &M);
   	graph = new node[N];
	dfn = new uint[N];
	low = new uint[N];

	for (uint i = 0; i < N; i++)
	{
		scanf("%u", &graph[i].size);
		graph[i].value = new uint[graph[i].size];
		for (uint j = 0; j < graph[i].size; j++)
		{
			scanf("%u", &graph[i].value[j]);
		}
	}
	
	for (uint i = 0; i < N; i++)
	{
		if (!dfn[i])
		{
			tarjan(i, (uint)-1);
		}
	}

	for (uint i = 0; i < N; i++)
	{
		if (graph[i].bridge != (uint)-1)
		{
			for (uint j = 0; j <= M; j++)
			{
				printf(OUT_STR, 0);
			}
			return 0;
		}
	}
	printf(OUT_STR, 1);

	for (uint i = 0; i < M; i++)
	{
		uint p1, p2;
		scanf("%u %u", &p1, &p2);
		if (graph[p1].bridge == p2)
		{
			printf(OUT_STR, 0);
		}
		else if (graph[p2].bridge == p1)
		{
			printf(OUT_STR, 0);
		}
		else
		{
			printf(OUT_STR, 1);
		}
	}
}