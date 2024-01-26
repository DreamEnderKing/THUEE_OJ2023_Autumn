#include <stdio.h>

#define DEBUG

// 栈单元：值+重复次数
// 栈中值严格倒序排列，无重复值
long* stack;
unsigned int* t_stack;
long top;

int main()
{
	int n;
	scanf("%d", &n);
	const int size = n / 2;
	stack = new long[size];
	t_stack = new unsigned int[size];
	for(int i = 0; i < size; i++)
	{
		stack[i] = 0;
		t_stack[i] = 0;
	}

	int m;
	unsigned long long times = 0;
	scanf("%d", &m);
	stack[0] = m;
	t_stack[0] = 1;
	top = 0;
	for(int i = 1; i < n; i++)
	{
#ifdef DEBUG
		printf("times: %d, stack: [", times);
		for(int j = 0; j <= top; j++)
			printf(" %d(%d),", stack[j], t_stack[j]);
		printf("]\n");
#endif

		scanf("%d", &m);
		if(m < stack[top])
		{
			// 假如新队员比栈顶队员弱，则只需比武一次
			times++;
			top++;
			stack[top] = m;
			t_stack[top] = 1;
		}
		else if(m == stack[top])
		{
			// 假如新队员与栈顶相等，则需要与所有相同武力值的成员比武完毕
			times += t_stack[top] + ((top == 0) ? 0 : 1);
			t_stack[top]++;
		}
		else
		{
			// 假如新队员比栈顶队员强，则需要比武，直到新队员比栈顶弱为止，栈顶出栈
			while(m > stack[top] && top >= 0)
			{
				times += t_stack[top];
				stack[top] = 0;
				t_stack[top] = 0;
				top--;
			}
			if(m == stack[top])
			{
				// 如果不位于栈底，还会和之前的成员比武一次
				times += t_stack[top] + ((top == 0) ? 0 : 1);
				t_stack[top]++;
			}
			else if(top < 0)
			{
				// 如果击败了所有对手
				top = 0;
				stack[top] = m;
				t_stack[top] = 1;
			}
			else
			{
				// 否则，新队员入栈
				top++;
				times++;
				stack[top] = m;
				t_stack[top] = 1;
			}
		}
	}

	printf("%lld", times);
}