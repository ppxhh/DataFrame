#include <iostream>
#include <cmath>
#include <cstdlib>
#include <iomanip>
#include <cstdio>
#define M 9
#define N M+1

using namespace std;

int Swap_Principal(double a[M][N], int x) //交换主元；
{
	int i,k;
	double t[10];
	for (i = x; i < M; i++){
	    t[x] = a[i][x];
	}
	double max = fabs(t[x]);
	for (i = x+1; i < M; i++){
		if(fabs(t[i]) > max){
			max = fabs(t[i]);
			k = i;
		}
		else{
			k = x;
		}
	}
	for (i = x; i < M; i++){
		double l[N];
		l[i] = a[x][i];
		a[x][i] = a[k][i];
		a[k][i] = l[i];
	}
	return k;
}

void New_Matrix(double a[M][N], int x, double b[M][N]) //消元计算；
{
	int i, j;
	for (i = 0; i < N ; i ++){
		b[x][i] = a[x][i];
	}
	for (i = x + 1; i < M; i++){
		for (j = x; j < N; j++){
			if (a[x][x] == 0){
				i ++;
				break;
			}
			else{
			b[i][j] = a[i][j] - (a[i][x] / a[x][x]) * a[x][j];
			}
		}
	}
}

void Print_Matrix(double a[M][N]) //打印矩阵；
{
	cout << "####The output of the augmented matrix####" << endl;
	cout << endl;
	for (int i = 0; i < M; i++){
		for (int j = 0; j < N; j++){
			cout << setprecision(6) << a[i][j] << "\t";
		}
		cout << endl;
	}
}

int main()
{
	cout << "####The input of the augmented matrix####" << endl;
	cout << endl;
	double a[M][N] = {0.};
	int i, j;
	
/*	for (i = 0; i < M; i++)
	{
		cout << "Please in put the " << i + 1 << "the augmented matrix row's N elements: " << endl;
		for (j = 0; j < N; j++){
			cin >> a[i][j];
		}
	}*/ //两种输入方式，一种从控制台直接输入，一种是利用文件输入数据，为了便于调试，选择文件输入；
 
    FILE *fpRead=fopen("data.txt","r");  
    if(fpRead==NULL)  {  
        return 0;  
    }  
    for(i=0;i<9;i++)  {  
		for(j=0;j<10;j++) {
        fscanf(fpRead,"%lf ",&a[i][j]);  
        printf("%lf\t",a[i][j]);  
   		}
		cout << endl;
	}
    getchar();
	fclose(fpRead);

	double b[M][N];
	int k;
	for ( k = 0; k < M-2; k ++){
		double ll = Swap_Principal(a, k);
	    New_Matrix(a, k, b);
		for (i = 0; i < M; i ++){
			for (j = 0; j < N; j ++){
				a[i][j] = b[i][j];
			}
		}
	}
	New_Matrix(a, M - 2, b);
	Print_Matrix(b);

	cout << "####The solution of the augmented matrix####" << endl;
	double x[9];
	for ( i = M-2; i >= 0; i --){
		x[M-1] = b[M-1][N-1] / b[M-1][M-1];
		double sum = 0;
		for ( j = i + 1; j <= M-1; j ++){
			sum += b[i][j] * x[j];
			x[i] = (b[i][N-1] - sum) / a[i][i];
		}
	}

	cout << "####The root of the augmented matrix####" << endl;
	for (i = 0; i < M; i ++){
		cout << "x" << i + 1 << ": " << setprecision(5) << x[i] << "\t";
	}
	cout << endl;

	return 0;
}
