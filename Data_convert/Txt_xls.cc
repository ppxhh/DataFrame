#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cstdio>

using namespace std;

int main()
{
	FILE *fp1, *fp2;
	char str[80];
	char *p;
	p = str;
	double a[540];
	double *q;
	q = a;
	int name[9] = { 0, 1, 2, 3, 4, 5, 6, 7, 8};  

	if ((fp2 = fopen("Outputdata.xls", "w")) == NULL)
		cout << "errors!" << endl;
	if ((fp1 = fopen("data.txt", "r")) == NULL)
		cout << "errors!" << endl;
	cout << "====read datas from data.txt====" << endl;
	int i, j;
	for (i = 0; i < 60; i++)
	{
		fscanf(fp1, "%s%lf", p ++, q++);
		fscanf(fp1, "%lf", q++);
		fscanf(fp1, "%lf", q++);
		fscanf(fp1, "%lf", q++);
		fscanf(fp1, "%lf", q++);
		fscanf(fp1, "%lf", q++);
		fscanf(fp1, "%lf", q++);
		fscanf(fp1, "%lf", q++);
		fscanf(fp1, "%lf", q++);
	}
	fclose(fp1);
	cout << "==== End read datas from data.txt====" << endl;
	//cout << str << endl;
	fprintf(fp2, "0 = time; 1-8 = channel1-8.\n");
	for (j = 0; j < 9; j++){
		fprintf(fp2, "%d\t", name[j]);
	}
	fprintf(fp2, "\n");
	for (i = 0; i < 60; i++){
		for (j = 0; j < 9; j++){
			fprintf(fp2, "%lf\t", a[i * 9 + j]);
		}
		fprintf(fp2, "\n");
	}
	fclose(fp2);

	return 0;
}
