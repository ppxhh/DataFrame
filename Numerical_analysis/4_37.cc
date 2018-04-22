#include <iostream>
#include <Windows.h>
#define NUM 11
using namespace std;
int main()
{
	double x[NUM], y[NUM], h[NUM], u[NUM];
	double v[NUM], d[NUM], M[NUM], b[NUM];
	double t[NUM], l[NUM], yy[NUM];
	double s[4];
	int i,n;
	double df[2];

	cout << "Please input the n: " << endl;
	cin >> n;

	FILE *fp, *fp1;
	fp = fopen("data_X.txt", "r");  //Read the x;
	if (fp == NULL)  {
		return 0;
	}
	for (i = 0; i < NUM; i ++)  {
		fscanf(fp, "%lf ", &x[i]);
		cout << x[i] << " ";
	}
	cout << endl;
	fclose(fp);

	fp1 = fopen("data_Y.txt", "r"); //Read the y;
	if (fp1 == NULL)  {
		return 0;
	}
	for (i = 0; i < NUM; i++)  {
		fscanf(fp1, "%lf ", &y[i]);
		cout << y[i] << " ";
	}
	cout << endl;
	fclose(fp1);
	
	cout << "Please input the df0 and df10: " << endl;  //Input 端点条件；
	cin >> df[0] >> df[1];

	for (i = 0; i <= n - 1; i ++)
	{
		h[i] = x[i + 1] - x[i];
		cout << "The h[" << i <<"]: " << h[i] << endl;
	}

	v[0] = 1;
	u[n] = 1;
	for (i = 1; i <= n - 1; i ++)
	{
		u[i] = h[i - 1] / (h[i - 1] + h[i]);
		v[i] = h[i] / (h[i - 1] + h[i]);
	}

	for (i = 1; i < n; i ++)
	{
		d[i] = 6 * ((y[i + 1] - y[i]) / h[i] - (y[i] - y[i - 1])) / h[i - 1] / (h[i - 1] + h[i]);
		d[0] = 6 * ((y[1] - y[0]) / h[0] - df[0]) / h[0];
		d[n] = 6 * (df[1] - (y[n] - y[n - 1])) / h[n - 1] / h[n - 1];
	}
	cout << "u[NUM]" << "\t" << "u[NUM]" << "\t" << "u[NUM]" << endl;
	for (i = 1; i <= n; i ++)
	{
		cout << u[i] << "\t";
	}
	cout << endl;
	for (i = 0; i < n; i++)
	{
		cout << v[i] << "\t";
	}
	cout << endl;
	for (i = 0; i <= n; i++)
	{
		cout << d[i] << "\t";
	}
	cout << endl;

	for(i = 0; i <= n; i ++)
	{
		b[i] = 2;
	}
	t[0] = b[0];
	yy[0] = d[0];
	for(i = 1; i <= n; i ++)
	{
		l[i] = u[i] / t[i - 1];
		t[i] = b[i] - l[i] * v[i - 1];
		yy[i] = d[i] - l[i] *  yy[i - 1];
	}
	M[n] = yy[n] / t[n];
	for (i = n - 1; i >= 0; i --)
	{
		M[i] = (yy[i] - v[i] * M[i + 1]) / t[i];
	}
	for ( i = 0; i <= n; i ++)
	{
		cout  << "M[" << i << "] = " << M[i] << endl;
	}	
	double S[10];
	for ( i = 0; i < n; i ++)
	{
		s[0] = y[i];
		s[1] = (y[i + 1] - y[i]) / h[i] -(M[i] / 3 + M[i + 1] /6) * h[i];
		s[2] = M[i + 1] / 2;
		s[3] = (M[i + 1] - M[i]) / (6 * h[i]);
		cout << "x in [" << i << "," << i + 1 << "]; " << "s(x) = ";
		cout << s[0] << " + (" << s[1] << " * (x - " << i << "))" << " + (" << s[2] << " * (x - " << i << ")^2)" << " + (" << s[3] << " * (x - " << i << ")^3)" << endl;		
		S[i] = s[0] + s[1] * 0.5 + s[2] * 0.5 * 0.5 + s[3] * 0.5 * 0.5 * 0.5;
	}	
	for (i = 0; i < 10; i ++)
	{
		cout << i + 1 << "\t" << "S[" << i + 0.5 << "]" << "\t" << S[i] << endl;
	}
	system("pause");
	return 0;
}
