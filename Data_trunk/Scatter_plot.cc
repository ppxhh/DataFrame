/*********************************
**Write by Zengxin in 2018/04/15**
**Use to plot a Graph.        **
*********************************/

#include <iostream>
#include <math.h>
#include <stdio.h>

#include "TFile.h"
#include "TLegend.h"
#include "TH1F.h"
#include "TCanvas.h"
#include "TGraph.h"

int Scatter_plot()
{
	//Please input the number of data and data array;
    const Int_t N = 15; //The number of data;
    Double_t x[N];      //x data;
    Double_t y1[N];     //y1 data;
    Double_t y2[N];     //y2 data;
    Double_t y3[N];     //y3 data; If you must deal with more data, please add yn data by yourself;

	//Open a file;
    FILE *fp;
    fp = fopen("Guolu.txt", "r+");
    if (fp == NULL) 
        printf("Can not open this file, Exit.\n");

	//Print the data;
    Int_t i;
    for (i = 0; i < N; i ++)
    {
        fscanf(fp, "%lf %lf %lf %lf", &x[i], &y1[i], &y2[i], &y3[i]);
        printf("%lf\t%lf\t%lf\t%lf\n", x[i], y1[i], y2[i], y3[i]);
    }
    fclose(fp);

	//New a 900 * 700 Graph backGr0ound;
    TCanvas *c1 = new TCanvas("c1","The Graph trunk", 200, 10, 900, 700);
    c1 -> SetFillColor(0);                              //Set the color of background;
    //c1->SetGrid();                                    //If plot the Grid, please cut the //;

    Gr0 = new TGraph(N, x, y1);                         //New a TGraph object;
    Gr0 -> SetLineColor(4);                             //Set color of line;
    Gr0 -> SetLineWidth(2);                             //Set width of line;

    Gr0 -> SetMarkerColor(4);                           //Set color of marker;
    Gr0 -> SetMarkerStyle(21);                          //Set style of marker;
    Gr0 -> SetMarkerSize(1);                            //Set size of marker;
 
    //Gr0->SetTitle("The Graph trunk");                 //Please change this title;
	
    Gr0 -> GetXaxis() -> SetTitle("X title");           //x title;
    Gr0 -> GetXaxis() -> SetTitleOffset(1.);            //The distabce of x-title with x-axis;
    Gr0 -> GetYaxis() -> SetTitle("Y title");           //y title;
	Gr0 -> GetYaxis() -> SetTitleOffset(1.);            //The distabce of y-title with y-axis;
    Gr0 -> GetXaxis() -> CenterTitle();                 //Set the x-title center;
    Gr0 -> GetYaxis() -> CenterTitle();                 //Set the y-title center

    //Gr0 -> SetMinimum(0.);                            //Set min-y;
    //Gr0 -> SetMaximum(5.);                            //Set max-y;

    Gr0 -> Draw("ACP");                                 //ACP mean carve, ,,,

    Gr1 = new TGraph(N, x, y2);                          
    Gr1 -> SetLineColor(2);
    Gr1 -> SetLineWidth(2);

    Gr1 -> SetMarkerColor(2);
    Gr1 -> SetMarkerStyle(24);
    Gr1 -> SetMarkerSize(1);

    Gr1 -> Draw("CP");

    TLegend *legend = new TLegend(.75, .80, .95, .95);  //New a TLegend object;
    legend -> AddEntry(Gr0, "ppx1", "pl");              //Set line name;
    legend -> AddEntry(Gr1, "pps2", "pl"); 
    legend -> SetFillColor(0);                          //Set fill color;
    legend -> SetBorderSize(1);                         //Set box line Size;
    legend -> Draw();                                   //Draw the legend;

    return 0;
}

