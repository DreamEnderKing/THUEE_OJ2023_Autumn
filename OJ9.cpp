#include "stdio.h"
#include "limits.h"
#include <queue>
#include <vector>

#pragma warning(disable:4996)

typedef long long int64;
using namespace std;

int64* EH, * EHR;		// Edge Head(and reversed)
int64 EC = 0;		// Edge Count

int64 N, M;
int64 Begin, End, TimeLimit;

struct Edge
{
	int64 from;
	int64 to;
	int64 next;
	int64 r_next;
	int64 time;
	int64 cost;
} *Edges;

struct Node
{
	Node(int64 _time = 0, int64 _cost = 0, int64 _distance = 0, int64 _index = 0, int64 _physical = 0, int64 _expand = 0)
		: time(_time), cost(_cost), distance(_distance), index(_index), physical(_physical), expand(_expand) {}
	Node(const Node& n)
		: time(n.time), cost(n.cost), distance(n.distance), index(n.index), physical(n.physical), expand(n.expand) {}
	int64 time;
	int64 cost;
	int64 distance;
	int64 index;
	int64 physical;
	int64 expand;
} *Nodes;

// 允许动态修改数值的最小堆
class Heap
{
private:
	void FixUp(int64 i)
	{
		int j = (i - 1) / 2;
		while (i > 0 && Comparer(data[i], data[j]))
		{
			data[i]->index = j, data[j]->index = i;
			Node* temp = data[i];
			data[i] = data[j], data[j] = temp;
			i = j;
			j = (i - 1) / 2;
		}
	}

	void FixDown(int64 i)
	{
		int j = 2 * i + 1;
		while (j < count)
		{
			if (j < count - 1 && Comparer(data[j + 1], data[j]))
				j++;
			if (Comparer(data[i], data[j]))
				break;
			data[i]->index = j, data[j]->index = i;
			Node* temp = data[i];
			data[i] = data[j], data[j] = temp;
			i = j;
			j = 2 * i + 1;
		}
	}
public:
	vector<Node*> data = {};
	int64 count = 0;

	typedef bool (*LessFunc)(Node*, Node*);
	LessFunc Comparer;

	void Push(Node* n)
	{
		data.push_back(n);
		n->index = count;
		count++;
		FixUp(count - 1);
	}

	Node* Pop()
	{
		Node* result = data.front();
		data[0] = data.back();
		data[0]->index = 0;
		data.pop_back();
		count--;
		FixDown(0);
		return result;
	}

	void Update(int64 i)
	{
		Node* temp = new Node(*data[i]);
		FixUp(i);
		FixDown(i);
		delete temp;
	}

	void Clear()
	{
		data.clear();
		count = 0;
	}
} NodeHeap;

void AddEdge(int64 u, int64 v, int64 time, int64 cost)
{
	Edges[EC].from = u;
	Edges[EC].to = v;
	Edges[EC].time = time;
	Edges[EC].cost = cost;
	Edges[EC].next = EH[u];
	Edges[EC].r_next = EHR[v];
	EH[u] = EC;
	EHR[v] = EC;
	EC++;
}

// 以distance为值进行Dijkstra算法
void Reversed_Dijkstra()
{
	auto cmp = [](Node* n1, Node* n2) -> bool { return (n1->distance < n2->distance) || n2->distance == -1; };
	NodeHeap.Clear();
	NodeHeap.Comparer = cmp;
	bool* visited = new bool[N];
	for (int64 i = 0; i < N; i++)
	{
		visited[i] = false;
		Nodes[i].index = -1;
	}

	Nodes[End].distance = 0;
	visited[End] = true;
	NodeHeap.Push(Nodes + End);

	while (NodeHeap.count)
	{
		Node* node = NodeHeap.Pop();
		visited[node->physical] = true;
		for (int64 j = EHR[node->physical]; j != -1; j = Edges[j].r_next)
		{
			Node* parent = &(Nodes[Edges[j].from]);
			if (!visited[parent->physical])
			{
				int64 expectedDistance = node->distance + Edges[j].cost;
				if (parent->distance == -1)
				{
					parent->distance = expectedDistance;
					NodeHeap.Push(parent);
				}
				else if (expectedDistance < parent->distance)
				{
					parent->distance = expectedDistance;
					NodeHeap.Update(parent->index);
				}
			}
		}
	}
}

