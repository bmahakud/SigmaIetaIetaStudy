#include<iostream>
#include "TStyle.h"

using namespace std;

class PlotHisto{

public:

PlotHisto();

void drawLegend(TH1F *h_1=0,TH1F *h_2=0,std::string H1R="",std::string H2R="");
void plotHist(TH1F *h1=0,TH1F *h2=0,TCanvas *c=0,std::string Region="",std::string h1R="",std::string h2R="",std::string sampleName="");

void plotStack(TH1F *h1=0,TH1F *h2=0,TCanvas *c=0,std::string Xtitle="");

double Pfrac(TH1F *h1=0,TH1F *h2=0);
double PfracErr(TH1F *h1=0,TH1F *h2=0);

double NPfrac(TH1F *h1=0,TH1F *h2=0);
double NPfracErr(TH1F *h1=0,TH1F *h2=0);


};


PlotHisto::PlotHisto(){


}
//////////////////////////////////////
void PlotHisto::drawLegend(TH1F *h_1=0,TH1F *h_2=0,std::string H1R="",std::string H2R=""){

char h1L[100];
char h2L[100];
  
const char *h1_L;
const char *h2_L;
h1_L=H1R.c_str();
h2_L=H2R.c_str();

sprintf(h1L,"%s",h1_L);
sprintf(h2L,"%s",h2_L);

TLegend *leg=new TLegend(0.4582943,0.7051483,0.6025753,0.9049564,NULL,"brNDC");
leg->SetTextFont(62);
leg->SetLineColor(1);
leg->SetLineStyle(1);
leg->SetLineWidth(3);
leg->SetFillColor(0);
leg->SetFillStyle(1001);
leg->SetShadowColor(0);
leg->SetDrawOption(0);
leg->SetBorderSize(0);
leg->SetTextSize(0.03);


leg->AddEntry(h_1,h1L,"P");
leg->AddEntry(h_2,h2L,"P");

//c->cd(
leg->Draw();




}


