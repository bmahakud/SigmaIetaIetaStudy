#include<iostream>
#include<vector>
#include "TH1.h"
#include "TH2.h"
#include "TGraph.h"
#include "TTree.h"
#include "TFile.h"
#include "TCanvas.h"
#include "TString.h"
#include "TDirectory.h"
#include "ReadTree.cc"
#include "PlotHisto.C"
#include "SetStyle.C"
void TeffPhotonPurity(){


    TStyle *gStyle = new TStyle("gStyle","Style for P-TDR");
    SetStyle st;
    st.SetPars(gStyle);
    PlotHisto pH;

    TH1F *hSRprompt[8];
    TH1F *hSRnonprompt[8];
    char hnameSRp[100];
    char hnameSRnp[100];
    for(int i=0;i<8;i++){
    sprintf(hnameSRp,"hSR%i",i);
    sprintf(hnameSRnp,"hSB%i",i);

    hSRprompt[i]=new TH1F(hnameSRp,hnameSRp,20,0.006,0.011);
    hSRprompt[i]->Sumw2();
    hSRnonprompt[i]=new TH1F(hnameSRnp,hnameSRnp,20,0.006,0.011);
    hSRnonprompt[i]->Sumw2();


   
         }

    TH1F *hPrompt=new TH1F("hPrompt","hPrompt",20,0.,1500);
    hPrompt->Sumw2();
    
    TH1F *hnonPrompt=new TH1F("hTotal","hTotal",20,0.0,1500);
    hnonPrompt->Sumw2();
  

    TChain* t1 = new TChain("SimpleTree");
    t1->Add("SignalGJets3.root");
    ReadTree read1(t1);

    
    TChain* t2 = new TChain("SimpleTree");
    t2->Add("QCD80toInf.root");
    ReadTree read2(t2);

    TEfficiency* pEff1 = new TEfficiency("eff1","my efficiency1;MHT;Prompt Fraction",3,0,1000);
    
    pEff1->SetUseWeightedEvents();


   bool Passed;


    int maxEvents1=t1->GetEntries();
    cout<<"maxEventsGJets: "<<maxEvents1<<endl;
    for(int i1=0;i1<maxEvents1;i1++){//GJets loop
    t1->GetEntry(i1);
    if(i1 % 1000000==0){cout<<"Event no GJets : "<<i1<<endl;}

   if(read1.nonPrompt !=1 && read1.BaseLine()==true && read1.evWeight<3000. && read1.SigmaIetaIeta < 0.0107 && read1.PGN==1 && read1.IchSR==1){//prompt 
   Passed=true;
   //look here for TEff filling for  prompt
   pEff1->FillWeighted(Passed,read1.evWeight,read1.MHT,0,0);

     


   hSRprompt[0]->Fill(read1.SigmaIetaIeta ,read1.evWeight);
   hPrompt->Fill(read1.MHT ,read1.evWeight);
  

   if(read1.NJetslow()==true){
   hSRprompt[1]->Fill(read1.SigmaIetaIeta ,read1.evWeight);
       }
   
   if(read1.NJetshigh()==true){
   hSRprompt[2]->Fill(read1.SigmaIetaIeta ,read1.evWeight);
   }
   
   if(read1.HTlow()==true){
   hSRprompt[3]->Fill(read1.SigmaIetaIeta ,read1.evWeight);
   }
   
   if(read1.HThigh()==true){
   hSRprompt[4]->Fill(read1.SigmaIetaIeta ,read1.evWeight);
   }
   
   if(read1.MHTlow()==true){
   hSRprompt[5]->Fill(read1.SigmaIetaIeta ,read1.evWeight);
   }

   if(read1.MHThigh()==true){
   hSRprompt[6]->Fill(read1.SigmaIetaIeta ,read1.evWeight);
   } 
   
   
   

   }//prompt


   }//GJets loop





   int maxEvents2=t2->GetEntries();
    cout<<"maxEventsQCD: "<<maxEvents2<<endl;
    for(int i2=0;i2<maxEvents2;i2++){//QCD loop
    t2->GetEntry(i2);
    if(i2 % 1000000==0){cout<<"Event no QCD : "<<i2<<endl;}

    if(read2.nonPrompt ==1 && read2.BaseLine()==true && read2.evWeight<3000. && read2.SigmaIetaIeta < 0.0107 && read2.PGN==1 && read2.IchSR==1){//non prompt 

   
   hSRnonprompt[0]->Fill(read2.SigmaIetaIeta ,read2.evWeight);
   
   Passed=false;

   //look here for TEff filling for non prompt
   pEff1->FillWeighted(Passed,read2.evWeight,read2.MHT,0,0);

   hnonPrompt->Fill(read2.MHT ,read2.evWeight);


   if(read2.NJetslow()==true){
   hSRnonprompt[1]->Fill(read2.SigmaIetaIeta ,read2.evWeight);
   }
   
   if(read2.NJetshigh()==true){
   hSRnonprompt[2]->Fill(read2.SigmaIetaIeta ,read2.evWeight);
   }


   if(read2.HTlow()==true){   
   hSRnonprompt[3]->Fill(read2.SigmaIetaIeta ,read2.evWeight);
   }
  
   if(read2.HThigh()==true){
   hSRnonprompt[4]->Fill(read2.SigmaIetaIeta ,read2.evWeight);
   }
   

   if(read2.MHTlow()==true){
   hSRnonprompt[5]->Fill(read2.SigmaIetaIeta ,read2.evWeight);
   }


   if(read2.MHThigh()==true){
   hSRnonprompt[6]->Fill(read2.SigmaIetaIeta ,read2.evWeight);
   }

   }//non prompt

   }//QCD loop



 
  TCanvas *c0=new TCanvas("c0","c0");
  c0->cd();
  hPrompt->SetLineColor(2);
  hnonPrompt->SetLineColor(3);
  hPrompt->Draw("hist E1");
  hnonPrompt->Draw("hist E1,SAME");

 
  cout<<"Prompt: "<<hSRprompt[0]->Integral()<<endl;
  cout<<"Non prompt: "<<hSRnonprompt[0]->Integral()<<endl;
  
  cout<<"Prompt MHT: "<<hPrompt->Integral()<<endl;
  cout<<"non Prompt MHT: "<<hnonPrompt->Integral()<<endl;

  cout<<"fraction from MHT: "<<hPrompt->Integral()/(hnonPrompt->Integral()+hPrompt->Integral())<<endl;

TCanvas *c1=new TCanvas("c1","c1");

  c1->cd();

  pEff1->Draw("AP");







}
