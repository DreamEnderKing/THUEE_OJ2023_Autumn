#include <stdio.h>
#include <malloc.h>

#pragma warning(disable:4996)
#pragma warning(disable:6031)

#define abs(x) ((x)>0 ? (x) : -(x)) 

double* xi, * yi, * x, * y;

int N, M;

int map[] = {0, 64, 32, 96, 16, 48, 80, 8, 24, 40, 56, 72, 88, 4, 12, 20, 28, 36, 44, 52, 60, 68, 76, 84, 92, 2, 6, 10, 14, 18, 22, 26, 30, 34, 38, 42, 46, 50, 54, 58, 62, 66, 70, 74, 78, 82, 86, 90, 94, 98, 1, 3, 5, 7, 9, 11, 13, 15, 17, 19, 21, 23, 25, 27, 29, 31, 33, 35, 37, 39, 41, 43, 45, 47, 49, 51, 53, 55, 57, 59, 61, 63, 65, 67, 69, 71, 73, 75, 77, 79, 81, 83, 85, 87, 89, 91, 93, 95, 97, 99};

void println(const char* str, double* data, int length)
{
	printf(str);
	printf(": {");
	for (int i = 0; i < length; i++)
		printf("%.8lf, ", data[i]);
	printf("}\n");
}

int main()
{
	scanf("%d %d", &N, &M);
	xi = (double*)malloc(sizeof(double) * N);
	yi = (double*)malloc(sizeof(double) * N);
	x = (double*)malloc(sizeof(double) * N);
	y = (double*)malloc(sizeof(double) * N);
	double* t = (double*)malloc(sizeof(double) * N);
	double* a = (double*)malloc(sizeof(double) * N);
	double* f = (double*)malloc(sizeof(double) * N);

	scanf("%lf %lf", xi, yi);
	// 对输入数组进行排序以改善条件数
	double xt, yt;
	for (int i = 1; i < N; i++)
	{
		scanf("%lf %lf", &xt, &yt);
		int l = 0, r = i - 1;
		while (l <= r)
		{
			int a = (l + r) / 2;
			if (xi[a] < xt)
				l = a + 1;
			else
				r = a - 1;
		}
		// TO DO: 滤除x差距过小的项(OK)
		if ((l >= 1 && xt - xi[l - 1] < 1e-6) || (l < i && xi[l] - xt < 1e-6))
		{
			i--, N--;
			continue;
		}
		for (int j = i - 1; j >= l; j--)
		{
			xi[j + 1] = xi[j];
			yi[j + 1] = yi[j];
		}
		xi[l] = xt, yi[l] = yt;
	}

	// 牛顿法求解并同步还原至多项式
	f[0] = 1, t[0] = yi[0], a[0] = t[0], x[0] = xi[0], y[0] = yi[0];
	int n = 1;
	for (int i = 1, cur = 1; i < N; i++)
	{
		a[i] = f[i] = 0;
		// 预求值
		int m;
		do
		{
			m = map[cur];
			cur++;
		} while (m >= N);
		double sum = 0, prod = 1;
		for (int j = 0; j <= n; j++)
		{
			sum += a[j] * prod;
			prod *= xi[m];
		}
		if (abs(sum - yi[m]) < 1e-6)
			continue;
		// 牛顿法解系数
		x[n] = xi[m], y[n] = yi[m];
		sum = 0, prod = 1;
		for (int j = 0; j < n; j++)
		{
			sum += t[j] * prod;
			prod *= x[n] - x[j];
		}
		t[n] = (y[n] - sum) / prod;
		// 还原为多项式
		f[n] = 1;
		for (int j = n - 1; j > 0; j--)
		{
			f[j] = -x[n - 1] * f[j] + f[j - 1];
		}
		f[0] *= -x[n - 1];
		for (int j = 0; j <= n; j++)
		{
			a[j] += t[n] * f[j];
		}
		n++;
	}
	printf("%d\n", n - 1);
	//println("t", t, n);
	//println("a", a, n);


	for (int i = 0; i < M; i++)
	{
		scanf("%lf", &xt);
		// 二分法查找吸附
		int l = 0, r = N - 1;
		while (l <= r)
		{
			int a = (l + r) / 2;
			if (xi[a] < xt)
				l = a + 1;
			else
				r = a - 1;
		}
		if (l - 1 >= 0 && xt - xi[l - 1] <= 1e-6)
		{
			printf("%.7lf\n", yi[l - 1]);
		}
		else if (l < N && xi[l] - xt <= 1e-6)
		{
			printf("%.7lf\n", yi[l]);
		}
		else
		{
			// 正常计算
			double sum = 0, prod = 1;
			for (int j = 0; j <= n; j++)
			{
				sum += a[j] * prod;
				prod *= xt;
			}
			printf("%.7lf\n", sum);
		}
	}
}