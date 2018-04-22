#include <stdio.h>
#include <string.h>
#include <Windows.h>
#include <iostream>

using namespace std;

#define N 3500  //The number of data, if over 3500, please change

void Filter(double *t, double *M, double *M_new, double *m_new){
	
	//First step: Cut top values and bottom values;
	for (int j = 0; j < N; j ++)
	{
		for (int i = 1; i < N - 1; i ++){
			if (M[i] > M[i - 1] && M[i] > M[i + 1]){
				M[i] = (M[i - 1] + M[i + 1]) / 2;
			}
		}
	}
	for (int j = 0; j < N; j ++)
	{
		for (int i = 1; i < N - 1; i ++){
			if (M[i] < M[i - 1] && M[i] < M[i + 1]){
				M[i] = (M[i - 1] + M[i + 1]) / 2;
			}
		}
	}
		
	//Sencond step: average of 10 elements, move step = 1;
	double sum_h, aver_h = 0.;
	for (int nu = 0; nu < 100; nu ++){
		for (int j = nu; j < N - 10 - nu; j ++){
			sum_h = 0.;
			for (int i = 0; i < 10; i ++){
				sum_h += M[i + j];		
			}
		aver_h = sum_h / 10;
		M_new[j] = aver_h;
		}
	}
	
	//Third step: flatten data;
	int a_n = 100;
	for (int px = 0; px < 3; px ++){
		for (int nu = 0; nu < 100; nu ++){
			for (int j = 0; j < N - a_n; j += a_n){
			sum_h = 0.;
			for (int i = 0; i < a_n; i ++){
				sum_h += M[i + j];		
			}
			aver_h = sum_h / a_n;		
			for (int ll = 0; ll < a_n; ll ++){
				if (M_new[j + ll] > aver_h)
					M_new[j + ll] = aver_h;
			}		
			}	
		}	
	}	
	
	a_n = 50;
	for (int j = 0; j < N - a_n; j += a_n){
		sum_h = 0.;
		for (int i = 0; i < a_n; i ++){
			sum_h += M[i + j];		
		}
		aver_h = sum_h / a_n;		
		for (int ll = 0; ll < a_n; ll ++){
			if (M_new[j + ll] > aver_h)
				M_new[j + ll] = aver_h;
	  	}
	}
	
	a_n = 100;
	for (int j = 0; j < N - a_n; j += a_n){
		sum_h = 0.;
		for (int i = 0; i < a_n; i ++){
			sum_h += M[i + j];		
		}
		aver_h = sum_h / a_n;		
		for (int ll = 0; ll < a_n; ll ++){
			if (M_new[j + ll] > aver_h)
				M_new[j + ll] = aver_h;
	  	}
	}	
	
	//Fourth step: remodeling top;
	for (int j = 0; j < 100; j ++)
	{
		for (int i = 1; i < N - 1; i ++){
			if ((M_new[i] - M_new[i - 1]) > 0.1 * M_new[i - 1]){
				M_new[i] = (M_new[i - 1] + M_new[i]) / 2;
			}
		}
	}
	
	//More step to flatten and cut top;
	/*
	int step = 100;
	for (int i = 0; i < N / step; i ++){
		double min = M_new[i * step];
		for (int j = 1 + i * step; j < i * step + step; j ++){
			if (min > M_new[j])
				min = M_new[j];
		}
		m_new[i] = min;
	}
	
	//Fifth step: Cut top again;
	a_n = 40;	
	for (int nu = 0; nu < 100; nu ++){
		for (int j = 0; j < N - a_n; j += a_n){
			sum_h = 0.;
			for (int i = 0; i < a_n; i ++){
				sum_h += M[i + j];		
			}
		aver_h = sum_h / a_n;		
		for (int ll = 0; ll < a_n; ll ++){
			M_new[j + ll] = aver_h;
		}
		}	
	}
		
	//Finally: Broken line change into curve;
	double K;
	for (int i = 20; i < N; i += 40){
		K = (M_new[i % 40 + 40] - M_new[i % 40]) / (40 * 0.05);
		for (int j = 0; j < 40; j ++)
		{
			M_new[i + j] = M_new[i] + K * 0.05 * j;
		}
	}*/
}

int main()
{
    FILE *fp = NULL;  
    char *line, *record;  
    char buffer[1024];
		
	double t[N], M[N], M_new[N], m_new[N / 24];
	int k = 0;

	//Input Filename;
	//char filename[100] = "ExpDat_AL2O3 2.csv";
	char filename[80];
	printf("Please input the filename: \n");
	scanf("%s", filename);
    strcat (filename, ".csv");
	
	char result[80] = "result_";
	strcat(result, filename);
	
	//Open .csv file;		
    if ((fp = fopen(filename, "at +")) != NULL)  
    {  
        char delims[] = ",";  
        char *result = NULL;  
        
		int nouse;
        while ((line = fgets(buffer, sizeof(buffer), fp))!=NULL) //If not over, go on loop; 
        {  
			int j = 0;
            record = strtok(line, ",");
            while (record != NULL)                               //read every row's data;  
            {  
				if (k >= 43 && j >= 5)
				{
					double num;
				    num = atof(record);
				    if (j == 5)
						t[k - 43] = num;
				    else if (j == 6)
					    M[k - 43] = num;
					else
						nouse = 0;
				}
                record = strtok(NULL, ",");  
                j ++;  
            }
            j = 0;
			k ++;
        }  
        fclose(fp);  
        fp = NULL;  
    }
    
    //The Filiter deal;
    Filter(t, M, M_new, m_new);

	for(int i = k - 143; i < k - 43; i ++){
		M_new[i] = M[i];
	}

	//Save data after Filter;
	fp = fopen(result, "w");
		if (fp == NULL) printf("Can not open this file, Exit.\n");
	
	for(int i = 0; i < k - 43; i ++)
	{	
		fprintf(fp, "%lf, %lf", t[i], M_new[i]);
		fprintf(fp, "\n");
	}	
	fclose(fp);
	
	cout << "The output file name is: " << result << endl;
	
	system("pause");
	return 0;
}
