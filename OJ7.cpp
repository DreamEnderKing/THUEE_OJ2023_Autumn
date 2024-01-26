#include <stdio.h>
#include <malloc.h>

#pragma warning(disable:4996)
#pragma warning(disable:6031)

int p, N, M;

int main()
{
	scanf("%d", &p);
	scanf("%d %d", &N, &M);

	// A矩阵: e->d->c->b->a
	// L矩阵: 全1->l->m
	// U矩阵: w->v->u
	double* d = (double*)malloc(sizeof(double) * N),
		* c = (double*)malloc(sizeof(double) * N),
		* b = (double*)malloc(sizeof(double) * N),
		* a = (double*)malloc(sizeof(double) * N),
		* l = (double*)malloc(sizeof(double) * N),
		* m = (double*)malloc(sizeof(double) * N),
		* u = (double*)malloc(sizeof(double) * N),
		* v = (double*)malloc(sizeof(double) * N),
		* w = (double*)malloc(sizeof(double) * N);
	if (p == 3)
	{
		for (int i = 0; i < N - 2; i++)
			w[i] = 0;
		for (int i = 0; i < N - 1; i++)
			scanf("%lf", d + i);
		for (int i = 0; i < N; i++)
			scanf("%lf", c + i);
		for (int i = 0; i < N - 1; i++)
			scanf("%lf", b + i);
		for (int i = 0; i < N - 2; i++)
			a[i] = 0;
	}
	else if (p == 5)
	{
		for (int i = 0; i < N - 2; i++)
			scanf("%lf", w + i);
		for (int i = 0; i < N - 1; i++)
			scanf("%lf", d + i);
		for (int i = 0; i < N; i++)
			scanf("%lf", c + i);
		for (int i = 0; i < N - 1; i++)
			scanf("%lf", b + i);
		for (int i = 0; i < N - 2; i++)
			scanf("%lf", a + i);
	}
	u[0] = c[0];
	v[0] = d[0];
	l[0] = b[0] / u[0];
	u[1] = c[1] - l[0] * v[0];
	for (int i = 0; i < N - 2; i++)
	{
		m[i] = a[i] / u[i];
		l[i + 1] = (b[i + 1] - m[i] * v[i]) / u[i + 1];
		v[i + 1] = d[i + 1] - l[i] * w[i];
		u[i + 2] = c[i + 2] - m[i] * w[i] - l[i + 1] * v[i + 1];
	}
	// 向量运算链: UX=Y, LY=Z
	double* x = d, * y = c, * z = b;
	for (int t = 0; t < M; t++)
	{
		for (int i = 0; i < N; i++)
			scanf("%lf", z + i);
		y[0] = z[0];
		y[1] = z[1] - l[0] * y[0];
		for (int i = 2; i < N; i++)
		{
			y[i] = z[i] - l[i - 1] * y[i - 1] - m[i - 2] * y[i - 2];
		}
		x[N - 1] = y[N - 1] / u[N - 1];
		x[N - 2] = (y[N - 2] - v[N - 2] * x[N - 1]) / u[N - 2];
		for (int i = N - 3; i >= 0; i--)
		{
			x[i] = (y[i] - v[i] * x[i + 1] - w[i] * x[i + 2]) / u[i];
		}
		for (int i = 0; i < N; i++)
		{
			printf("%.4lf ", x[i]);
		}
		printf("\n");
	}
}