///////////////////////////////////
void PlotHisto::plotHist(TH1F *h1,TH1F *h2,TCanvas *c,std::string Region="",std::string h1R="",std::string h2R="",std::string sampleName=""){



char h1L[100];
char h2L[100];

char region[100];
char PlotName[100];  

char Ratio[100];
const char *h1_L;
const char *h2_L;
const char *Rgn;

std::string plotstring=sampleName+"_"+Region+"_"+h1R+"_"+h2R+"_";

const char *plotname;

plotname=plotstring.c_str();


h1_L=h1R.c_str();
h2_L=h2R.c_str();
Rgn=Region.c_str();

sprintf(h1L,"%s",h1_L);
sprintf(h2L,"%s",h2_L);  

sprintf(Ratio,"%s/%s",h1_L,h2_L);
sprintf(region,"%s",Rgn);




TPaveText *tpav_txt = new TPaveText(0.23043478,0.4148342,0.6652174,0.8010471,"brNDC");

tpav_txt->SetBorderSize(0);
tpav_txt->SetFillStyle(0);
tpav_txt->SetTextAlign(11);
tpav_txt->SetTextFont(42);
tpav_txt->SetTextSize(0.04);
//tpav_txt->AddText("#gamma+ Jets");
tpav_txt->AddText("QCD");
tpav_txt->AddText("HT >500");
tpav_txt->AddText("#gamma p_{T} > 100 ");
tpav_txt->AddText("NJets >=4");
tpav_txt->AddText("MHT>200");
tpav_txt->AddText("w/  I^{#gamma},I^{n}");
tpav_txt->AddText("#Delta #Phi (0.5,0.5,0.3)");
tpav_txt->AddText(region);



c=new TCanvas("MyCanvas","MyCanvas",600,700);
TPad *pad1 = new TPad("pad1", "pad1", 0, 0.3, 1, 1.0);
   pad1->SetBottomMargin(0); // Upperand lower plot are joined
   //pad1->SetGridy();         // Vertical grid
   pad1->Draw();             // Draw the upper pad: pad1
   pad1->cd();               // pad1 becomes the current pad
  // h1->SetStats(0);          // No statistics on upper plot
   //h1->Draw();               // Draw h1
   //h2->Draw("same");         // Draw h2 on top of h1



h1->GetYaxis()->SetTitle("Events");
//h1->GetXaxis()->SetTitle("#sigma_{i#etai#eta}");
//h1->SetLineColor(1);
//h1->SetFillColor(2);
//h1->SetLineWidth(2);
//h1->SetLineStyle(2);
//h1->SetMarkerStyle(25);
//h2->SetLineColor(2);
//h2->SetLineWidth(2);
//h2->SetFillColor(2);
//h2->SetLineStyle(2);
//h2->SetMarkerStyle(8);
h2->Sumw2();
h2->Scale((1/h2->Integral())*h1->Integral());
h1->GetYaxis()->SetRangeUser( 0. , max( h1->GetMaximum() , h2->GetMaximum() ) * 3.5 );

//c->cd();

h1->Draw("hist ");
h1->Draw("E1 SAME");
//h2->Draw("hist ");
h2->Draw("P,E1 SAME");
tpav_txt->Draw();
drawLegend(h1,h2,h1R,h2R);

TGaxis *axis = new TGaxis( -5, 20, -5, 220, 20,220,510,"");
   axis->SetLabelFont(43); // Absolute font size in pixel (precision 3)
   axis->SetLabelSize(15);
   axis->Draw();


c->cd();

 TPad *pad2 = new TPad("pad2", "pad2", 0, 0.05, 1, 0.3);
   pad2->SetTopMargin(0);
   pad2->SetBottomMargin(0.2);
   pad2->SetGridy(); // vertical grid
   pad2->Draw();
   pad2->cd();       // pad2 becomes the current pad

   // Define the ratio plot
   TH1F *h3 = (TH1F*)h1->Clone("h3");
   h3->SetLineColor(kBlack);
   h3->SetMinimum(-1);  // Define Y ..
   h3->SetMaximum(3); // .. range
   h3->Sumw2();
   h3->SetStats(0);      // No statistics on lower plot
   h3->Divide(h2);
   h3->SetMarkerStyle(21);
   h3->Draw("ep");       // Draw the r


   // h1 settings
   h1->SetLineColor(kBlue);
   h1->SetMarkerStyle(25);
   h1->SetMarkerColor(kBlue);
   h1->SetLineWidth(2);

   // Y axis h1 plot settings
   h1->GetYaxis()->SetTitleSize(20);
   h1->GetYaxis()->SetTitleFont(43);
   h1->GetYaxis()->SetTitleOffset(1.55);

   // h2 settings
   h2->SetLineColor(kRed);
   h2->SetLineWidth(2);
   h2->SetMarkerStyle(8);
   h2->SetMarkerColor(kRed);

   // Ratio plot (h3) settings
   h3->GetXaxis()->SetTitle("#sigma_{i#eta i#eta}"); // Remove the ratio title

   // Y axis ratio plot settings
   h3->GetYaxis()->SetTitle(Ratio);
   h3->GetYaxis()->SetNdivisions(505);

   h3->GetYaxis()->SetTitleSize(20);
   h3->GetYaxis()->SetTitleFont(43);
   h3->GetYaxis()->SetTitleOffset(1.55);
   h3->GetYaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
   h3->GetYaxis()->SetLabelSize(15);

   // X axis ratio plot settings
   h3->GetXaxis()->SetTitleSize(20);
   h3->GetXaxis()->SetTitleFont(43);
   h3->GetXaxis()->SetTitleOffset(3.);
   h3->GetXaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
   h3->GetXaxis()->SetLabelSize(15);








char pName[100];

sprintf(pName,"%s_Baseline.png",plotname);
c->SaveAs(pName);
sprintf(pName,"%s_Baseline.gif",plotname);
c->SaveAs(pName);
sprintf(pName,"%s_Baseline.pdf",plotname);
c->SaveAs(pName);


}


