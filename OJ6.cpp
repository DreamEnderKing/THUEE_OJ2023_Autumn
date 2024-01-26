#include <stdio.h>

#define cut 8

typedef unsigned int uint32;
typedef long long int64;

#define __UINT32_MAX__ 4294967295U

uint32 M, K, ind = 0;
int64 H;
int64 pairs = 0;

class Queue
{
public:
	Queue(uint32 _cap)
	{
		cap = _cap;
		if (cap)
		{
			data = new uint32[cap];
		}
		else
			data = NULL;
		head = 0; tail = 0; count = 0;
	}
	~Queue()
	{
		if (cap != 0)
			delete[] data;
	}
	void Enqueue(uint32 x)
	{
		data[tail] = x;
		tail = (tail + 1) % cap;
		count++;
	}
	uint32 Dequeue()
	{
		uint32 tmp = data[head];
		head = (head + 1) % cap;
		count--;
		return tmp;
	}
	uint32 GetVal(int i)
	{
		return data[(i + head) % cap];
	}
	uint32 count;
protected:
	uint32 cap;
	uint32* data;
	uint32 head, tail;
};

long long tmp = 0;

int main()
{
	scanf("%u %u %lld", &M, &K, &H);

	uint32 cell_c = (uint32)((int64)(__UINT32_MAX__) * cut / H + 1);
	Queue steps = Queue(K);
	Queue **cells = new Queue*[cell_c];
	for (uint32 i = 0; i < cell_c; i++)
	{
		cells[i] = new Queue(K / 2);
	}
	if (M <= 1 || K == 0)
	{
		printf("0\n");
		return 0;
	}

	// 初始化台阶数据
	for (; ind < M && ind < K; ind++)
	{
		scanf("%lld", &tmp);

		uint32 cell_i = (uint32)(tmp * cut / H);
		for (int j = -(cut - 1); j <= (cut - 1); j++)
		{
			if (cell_i + j < 0 || cell_i + j > cell_c)
				continue;
			pairs += cells[cell_i + j]->count;
		}
		if (cell_i >= cut)
			for (int j = 0; j < cells[cell_i - cut]->count; j++)
			{
				int64 d = (int64)cells[cell_i - cut]->GetVal(j);
				if (d >= tmp - H)
					pairs++;
			}
		if (cell_i <= cell_c - cut)
			for (int j = 0; j < cells[cell_i + cut]->count; j++)
			{
				int64 d = (int64)cells[cell_i + cut]->GetVal(j);
				if (d <= tmp + H)
					pairs++;
			}
		uint32 t = (uint32)tmp;
		steps.Enqueue(cell_i);
		cells[cell_i]->Enqueue(t);
	}
	// 依次录入并比较
	for (; ind < M; ind++)
	{
		scanf("%lld", &tmp);

		uint32 cell_i = (uint32)(tmp * cut / H);
		for (int j = -(cut - 1); j <= (cut - 1); j++)
		{
			if (cell_i + j < 0 || cell_i + j > cell_c)
				continue;
			pairs += cells[cell_i + j]->count;
		}
		if (cell_i >= cut)
			for (int j = 0; j < cells[cell_i - cut]->count; j++)
			{
				int64 d = (int64)cells[cell_i - cut]->GetVal(j);
				if (d >= tmp - H)
					pairs++;
			}
		if (cell_i <= cell_c - cut)
			for (int j = 0; j < cells[cell_i + cut]->count; j++)
			{
				int64 d = (int64)cells[cell_i + cut]->GetVal(j);
				if (d <= tmp + H)
					pairs++;
			}
		uint32 prev = steps.Dequeue();
		steps.Enqueue(cell_i);
		cells[prev]->Dequeue();
		cells[cell_i]->Enqueue((uint32)tmp);
	}
	printf("%lld\n", pairs);
}