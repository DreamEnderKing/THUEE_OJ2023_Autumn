#include "stdio.h"

int BitToTer(int num, char* ret)
{
	// 鉴于学生学号范围，三进制数长度为20
	int i;
	for(i = 0; i < 20; i++)
		ret[i] = 0;
	for(i = 0; num != 0 && i < 20; i++)
	{
		ret[i] = num % 3;
		num /= 3;
	}
	return i;
}

void TerAdd(char *buf, char *num)
{
	for(int i = 0; i < 20; i++)
		buf[i] = (buf[i] + num[i]) % 3;
}

int main(void)
{
	int m, n, r;
	scanf("%d", &n);
	int cur = 0;		// 指示3进制位最高位
	char sum[20] = {0}, num[20] = {0};

	for(int i = 0; i < 3 * n - 1; i++)
	{
		scanf("%d", &m);
		int j = BitToTer(m, num);
		TerAdd(sum, num);
		cur = (j > cur) ? j : cur;
	}
	
	for(int i = cur - 1; i >= 0; i--)
	{
		r *= 3;
		r += (3 - sum[i]) % 3;
	}

	printf("%d\n", r);
}