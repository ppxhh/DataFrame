#include <stdio.h>
#include <string.h>
#include <math.h>
#include <Windows.h>

double miu_deduce(double G, double Tb, double Q_f, double Q_p, double Q_s, double Pb, double P1)
{
	double Ps = 4.1;
	double Ts = 293;
	double row_s = 68.9884;
	double row_c = 1229.96;
	double row_b;

	row_b = Pb * 273.15 * 1.784 / (0.10133 * Tb);

	double miu;
	miu = G / ((Q_f + Q_p + Q_s) * (Ps / Pb) * (sqrt(row_s * Pb * Ts / (row_b * Ps * Tb))) - (P1 * G / Pb / row_c));
	return miu;
}

int main()
{
    FILE *fp = NULL;  
    char *line,*record;  
    char buffer[1024];
	
	double a[1000], b[1000], c[1000], d[1000], e[1000], f[1000];
	int k = 0;
	int flag = 1;

	char filename[100];// = "data+1515493093.csv";
//	printf("请输入工作表文件名(不加.csv后缀): \n");

//	scanf("%s", filename);
	
	while( flag != 0)
	{

		printf("请输入工作表文件名(不加.csv后缀): \n");

		scanf("%s", filename);

	//	strcat("data+", filename);

	
		strcat(filename,".csv");

		if ((fp = fopen(filename, "at+")) != NULL) {   
        char delims[] = ",";  
        char *result = NULL;  
        int j = 0;
		int nouse;
        while ((line = fgets(buffer, sizeof(buffer), fp))!=NULL)//当没有读取到文件末尾时循环继续  
        {  
            record = strtok(line, ",");  
            while (record != NULL)//读取每一行的数据  
            {  
				if (k >= 1 && j >= 1)
				{
					double num;
				    num = atof(record);
				    if (j == 1)
						a[k-1] = num;
				    else if (j == 2)
					    b[k-1] = num;
				    else if (j == 3)
					    c[k-1] = num;
					else if (j == 4)
						d[k-1] = num;
					else if (j == 5)
						e[k-1] = num;
					else if (j == 6)
						f[k-1] = num;
					else
						nouse = 0;
				}
                record = strtok(NULL, ",");  
                j++;  
            }
            //printf("\n");  
            j = 0;
			k ++;
        }  
        fclose(fp);  
        fp = NULL;  
    }

	int ll;

	double sum_a = 0.0, sum_b = 0.0, sum_c = 0.0, sum_d = 0.0, sum_e = 0.0, sum_f = 0.0;
//	printf("The data list is : \n");
	for (ll = 0; ll < k-1; ll ++)
	{
	//	printf("%lf %lf %lf %lf %lf %lf\n", a[ll],b[ll],c[ll],d[ll],e[ll],f[ll]);
		sum_a += a[ll];
		sum_b += b[ll];
		sum_c += c[ll];
		sum_d += d[ll];
		sum_e += e[ll];
		sum_f += f[ll];
	}

	double average_a, average_b, average_c, average_d, average_e, average_f;
	average_a = sum_a / (k - 1);
	average_b = sum_b / (k - 1);
	average_c = sum_c / (k - 1);
	average_d = sum_d / (k - 1);
	average_e = sum_e / (k - 1);
	average_f = sum_f / (k - 1);

	printf("各项平均值为: \n");
	printf("P1/Bar\t         P2/Bar\t         M/KG\t         F1/m3/h\t F2/m3/h\t F3/m3/h\n");
	printf("%lf\t %lf\t %lf\t %lf\t %lf\t %lf\t\n", average_a, average_b, average_c, average_d, average_e, average_f);

	double G, TB, Tb, Pb = average_a;
	printf("请输入质量流率G(kg/h): \n");
	scanf("%lf", &G);
	printf("请输入质量流率缓冲罐的气体温度T(℃): \n");
	scanf("%lf", &Tb);

	TB = Tb + 273.0;

	double result;
	double P1 = average_b;
	result = miu_deduce(G, TB, average_d, average_e, average_f, Pb, P1);

	printf("固气比μ =  %lf\n", result);
	}

	system("pause");
	return 0;
}
