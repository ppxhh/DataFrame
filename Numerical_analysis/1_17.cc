#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

int main()
{
    long int N  = 0;
    float Sn1 = 0.,Sn2 = 0.;
    cout << "Please input the number N:" << endl;
    cin >> N;
    float SN;
    SN = (1.0 / 2.0) * (3.0 / 2.0 - 1.0 / N - 1.0 / (N + 1.0 ));
    cout << "准确值SN为:" << setprecision(6) << SN << endl;

    for (long int i = 2; i <= N; i ++)  {   Sn1 = Sn1 + 1.0 / (i * i - 1);    }
    for (long int i = N; i >= 2; i --)   {	Sn2 = Sn2 + 1.0 / (i * i - 1);    }
    cout << "从大到小的顺序累加得Sn1为: Sn1 = " << setprecision(6) << Sn1 << endl;
    cout << "从小到大的顺序累加得Sn2为: Sn2 = " << setprecision(6) << Sn2 << endl;

    float e1 = SN - Sn1;
    float e2 = SN - Sn2;
    float er1 = e1 / Sn1;
    float er2 = e2 / Sn2;

    cout << "从大到小的顺序累加的绝对误差为: e1 = " << setprecision(6) << fabs(e1) << endl;
    cout << "从大到小的顺序累加的相对误差为: er1 = " << setprecision(6) << fabs(er1) << endl;
    cout << "从小到大的顺序累加的绝对误差为: e2 = " << setprecision(6) << fabs(e2) << endl;
    cout << "从小到大的顺序累加的相对误差为: er2 = " << setprecision(6) << fabs(er2) << endl;
   
   return 0;
}
