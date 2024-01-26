#include "stdio.h"

//#define DEBUG
class NodeList
{
public:
	NodeList();
	~NodeList();
	void Add(int x, int y);
	void PrintAfter(int x);
	void PrintAll();
	void Remove(int x);
private:
	int *data;
	int head;
};

NodeList::NodeList()
{
	data = new int[100000];
	for(int i = 0; i < 100000; i++)
	{
		data[i] = 0;
	}
	head = 0;
}

NodeList::~NodeList()
{
	delete[] data;
}

void NodeList::Add(int x, int y)
{
	if(x == 0) {
		data[y] = head;
		head = y;
	}
	else {
		data[y] = data[x];
		data[x] = y;
	}
}

void NodeList::PrintAfter(int x)
{
	if(x == 0) {
		printf("%d\n", head);
	}
	else {
		printf("%d\n", data[x]);
	}
}

void NodeList::PrintAll()
{
	int i = head;
	while(i != 0)
	{
		printf("%d\n", i);
		i = data[i];
	}
}

void NodeList::Remove(int x)
{
	if(head == x)
	{
		head = data[x];
		data[x] = 0;
	}
	for(int i = 0; i < 100000; i++)
	{
		if(data[i] == x)
		{
			data[i] = data[x];
			data[x] = 0;
			break;
		}
	}
}

int main()
{
	NodeList list = {};
	list.Add(0, 1);
	int n, c, a1, a2;
	scanf("%d", &n);
	for(int i = 0; i < n; i++)
	{
#ifdef DEBUG
		list.PrintAll();
#endif
		scanf("%d", &c);
		switch (c)
		{
		case 1:
			scanf("%d %d", &a1, &a2);
			list.Add(a1, a2);
			break;
		case 2:
			scanf("%d", &a1);
			list.PrintAfter(a1);
			break;
		case 3:
			scanf("%d", &a1);
			list.Remove(a1);
			break;
		default:
			break;
		}
	}
	list.PrintAll();
}