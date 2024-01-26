#include "stdio.h"
#include "limits.h"
#include "malloc.h"

#pragma warning(disable:4996)

typedef long long int64;

int n;
int dimension;
int* size;						// 存储前k-2维大小信息

struct cell
{
	int64 times;
	int mask;					// 第i维是否为1的掩码
	int divide;					// 分割点和头部的长度
	int64 matX, matY;			// 最后两维构成矩阵
};

cell** table;

int64 getMulti(int mask)
{
	int i = 0x1, result = 1;
	for (int j = 0; j < dimension - 2; i <<= 1, j++)
	{
		if (mask & i)
		{
			result *= size[j];
		}
	}
	return result;
}

int main()
{
	scanf("%d %d", &n, &dimension);
	size = new int[dimension - 2];
	table = new cell * [n];

	// table规则：[delta][start]
	for (int i = 0; i < n; i++)
	{
		table[i] = new cell[n - i];
	}

	for (int i = 0; i < n; i++)
	{
		table[0][i].mask = 0;
		int m = 0x1;
		for (int j = 0; j < dimension - 2; j++, m <<= 1)
		{
			int64 a;
			scanf("%lld", &a);
			if (a != 1)
			{
				table[0][i].mask += m;
				size[j] = a;				// 假设输入合法性
			}
		}
		scanf("%lld", &table[0][i].matX);
		scanf("%lld", &table[0][i].matY);
		table[0][i].times = 0;
		table[0][i].divide = 0;
	}

	for (int delta = 1; delta < n; delta++)
	{
		for (int i = 0; i < n - delta; i++)
		{
			cell* target = table[delta] + i;
			target->mask = (table[0][i].mask) | (table[delta - 1][i + 1].mask);
			target->matX = table[0][i].matX;
			target->matY = table[0][i + delta].matY;
			target->times = LLONG_MAX;
			int64 multi = getMulti(target->mask) * target->matX * target->matY;
			if (delta < 600)
			{
				for (int k = 0; k < delta; k++)
				{
					int64 t1 = table[k][i].times, t2 = table[delta - k - 1][i + k + 1].times;
					int64 t3 = multi * table[k][i].matY;
					if (t1 + t2 + t3 < target->times)
					{
						target->times = t1 + t2 + t3;
						target->divide = k;
					}
				}
			}
			else
			{
				int64 min = table[delta - 1][i].divide, max = table[delta - 1][i + 1].divide + 2;
				const int64 l = 100;
				min = (min - l >= 0) ? min - l : 0;
				max = (max + l <= delta) ? max + l : delta;
				for (int k = 0; k < l; k++)
				{
					int64 t1 = table[k][i].times, t2 = table[delta - k - 1][i + k + 1].times;
					int64 t3 = multi * table[k][i].matY;
					if (t1 + t2 + t3 < target->times)
					{
						target->times = t1 + t2 + t3;
						target->divide = k;
					}
				}
				for (int k = delta - l; k < delta; k++)
				{
					int64 t1 = table[k][i].times, t2 = table[delta - k - 1][i + k + 1].times;
					int64 t3 = multi * table[k][i].matY;
					if (t1 + t2 + t3 < target->times)
					{
						target->times = t1 + t2 + t3;
						target->divide = k;
					}
				}
				for (int k = min; k < max; k++)
				{
					int64 t1 = table[k][i].times, t2 = table[delta - k - 1][i + k + 1].times;
					int64 t3 = multi * table[k][i].matY;
					if (t1 + t2 + t3 < target->times)
					{
						target->times = t1 + t2 + t3;
						target->divide = k;
					}
				}
			}
		}
	}

	printf("%lld", table[n - 1][0].times);
}