#include <iostream>
#include <cmath>
#include <iomanip>
#define N 9
#define M N + 1
#define eps 0.5e-5 

using namespace std;

void Print_Matrix(double a[N][M]) //打印矩阵；
{
	cout << "####The output of the augmented matrix####" << endl;
	cout << endl;
	for (int i = 0; i < N; i++){
		for (int j = 0; j < M; j++){
			cout << setprecision(6) << a[i][j] << "\t";
		}
		cout << endl;
	}
}

double Max(double E[N]) //求解最大误差；
{
	double t;
	int k;
	t = (fabs(E[0]));
	for (k = 1; k < N; k++)
	{
		if (t < fabs(E[k]))
			t = fabs(E[k]);
	}
	return t;
}

int main()
{
	cout << "####The input of the augmented matrix####" << endl;
	cout << endl;
	double a[N][M] = { 0. };
	int i, j;
/*	for (i = 0; i < M; i++)
	{
		cout << "Please in put the " << i + 1 << "the augmented matrix row's N elements: " << endl;
		for (j = 0; j < N; j++){
			cin >> a[i][j];
		}
	}*/ //两种输入方式，一种从控制台直接输入，一种是利用文件输入数据，为了便于调试，选择文件输入；

	FILE *fpRead = fopen("data.txt", "r");
	if (fpRead == NULL)  {
		return 0;
	}
	for (i = 0; i<9; i++)  {
		for (j = 0; j<10; j++) {
			fscanf(fpRead, "%lf ", &a[i][j]);
			printf("%f\t", a[i][j]);
		}
		cout << endl;
	}
	getchar();
	fclose(fpRead);
	Print_Matrix(a);

	double w; //松弛因子
	int t, k;
	double E[N];
	double sum;
	cout << "w" << "\t" << "迭代次数" << "\t" << endl;
	for (k = 1; k < 100; k++)
	{
		t = 0;
		w = k / 50.0;
		double xold[N] = { 1, 1, 1, 1, 1, 1, 1, 1, 1 }; 
		double xnew[N] = { 1, 1, 1, 1, 1, 1, 1, 1, 1 }; //初值；
		do
		{
			for (i = 0; i < N; i++){
				xold[i] = xnew[i];
			}
			for (i = 0; i < N; i++){
				sum = 0;
				for (j = 0; j < i; j++){
					sum += a[i][j] * xnew[j];
				}
				for (j = i + 1; j < N; j++){
					sum += a[i][j] * xold[j];
				}
				xnew[i] = (1 - w) * xold[i] + w * (a[i][M - 1] - sum) / a[i][i];
			}
			for (i = 0; i < N; i++){
				E[i] = xnew[i] - xold[i];
			}
			t++;
		} while (Max(E) >= eps);
		if (Max(E) <= eps){
			cout << w << "\t" << t << "\t" << endl;
		}

		for (i = 0; i < N; i++){ //打印解向量；
			cout << "xnew" << i + 1 << ": " << xnew[i] << "\t";
		}
	}
	cout << endl;

	return 0;
}
