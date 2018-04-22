#include <iostream>
#include <cmath>
#include <iomanip>

#define h 0.000001

using namespace std;

double f1(double x) //原函数；
{
	double a;
	a = x * x * x / 3 - x;
	return a;
}

double f2(double x) //导函数；
{
	double b;
	b = x * x - 1;
	return b;
}

int f3(double x0) //求最大迭代区间；
{
	int a, flag = 0;
	double x1;
	while (flag == 0)
	{
		x1 = x0 - f1(x0) / f2(x0);
		if (x1 == x0) flag = 1;
		else x0 = x1;
	}
	if (x0 == 0.) a = 1;
	else a = 0;
	return a;
}

int main()
{
	double xnew, xold, e, x0 = 0.;
    e = 0.0000000005;

//	cout << "Please input the precision e: " << endl;
//	cin >> e;
	cout << "Please input the xold: " << endl;
	cin >> xold;
	int i = 0;
	xnew = xold - (f1(xold) / f2(xold));
	cout << "\t" << "i" << "    " << "x" << endl;
	while (fabs(xnew - xold) >= e)
	{
		xold = xnew;
		xnew = xold - (f1(xold) / f2(xold));
	i ++;
		cout << "\t" << i << "    " << setiosflags(ios::fixed) << setprecision(6) << xnew << endl;
	}

	cout << "The The root of equation x is: " << setprecision(7) << xnew << endl;

	while (f3(x0) == 1){ x0 += h; }
	cout << "The maximum deltal of x = 0 is " << setprecision(6) << x0 << endl;

	return 0;
}
