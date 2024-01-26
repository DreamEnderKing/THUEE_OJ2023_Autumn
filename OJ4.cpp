#include <stdio.h>

#define DEBUG

struct storey
{
	long begin, end;
	long *bp_pos; // 当前层缺损点所在位置
	long bp_num;	 // 当前层缺损点个数
	storey *prev;
	storey *next;
};

long *bps, *tps;		// 记录breakpolongs和targetpolongs的数组
long *e_bps, *e_tps; // 数组结束位置+1
storey *head;
int height;

int main()
{
	// 初始化存储数组
	int N, M;
	scanf("%d %d", &N, &M);
	bps = new long[N];
	tps = new long[M];
	e_bps = bps + N;
	e_tps = tps + M;
	// 初始化第一层
	height = 1;
	head = new storey;
	head->begin = head->end = 1;
	head->bp_num = 0;
	head->bp_pos = NULL;
	head->prev = head->next = NULL;

	// 读取数据并存储
	long max_tp = 0;
	for (int i = 0; i < N; i++)
	{
		scanf("%ld", bps + i);
	}
	for (int i = 0; i < M; i++)
	{
		scanf("%ld", tps + i);
		max_tp = tps[i];
	}

	// DEBUG: 如果根节点就是缺损节点的话程序工作不正常
	if (bps[0] == 1)
	{
		int i = 0;
		if (tps[0] == 1)
		{
			printf("1 \n");
			i++;
		}
		for (; i < M; i++)
		{
			printf("0 \n");
		}
		return 0;
	}

	// 建立层视图
	storey *pres = head;
	long *p_bps = bps;
	long *buf = new long[N]; // 临时存储
	long forbidden = __LONG_MAX__;
	while (pres->end < max_tp)
	{
		height++;
		storey *cs = new storey;
		pres->next = cs;
		cs->prev = pres;
		cs->begin = pres->end + 1;
		cs->end = cs->begin + 2 * (pres->end - pres->begin - pres->bp_num + 1) - 1;
		cs->bp_num = 0;
		cs->next = NULL;
		while (p_bps < e_bps && *p_bps <= cs->end)
		{
			buf[cs->bp_num] = *p_bps - cs->begin; // Warning: 决定了每层次序为0, 1, ...
			cs->bp_num++;
			p_bps++;
		}
		// 如果有一层全是缺损点，那么层到此结束
		if (cs->bp_num == cs->end - cs->begin + 1)
		{
			forbidden = cs->end;
			break;
		}
		cs->bp_pos = new long[cs->bp_num];
		for (int i = 0; i < cs->bp_num; i++)
		{
			cs->bp_pos[i] = buf[i];
		}
		pres = cs;
	}
	delete[] buf;
	delete[] bps;

	// 查找所在位置
	long *stack = new long[height];
	for (long *p_tps = tps; p_tps < e_tps; p_tps++)
	{
		// 查询所在层层高
		int h = 0, p = 0;
		long cv = *p_tps;
		if (cv > forbidden)
		{
			printf("0 \n");
			continue;
		}
		storey *cs = head;
		for (; h < height; h++, cs = cs->next)
			if (cv <= cs->end)
				break;
		// 递归查询上级
		for (;; h--)
		{
			stack[p] = cv;
			if (h == 0)
				break;
			storey *ps = cs->prev;
			long ind = (cv - cs->begin) / 2;
			for (int i = 0; i < ps->bp_num; i++)
				if (ps->bp_pos[i] <= ind)
					ind++;
			cv = ps->begin + ind;
			cs = ps;
			p++;
		}
		// 输出查询结果
		for (; p >= 0; p--)
			printf("%ld ", stack[p]);
		printf("\n");
	}
	delete[] stack;
	delete[] tps;
}