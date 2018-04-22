#include <stdio.h>
#include <math.h>
#include <Windows.h>
#define PI 3.1415926
#define eps 0.000005

double Function(double x, double y)
{
	return tan(x * x + y * y);
}

int main()
{
	int i, j, m = 1, n = 1, kk = 0;
	double old, index;
	double In_down = 0, Out_down = 0;  //重积分内外层下限值；
	double In_up = PI / 3.0, Out_up = PI / 6.0;  //重积分内外层上限值；
	double h = (In_up - In_down) / (2 * n);
	double k = (Out_up - Out_down) / (2 * m);  //初始步长;
	double I_f = 0;  //初始结果；

	printf("k\t2^k\tI_f\t        DeltI_f\n");
	do
	{
		old = I_f;
		I_f = 0;
		I_f += Function(In_down, Out_down);
		index = 0;

		for (i = 1; i < n; i++)
		{
			index += Function(In_down + 2 * i * h, Out_down);
		}
		index *= 2;
		I_f += index;
		index = 0;

		for (i = 1; i <= n; i++)
		{
			index += Function(In_down + (2 * i - 1) * h, Out_down);
		}
		index *= 2;
		I_f += index;
		I_f += Function(In_up, Out_down);
		index = 0;

		for (j = 1; j < m; j++)
		{
			index += Function(In_down, Out_down + 2 * j * k);
		}
		index *= 2;
		I_f += index;
		index = 0;

		for (j = 1; j < m; j++)
		{
			for (i = 1; i < n; i++)
				index += Function(In_down + (2 * i) * h, Out_down + 2 * j * k);
		}
		index *= 4;
		I_f += index;
		index = 0;

		for (j = 1; j < m; j++)
		{
			for (i = 1; i <= n; i++)
				index += Function(In_down + (2 * i - 1) * h, Out_down + 2 * j * k);
		}
		index *= 8;
		I_f += index;
		index = 0;

		for (j = 1; j < m; j++)
		{
			index += Function(In_up, Out_down + 2 * j * k);
		}
		index *= 2;
		I_f += index;
		index = 0;

		for (j = 1; j <= m; j++)
		{
			index += Function(In_down, Out_down + (2 * j -1) * k);
		}
		index *= 4;
		I_f += index;
		index = 0;

		for (j = 1; j <= m; j++)
		{
			for (i = 1; i < n; i++)
			{
				index += Function(In_down + 2 * i * h, Out_down + (2 * j - 1) * k);
			}
		}
		index *= 8;
		I_f += index;
		index = 0;

		for (j = 1; j <= m; j++)
		{
			for (i = 1; i <= n; i++)
			{
				index += Function(In_down + (2 * i - 1) * h, Out_down + (2 * j - 1) * k);
			}
		}
		index *= 16;
		I_f += index;
		index = 0;

		for (j = 1; j <= m; j++)
		{
			index += Function(In_up, Out_down + (2 * j - 1) * k);
		}
		index *= 4;
		I_f += index;
		index += Function(In_down, Out_up);
		index = 0;

		for (i = 1; i < n; i++)
		{
			index += Function(In_down + (2 * i) * h, Out_up);
		}
		index *= 2;
		I_f += index;
		index = 0;

		for (i = 1; i <= n; i++)
		{
			index += Function(In_down + (2 * i - 1) * h, Out_up);
		}
		index *= 4;
		I_f += index;
		I_f += Function(Out_down, Out_up);
		I_f = I_f * h * k / 9;
		m *= 2;
		n *= 2;
		h = (In_up - In_down) / (2 * n);
		k = (Out_up - Out_down) / (2 * m);

		printf("%d\t%d\t%lf\t%lf\n", kk, m / 2, I_f, I_f - old);
		kk ++;
	}while (fabs(I_f - old) > eps);

	printf("I(f) is : %lf\n", I_f);

	double mm;
	mm = (double)(m / 2);
	double qq = log(mm) / log(2.0);
	printf("The numder of parts is: %lf\n", qq);
	
	system("pause");
	return 0;
	

}