void PlotHisto::plotStack(TH1F *h1,TH1F *h2,TCanvas *c,std::string Xtitle=""){


TLegend *leg=new TLegend(0.4582943,0.7051483,0.6025753,0.9049564,NULL,"brNDC");
leg->SetTextFont(62);
leg->SetLineColor(1);
leg->SetLineStyle(1);
leg->SetLineWidth(3);
leg->SetFillColor(0);
leg->SetFillStyle(1001);
leg->SetShadowColor(0);
leg->SetDrawOption(0);
leg->SetBorderSize(0);
leg->SetTextSize(0.03);

char XTitle[100];

const char *xTitle;
xTitle=Xtitle.c_str();
sprintf(XTitle,"%s",xTitle);


THStack *hs = new THStack("hs","Stacked 1D histograms");

h1->SetLineColor(kRed);
h1->SetLineWidth(2);
h1->GetYaxis()->SetTitle("Events");
h1->GetXaxis()->SetTitle(XTitle);
h1->SetMinimum(0.01);
h1->SetMarkerStyle(25);
h1->SetMarkerColor(kRed);

h2->SetLineWidth(2);
h2->SetLineColor(kBlue);
h2->GetYaxis()->SetTitle("Events");
h2->GetXaxis()->SetTitle(XTitle);
h2->SetMinimum(0.01);
h2->SetMarkerStyle(8);
h2->SetMarkerColor(kBlue);

h1->GetYaxis()->SetRangeUser( 0.01 , max( h1->GetMaximum() , h2->GetMaximum() ) * 25 );
//hs->Add(h1);
//hs->Add(h2);

leg->AddEntry(h1,"#gamma +Jets,Prompt,","P");
leg->AddEntry(h2,"QCD,NonPrompt,","P");


c->SetLogy(); 
c->cd();

h1->Draw("hist ");
h1->Draw("E1 SAME");
h2->Draw("hist SAME");
h2->Draw("P,E1 SAME");


leg->Draw();
char PlotName[100];
sprintf(PlotName,"%s_.png",xTitle);
c->SaveAs(PlotName);
sprintf(PlotName,"%s_.gif",xTitle);
c->SaveAs(PlotName);

sprintf(PlotName,"%s_.pdf",xTitle);
c->SaveAs(PlotName);

}


double PlotHisto::Pfrac(TH1F *h1=0,TH1F *h2=0){

double frac;

frac=h1->Integral()/(h1->Integral()+h2->Integral());

return frac;
}


double PlotHisto::PfracErr(TH1F *h1=0,TH1F *h2=0){

double frac;
double x=h1->Integral();
double y=h2->Integral();
double xErr=0;
double yErr=0;
int xMaxBin=h1->GetSize()-2;
int yMaxBin=h2->GetSize()-2;

frac=x/(x+y);

h1->IntegralAndError(0,xMaxBin,xErr);
h2->IntegralAndError(0,yMaxBin,yErr);
double Err=(1/((x+y)*(x+y)))*sqrt((y*y*xErr*xErr)+(x*x*yErr*yErr));

return Err;

}



double PlotHisto::NPfrac(TH1F *h1=0,TH1F *h2=0){
double frac;

frac=h2->Integral()/(h1->Integral()+h2->Integral());

return frac;

}

double PlotHisto::NPfracErr(TH1F *h1=0,TH1F *h2=0){


double frac;
double x=h1->Integral();
double y=h2->Integral();
double xErr=0;
double yErr=0;
int xMaxBin=h1->GetSize()-2;
int yMaxBin=h2->GetSize()-2;

frac=x/(x+y);

h1->IntegralAndError(0,xMaxBin,xErr);
h2->IntegralAndError(0,yMaxBin,yErr);

double Err=(1/((x+y)*(x+y)))*sqrt((y*y*xErr*xErr)+(x*x*yErr*yErr));

return Err;


}





