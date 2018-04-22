#include <iostream>
#include <math.h>
#include <stdio.h>

using namespace std;

typedef double Double_t;
typedef int Int_t;
#define pi 3.141593

int main(void)
{
	//Initialization of data;
	//The enter port;
	Double_t T1 = 282.0;                 //degree Celsius;
	Double_t H1 = 1239.3;                //kJ/kg;
	Double_t Row1 = 1 / 0.00128303;      //kg/m3;
	Double_t Cp1 = 4.869124;             //kJ/kg/K;
	
	//The Exit;
	Double_t T2 = 336.8;
	Double_t H2 = 1530.0;
	Double_t Row2 = 1 / 0.00148250;
	Double_t Cp2 = 5.303;
	
	//The flow;
	Double_t D0 = 1825 * 1000 / 3600;  //kg/s;
	Double_t Q0 = D0 * (H2 - H1);

	//Economizer;
	Double_t L = 220.0;              //m;
	Int_t n = 501; 
	Double_t D = 0.0508;           //m;
	Double_t d = D - 0.00789;
	Double_t Row_G = 7.93 * 1000;  //kg/m3;
	Double_t Cj = 0.46;           //KJ/kg/K;
	Double_t Mj = n * L * pi * Row_G * (D * D - d * d) / 4;  //kg ;
	Double_t V0 = L * pi * (d * d / 4) * n; //Flow volume;	
	Double_t M = V0 * Row1;       //Mass of flow;
	Double_t a2 = 1 * pi * D * L * n;     //Area of inpipe;
	Double_t Tj = T2 + 30;        //
	Double_t K = Q0 / pow(D0, 0.8) / (Tj - T2) / a2;

	Int_t N = 1000; 
	Double_t t[N];
	Double_t T2_T[N];
	Double_t Tj_T[N];
	Double_t T2_D[N];
	Double_t Tj_D[N];
	Double_t T2_Q[N];
	Double_t Tj_Q[N];
	
	Int_t i;
	t[0] = 0.0;
	T2_T[0] = T2;
	Tj_T[0] = T2 + 30.0;
	T2_D[0] = T2;
	Tj_D[0] = T2 + 30.0;
	T2_Q[0] = T2;
	Tj_Q[0] = T2 + 30.0;
	
	Double_t d_t = 2.0;
		
	for (i = 1; i < N; i ++)
	{
		t[i] = t[i - 1] + d_t;
		Tj_T[i] = Tj_T[i - 1] + d_t * (Q0 - K * a2 * (pow(D0, 0.8)) 
		* (Tj_T[i - 1] - T2_T[i - 1])) / Mj / Cj;
		T2_T[i] = T2_T[i - 1] + d_t * (K * a2 *(pow(D0, 0.8)) * (Tj_T
		[i - 1] - T2_T[i - 1]) - (D0) * Cp2 * (T2_T[i - 1] - T1 - 10)) / V0 / Row2 / Cp1;
		
		Tj_D[i] = Tj_D[i - 1] + d_t * (Q0 - K * a2 * (pow(1.1 * D0, 0.8)) 
		* (Tj_D[i - 1] - T2_D[i - 1])) / Mj / Cj;
		T2_D[i] = T2_D[i - 1] + d_t * (K * a2 *(pow(1.1 * D0, 0.8)) * (Tj_D
		[i - 1] - T2_D[i - 1]) - (1.1 * D0) * Cp2 * (T2_D[i - 1] - T1)) / V0 / Row2 / Cp1;
		
		Tj_Q[i] = Tj_Q[i - 1] + d_t * (1.05 * Q0 - K * a2 * (pow(D0, 0.8)) 
		* (Tj_Q[i - 1] - T2_Q[i - 1])) / Mj / Cj;
		T2_Q[i] = T2_Q[i - 1] + d_t * (K * a2 *(pow(D0, 0.8)) * (Tj_Q
		[i - 1] - T2_Q[i - 1]) - (D0) * Cp2 * (T2_Q[i - 1] - T1)) / V0 / Row2 / Cp2;
		
	}
	FILE *fp;
	fp = fopen("Guolu.bin", "w");
		if (fp == NULL) printf("Can not open this file, Exit.\n");
		
	for(i = 0; i < N; i ++)
	{
		fprintf(fp, "%lf %lf %lf %lf", t[i], T2_T[i], T2_D[i], T2_Q[i]);
		fprintf(fp, "\n");
	}	
	fclose(fp);
	
	/*
	TCanvas *c1 = new TCanvas("c1","The Graph trunk", 200, 10, 900, 700);
    c1->SetFillColor(0);
    gr = new TGraph(N, t, T2_Q);
    gr->SetLineColor(4);
    gr->SetLineWidth(2);
    gr->SetMarkerColor(4);
    gr->SetMarkerStyle(21);
    gr->SetMarkerSize(1);
    gr->SetTitle("Guolu");
    gr->GetXaxis()->SetTitle("Time/s");
    gr->GetYaxis()->SetTitleOffset(1.2);
    gr->GetYaxis()->SetTitle("T2/C ");
    gr->GetXaxis()->CenterTitle();
    gr->GetYaxis()->CenterTitle();
    gr->SetMinimum(336.);
    gr->SetMaximum(342.);
    gr->Draw("ACP");   
    TLegend *legend = new TLegend(.75,.80,.95,.95);
    legend->AddEntry(gr, "T2 change over time", "pl");
    legend->SetFillColor(0);
    legend->SetBorderSize(1);
    legend->Draw();*/
		
	return 0;
}