int64 AStar_KthPath_Small()
{
	auto cmp = [](Node* n1, Node* n2) -> bool { return (n1->cost + n1->distance < n2->cost + n2->distance)
		|| ((n1->cost + n1->distance == n2->cost + n2->distance) && (n1->cost < n2->cost)
		|| n2->cost == -1 || n2->distance == -1); };
	NodeHeap.Clear();
	NodeHeap.Comparer = cmp;
	for (int64 i = 0; i < N; i++)
	{
		Nodes[i].index = -1;
	}

	Nodes[Begin].cost = 0;
	Nodes[Begin].time = 0;
	NodeHeap.Push(new Node(Nodes[Begin]));

	int64 cost = -1;

	while (NodeHeap.count)
	{
		Node* node = NodeHeap.Pop();
		for (int64 j = EH[node->physical]; j != -1; j = Edges[j].next)
		{
			Node* child = new Node(Nodes[Edges[j].to]);
			child->cost = node->cost + Edges[j].cost;
			child->time = node->time + Edges[j].time;
			child->expand++;
			if (child->time > TimeLimit)
			{
				delete child;
				continue;
			}
			if (child->physical == End)
			{
				cost = (cost > child->cost || cost < 0) ? child->cost : cost;
				continue;
			}
			NodeHeap.Push(child);
		}
	}
	return cost;
}

int64 AStar_KthPath_Big()
{
	auto cmp = [](Node* n1, Node* n2) -> bool { return (n1->cost + n1->distance < n2->cost + n2->distance)
		|| ((n1->cost + n1->distance == n2->cost + n2->distance) && (n1->cost < n2->cost)
			|| n2->cost == -1 || n2->distance == -1); };
	NodeHeap.Clear();
	NodeHeap.Comparer = cmp;
	for (int64 i = 0; i < N; i++)
	{
		Nodes[i].index = -1;
	}

	Nodes[Begin].cost = 0;
	Nodes[Begin].time = 0;
	NodeHeap.Push(new Node(Nodes[Begin]));

	while (NodeHeap.count)
	{
		Node* node = NodeHeap.Pop();
		int64 cost = -1;
		bool canExit = false;

		for (int64 j = EH[node->physical]; j != -1; j = Edges[j].next)
		{
			Node* child = new Node(Nodes[Edges[j].to]);
			child->cost = node->cost + Edges[j].cost;
			child->time = node->time + Edges[j].time;
			child->expand++;
			if (child->time > TimeLimit)
			{
				delete child;
				continue;
			}
			if (child->physical == End)
			{
				cost = (cost > child->cost || cost < 0) ? child->cost : cost;
				canExit = true;
				continue;
			}
			NodeHeap.Push(child);
		}
		if (canExit)
		{
			return cost;
		}
	}
	return -1;
}

int main()
{
	scanf("%lld %lld", &N, &M);
	EH = new int64[N];
	EHR = new int64[N];
	Nodes = new Node[N];
	Edges = new Edge[M];
	for (int64 i = 0; i < N; i++)
	{
		EH[i] = -1;
		EHR[i] = -1;
		Nodes[i].physical = i;
		Nodes[i].cost = -1;
		Nodes[i].time = -1;
		Nodes[i].distance = -1;
		Nodes[i].expand = 0;
	}
	for (int64 i = 0; i < M; i++)
	{
		int64 a, b, c, d;
		scanf("%lld %lld %lld %lld", &a, &b, &c, &d);
		if (a != b)
			AddEdge(a, b, c, d);
	}
	scanf("%lld %lld %lld", &Begin, &End, &TimeLimit);

	Reversed_Dijkstra();

	if (Nodes[Begin].distance == -1)
	{
		printf("-1");
		return 0;
	}

	int64 cost = (N <= 1500) ? AStar_KthPath_Small() : AStar_KthPath_Big();
	printf("%lld", cost);
}