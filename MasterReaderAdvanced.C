#include <iostream>
#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include "TLorentzVector.h"
#include <vector>
#include "TTree.h"
#include "ClassReadTree.cc"
#include "TString.h"
#include "TH1F.h"
using namespace std;


void MasterReaderAdvanced(TString InputFile="",TString OutputFile="", std::string Weight=""){
 

    
    if(InputFile=="" || OutputFile=="" || Weight==""){
    cout<<"You are missing input arguments,you should put arguments before running ..."<<endl;

    }


    std::string SIetaFnNames[8]={"P_Ich_SR_PGN","P_Ich_SB_PGN","NP_Ich_SR_PGN","NP_Ich_SB_PGN","P_Ich_SR_NGN","P_Ich_SB_NGN","NP_Ich_SR_NGN","NP_Ich_SB_NGN"};


    std::string IchFnNames[8]={"P_SIeta_SR_PGN","P_SIeta_SB_PGN","NP_SIeta_SR_PGN","NP_SIeta_SB_PGN","P_SIeta_SR_NGN","P_SIeta_SB_NGN","NP_SIeta_SR_NGN","NP_SIeta_SB_NGN"};




    TFile *fall=new TFile(OutputFile,"RECREATE");


    TH1F  *h_SIeta[56];
    TH1F  *h_Ich[56];
  
    

   char histName_SIeta[100];
   char histName_Ich[100];    

    
    

    

   double rangeMinIch=0;
   double rangeMaxIch=20;
   int NoOfbinsIch=40;

   double rangeMinS=0;
   double rangeMaxS=0.05;
   int NoOfbinsS=100;
   




    for(int i=0;i<56;i++){//loop bins
    
    
    sprintf(histName_SIeta,"SIeta_%i_h",i);
    sprintf(histName_Ich,"IsoCh_%i_h",i);

    
    if(i % 4==0 || i % 4==1){//prompt
    h_SIeta[i]=new TH1F(histName_SIeta,histName_SIeta,40,0.006,0.012);
    h_Ich[i]=new TH1F(histName_Ich,histName_Ich,20,0,150);
   
    }//prompt

    if(i % 4==2 || i % 4 ==3){//non prompt
    h_SIeta[i]=new TH1F(histName_SIeta,histName_SIeta,12,0.005,0.025);
    h_Ich[i]=new TH1F(histName_Ich,histName_Ich,20,0,200);
    }//non prompt

    }//loop bins

    TH1F *hpromptS=new TH1F("hpromptS","hpromptS",80,0.006,0.025);
    TH1F *hnpromptS=new TH1F("hnpromptS","hnpromptS",80,0.006,0.025);






    TChain* t = new TChain("TreeMaker2/PreSelection");
    t->Add(InputFile);
    ClassReadTree read(t);
    for(int iEv=0;iEv < t->GetEntries();iEv++){//event loop 
	if( iEv % 500 == 0 ) cout << "event: " << iEv << endl;
        t->GetEntry(iEv);
	int photon=-1;
	float PhPt_p=0;
             //std::cout<<"photon size : "<<read.photonCands->size()<<std::endl;

            // for(int photon=0;photon<read.photonCands->size();photon++){//photon loop
               for(int iPh=0;iPh<read.photonCands->size();iPh++){//photon loop
             if(read.photonCands->at(iPh).Pt() > PhPt_p){
             PhPt_p=read.photonCands->at(iPh).Pt();
             photon=iPh;
             }
             }//photon loop
         //cout<<"photon size : "<<photon<read.photonCands->size()<<endl;
       //////////////////
     //  if(read.photonCands->at(photon).Pt() >100.  && read.photon_isEB->at(photon)==1){//Leading Pt Photon all photons
       if( photon !=-1 && read.photon_isEB->at(photon)==1){//Leading Pt Photon

       if(read.Prompt(photon)==true){     
       hpromptS->Fill(read.photon_sigmaIetaIeta->at(photon));
          }
       if(read.NonPrompt(photon)==true){
        hnpromptS->Fill(read.photon_sigmaIetaIeta->at(photon));    
          }
 
       if(read.P_Ich_SR_PGN(photon)==true){h_SIeta[0]->Fill(read.photon_sigmaIetaIeta->at(photon));}
       if(read.P_Ich_SB_PGN(photon)==true){h_SIeta[1]->Fill(read.photon_sigmaIetaIeta->at(photon));}
       if(read.NP_Ich_SR_PGN(photon)==true){h_SIeta[2]->Fill(read.photon_sigmaIetaIeta->at(photon));}
       if(read.NP_Ich_SB_PGN(photon)==true){h_SIeta[3]->Fill(read.photon_sigmaIetaIeta->at(photon));}
       if(read.P_Ich_SR_NGN(photon)==true){h_SIeta[4]->Fill(read.photon_sigmaIetaIeta->at(photon));}
       if(read.P_Ich_SB_NGN(photon)==true){h_SIeta[5]->Fill(read.photon_sigmaIetaIeta->at(photon));}
       if(read.NP_Ich_SR_NGN(photon)==true){h_SIeta[6]->Fill(read.photon_sigmaIetaIeta->at(photon));}
       if(read.NP_Ich_SB_NGN(photon)==true){h_SIeta[7]->Fill(read.photon_sigmaIetaIeta->at(photon));}

       if(read.NJetslow()==true){//low Njet
        
       if(read.P_Ich_SR_PGN(photon)==true){h_SIeta[8]->Fill(read.photon_sigmaIetaIeta->at(photon));}
       if(read.P_Ich_SB_PGN(photon)==true){h_SIeta[9]->Fill(read.photon_sigmaIetaIeta->at(photon));}
       if(read.NP_Ich_SR_PGN(photon)==true){h_SIeta[10]->Fill(read.photon_sigmaIetaIeta->at(photon));}
       if(read.NP_Ich_SB_PGN(photon)==true){h_SIeta[11]->Fill(read.photon_sigmaIetaIeta->at(photon));}
       if(read.P_Ich_SR_NGN(photon)==true){h_SIeta[12]->Fill(read.photon_sigmaIetaIeta->at(photon));}
       if(read.P_Ich_SB_NGN(photon)==true){h_SIeta[13]->Fill(read.photon_sigmaIetaIeta->at(photon));}
       if(read.NP_Ich_SR_NGN(photon)==true){h_SIeta[14]->Fill(read.photon_sigmaIetaIeta->at(photon));}
       if(read.NP_Ich_SB_NGN(photon)==true){h_SIeta[15]->Fill(read.photon_sigmaIetaIeta->at(photon));}


         }//low Njet

       if(read.NJetshigh()==true){//high Njet

       if(read.P_Ich_SR_PGN(photon)==true){h_SIeta[16]->Fill(read.photon_sigmaIetaIeta->at(photon));}
       if(read.P_Ich_SB_PGN(photon)==true){h_SIeta[17]->Fill(read.photon_sigmaIetaIeta->at(photon));}
       if(read.NP_Ich_SR_PGN(photon)==true){h_SIeta[18]->Fill(read.photon_sigmaIetaIeta->at(photon));}
       if(read.NP_Ich_SB_PGN(photon)==true){h_SIeta[19]->Fill(read.photon_sigmaIetaIeta->at(photon));}
       if(read.P_Ich_SR_NGN(photon)==true){h_SIeta[20]->Fill(read.photon_sigmaIetaIeta->at(photon));}
       if(read.P_Ich_SB_NGN(photon)==true){h_SIeta[21]->Fill(read.photon_sigmaIetaIeta->at(photon));}
       if(read.NP_Ich_SR_NGN(photon)==true){h_SIeta[22]->Fill(read.photon_sigmaIetaIeta->at(photon));}
       if(read.NP_Ich_SB_NGN(photon)==true){h_SIeta[23]->Fill(read.photon_sigmaIetaIeta->at(photon));}

         }//high Njet

        if(read.HTlow()==true){//low HT

       if(read.P_Ich_SR_PGN(photon)==true){h_SIeta[24]->Fill(read.photon_sigmaIetaIeta->at(photon));}
       if(read.P_Ich_SB_PGN(photon)==true){h_SIeta[25]->Fill(read.photon_sigmaIetaIeta->at(photon));}
       if(read.NP_Ich_SR_PGN(photon)==true){h_SIeta[26]->Fill(read.photon_sigmaIetaIeta->at(photon));}
       if(read.NP_Ich_SB_PGN(photon)==true){h_SIeta[27]->Fill(read.photon_sigmaIetaIeta->at(photon));}
       if(read.P_Ich_SR_NGN(photon)==true){h_SIeta[28]->Fill(read.photon_sigmaIetaIeta->at(photon));}
       if(read.P_Ich_SB_NGN(photon)==true){h_SIeta[29]->Fill(read.photon_sigmaIetaIeta->at(photon));}
       if(read.NP_Ich_SR_NGN(photon)==true){h_SIeta[30]->Fill(read.photon_sigmaIetaIeta->at(photon));}
       if(read.NP_Ich_SB_NGN(photon)==true){h_SIeta[31]->Fill(read.photon_sigmaIetaIeta->at(photon));}

         }//low HT

       if(read.HThigh()==true){//high HT
       if(read.P_Ich_SR_PGN(photon)==true){h_SIeta[32]->Fill(read.photon_sigmaIetaIeta->at(photon));}
       if(read.P_Ich_SB_PGN(photon)==true){h_SIeta[33]->Fill(read.photon_sigmaIetaIeta->at(photon));}
       if(read.NP_Ich_SR_PGN(photon)==true){h_SIeta[34]->Fill(read.photon_sigmaIetaIeta->at(photon));}
       if(read.NP_Ich_SB_PGN(photon)==true){h_SIeta[35]->Fill(read.photon_sigmaIetaIeta->at(photon));}
       if(read.P_Ich_SR_NGN(photon)==true){h_SIeta[36]->Fill(read.photon_sigmaIetaIeta->at(photon));}
       if(read.P_Ich_SB_NGN(photon)==true){h_SIeta[37]->Fill(read.photon_sigmaIetaIeta->at(photon));}
       if(read.NP_Ich_SR_NGN(photon)==true){h_SIeta[38]->Fill(read.photon_sigmaIetaIeta->at(photon));}
       if(read.NP_Ich_SB_NGN(photon)==true){h_SIeta[39]->Fill(read.photon_sigmaIetaIeta->at(photon));}


         }//high HT


        if(read.MHTlow()==true){//low MHT
       if(read.P_Ich_SR_PGN(photon)==true){h_SIeta[40]->Fill(read.photon_sigmaIetaIeta->at(photon));}
       if(read.P_Ich_SB_PGN(photon)==true){h_SIeta[41]->Fill(read.photon_sigmaIetaIeta->at(photon));}
       if(read.NP_Ich_SR_PGN(photon)==true){h_SIeta[42]->Fill(read.photon_sigmaIetaIeta->at(photon));}
       if(read.NP_Ich_SB_PGN(photon)==true){h_SIeta[43]->Fill(read.photon_sigmaIetaIeta->at(photon));}
       if(read.P_Ich_SR_NGN(photon)==true){h_SIeta[44]->Fill(read.photon_sigmaIetaIeta->at(photon));}
       if(read.P_Ich_SB_NGN(photon)==true){h_SIeta[45]->Fill(read.photon_sigmaIetaIeta->at(photon));}
       if(read.NP_Ich_SR_NGN(photon)==true){h_SIeta[46]->Fill(read.photon_sigmaIetaIeta->at(photon));}
       if(read.NP_Ich_SB_NGN(photon)==true){h_SIeta[47]->Fill(read.photon_sigmaIetaIeta->at(photon));}
 

         }//low MHT

       if(read.MHThigh()==true){//high MHT
        if(read.P_Ich_SR_PGN(photon)==true){h_SIeta[48]->Fill(read.photon_sigmaIetaIeta->at(photon));}
       if(read.P_Ich_SB_PGN(photon)==true){h_SIeta[49]->Fill(read.photon_sigmaIetaIeta->at(photon));}
       if(read.NP_Ich_SR_PGN(photon)==true){h_SIeta[50]->Fill(read.photon_sigmaIetaIeta->at(photon));}
       if(read.NP_Ich_SB_PGN(photon)==true){h_SIeta[51]->Fill(read.photon_sigmaIetaIeta->at(photon));}
       if(read.P_Ich_SR_NGN(photon)==true){h_SIeta[52]->Fill(read.photon_sigmaIetaIeta->at(photon));}
       if(read.P_Ich_SB_NGN(photon)==true){h_SIeta[53]->Fill(read.photon_sigmaIetaIeta->at(photon));}
       if(read.NP_Ich_SR_NGN(photon)==true){h_SIeta[54]->Fill(read.photon_sigmaIetaIeta->at(photon));}
       if(read.NP_Ich_SB_NGN(photon)==true){h_SIeta[55]->Fill(read.photon_sigmaIetaIeta->at(photon));}


         }//high MHT

       /////////////////////////starting Ich histos

        if(read.P_SIeta_SR_PGN(photon)==true){h_Ich[0]->Fill(read.photon_pfChargedIsoRhoCorr->at(photon));}
       if(read.P_SIeta_SB_PGN(photon)==true){h_Ich[1]->Fill(read.photon_pfChargedIsoRhoCorr->at(photon));}
       if(read.NP_SIeta_SR_PGN(photon)==true){h_Ich[2]->Fill(read.photon_pfChargedIsoRhoCorr->at(photon));}
       if(read.NP_SIeta_SB_PGN(photon)==true){h_Ich[3]->Fill(read.photon_pfChargedIsoRhoCorr->at(photon));}
       if(read.P_SIeta_SR_NGN(photon)==true){h_Ich[4]->Fill(read.photon_pfChargedIsoRhoCorr->at(photon));}
       if(read.P_SIeta_SB_NGN(photon)==true){h_Ich[5]->Fill(read.photon_pfChargedIsoRhoCorr->at(photon));}
       if(read.NP_SIeta_SR_NGN(photon)==true){h_Ich[6]->Fill(read.photon_pfChargedIsoRhoCorr->at(photon));}
       if(read.NP_SIeta_SB_NGN(photon)==true){h_Ich[7]->Fill(read.photon_pfChargedIsoRhoCorr->at(photon));}

       if(read.NJetslow()==true){//low Njet
        
       if(read.P_SIeta_SR_PGN(photon)==true){h_Ich[8]->Fill(read.photon_pfChargedIsoRhoCorr->at(photon));}
       if(read.P_SIeta_SB_PGN(photon)==true){h_Ich[9]->Fill(read.photon_pfChargedIsoRhoCorr->at(photon));}
       if(read.NP_SIeta_SR_PGN(photon)==true){h_Ich[10]->Fill(read.photon_pfChargedIsoRhoCorr->at(photon));}
       if(read.NP_SIeta_SB_PGN(photon)==true){h_Ich[11]->Fill(read.photon_pfChargedIsoRhoCorr->at(photon));}
       if(read.P_SIeta_SR_NGN(photon)==true){h_Ich[12]->Fill(read.photon_pfChargedIsoRhoCorr->at(photon));}
       if(read.P_SIeta_SB_NGN(photon)==true){h_Ich[13]->Fill(read.photon_pfChargedIsoRhoCorr->at(photon));}
       if(read.NP_SIeta_SR_NGN(photon)==true){h_Ich[14]->Fill(read.photon_pfChargedIsoRhoCorr->at(photon));}
       if(read.NP_SIeta_SB_NGN(photon)==true){h_Ich[15]->Fill(read.photon_pfChargedIsoRhoCorr->at(photon));}


         }//low Njet

       if(read.NJetshigh()==true){//high Njet

       if(read.P_SIeta_SR_PGN(photon)==true){h_Ich[16]->Fill(read.photon_pfChargedIsoRhoCorr->at(photon));}
       if(read.P_SIeta_SB_PGN(photon)==true){h_Ich[17]->Fill(read.photon_pfChargedIsoRhoCorr->at(photon));}
       if(read.NP_SIeta_SR_PGN(photon)==true){h_Ich[18]->Fill(read.photon_pfChargedIsoRhoCorr->at(photon));}
       if(read.NP_SIeta_SB_PGN(photon)==true){h_Ich[19]->Fill(read.photon_pfChargedIsoRhoCorr->at(photon));}
       if(read.P_SIeta_SR_NGN(photon)==true){h_Ich[20]->Fill(read.photon_pfChargedIsoRhoCorr->at(photon));}
       if(read.P_SIeta_SB_NGN(photon)==true){h_Ich[21]->Fill(read.photon_pfChargedIsoRhoCorr->at(photon));}
       if(read.NP_SIeta_SR_NGN(photon)==true){h_Ich[22]->Fill(read.photon_pfChargedIsoRhoCorr->at(photon));}
       if(read.NP_SIeta_SB_NGN(photon)==true){h_Ich[23]->Fill(read.photon_pfChargedIsoRhoCorr->at(photon));}

         }//high Njet

        if(read.HTlow()==true){//low HT

       if(read.P_SIeta_SR_PGN(photon)==true){h_Ich[24]->Fill(read.photon_pfChargedIsoRhoCorr->at(photon));}
       if(read.P_SIeta_SB_PGN(photon)==true){h_Ich[25]->Fill(read.photon_pfChargedIsoRhoCorr->at(photon));}
       if(read.NP_SIeta_SR_PGN(photon)==true){h_Ich[26]->Fill(read.photon_pfChargedIsoRhoCorr->at(photon));}
       if(read.NP_SIeta_SB_PGN(photon)==true){h_Ich[27]->Fill(read.photon_pfChargedIsoRhoCorr->at(photon));}
       if(read.P_SIeta_SR_NGN(photon)==true){h_Ich[28]->Fill(read.photon_pfChargedIsoRhoCorr->at(photon));}
       if(read.P_SIeta_SB_NGN(photon)==true){h_Ich[29]->Fill(read.photon_pfChargedIsoRhoCorr->at(photon));}
       if(read.NP_SIeta_SR_NGN(photon)==true){h_Ich[30]->Fill(read.photon_pfChargedIsoRhoCorr->at(photon));}
       if(read.NP_SIeta_SB_NGN(photon)==true){h_Ich[31]->Fill(read.photon_pfChargedIsoRhoCorr->at(photon));}

         }//low HT

       if(read.HThigh()==true){//high HT
       if(read.P_SIeta_SR_PGN(photon)==true){h_Ich[32]->Fill(read.photon_pfChargedIsoRhoCorr->at(photon));}
       if(read.P_SIeta_SB_PGN(photon)==true){h_Ich[33]->Fill(read.photon_pfChargedIsoRhoCorr->at(photon));}
       if(read.NP_SIeta_SR_PGN(photon)==true){h_Ich[34]->Fill(read.photon_pfChargedIsoRhoCorr->at(photon));}
       if(read.NP_SIeta_SB_PGN(photon)==true){h_Ich[35]->Fill(read.photon_pfChargedIsoRhoCorr->at(photon));}
       if(read.P_SIeta_SR_NGN(photon)==true){h_Ich[36]->Fill(read.photon_pfChargedIsoRhoCorr->at(photon));}
       if(read.P_SIeta_SB_NGN(photon)==true){h_Ich[37]->Fill(read.photon_pfChargedIsoRhoCorr->at(photon));}
       if(read.NP_SIeta_SR_NGN(photon)==true){h_Ich[38]->Fill(read.photon_pfChargedIsoRhoCorr->at(photon));}
       if(read.NP_SIeta_SB_NGN(photon)==true){h_Ich[39]->Fill(read.photon_pfChargedIsoRhoCorr->at(photon));}


         }//high HT


        if(read.MHTlow()==true){//low MHT
       if(read.P_SIeta_SR_PGN(photon)==true){h_Ich[40]->Fill(read.photon_pfChargedIsoRhoCorr->at(photon));}
       if(read.P_SIeta_SB_PGN(photon)==true){h_Ich[41]->Fill(read.photon_pfChargedIsoRhoCorr->at(photon));}
       if(read.NP_SIeta_SR_PGN(photon)==true){h_Ich[42]->Fill(read.photon_pfChargedIsoRhoCorr->at(photon));}
       if(read.NP_SIeta_SB_PGN(photon)==true){h_Ich[43]->Fill(read.photon_pfChargedIsoRhoCorr->at(photon));}
       if(read.P_SIeta_SR_NGN(photon)==true){h_Ich[44]->Fill(read.photon_pfChargedIsoRhoCorr->at(photon));}
       if(read.P_SIeta_SB_NGN(photon)==true){h_Ich[45]->Fill(read.photon_pfChargedIsoRhoCorr->at(photon));}
       if(read.NP_SIeta_SR_NGN(photon)==true){h_Ich[46]->Fill(read.photon_pfChargedIsoRhoCorr->at(photon));}
       if(read.NP_SIeta_SB_NGN(photon)==true){h_Ich[47]->Fill(read.photon_pfChargedIsoRhoCorr->at(photon));}
 

         }//low MHT

       if(read.MHThigh()==true){//high MHT
        if(read.P_SIeta_SR_PGN(photon)==true){h_Ich[48]->Fill(read.photon_pfChargedIsoRhoCorr->at(photon));}
       if(read.P_SIeta_SB_PGN(photon)==true){h_Ich[49]->Fill(read.photon_pfChargedIsoRhoCorr->at(photon));}
       if(read.NP_SIeta_SR_PGN(photon)==true){h_Ich[50]->Fill(read.photon_pfChargedIsoRhoCorr->at(photon));}
       if(read.NP_SIeta_SB_PGN(photon)==true){h_Ich[51]->Fill(read.photon_pfChargedIsoRhoCorr->at(photon));}
       if(read.P_SIeta_SR_NGN(photon)==true){h_Ich[52]->Fill(read.photon_pfChargedIsoRhoCorr->at(photon));}
       if(read.P_SIeta_SB_NGN(photon)==true){h_Ich[53]->Fill(read.photon_pfChargedIsoRhoCorr->at(photon));}
       if(read.NP_SIeta_SR_NGN(photon)==true){h_Ich[54]->Fill(read.photon_pfChargedIsoRhoCorr->at(photon));}
       if(read.NP_SIeta_SB_NGN(photon)==true){h_Ich[55]->Fill(read.photon_pfChargedIsoRhoCorr->at(photon));}


         }//high MHT

      




       ////////////////////////      

       cout<<"for testing purpose"<<endl;


       }//Leading Pt Photon

    // }//photon loop
		
    }//event loop 




    double weight = ::atof(Weight.c_str());

    
    cout<<"converted string value: "<<weight<<endl;
    for(int i=0;i<56;i++){
    h_SIeta[i]->Sumw2();
    h_Ich[i]->Sumw2();
    h_SIeta[i]->Scale(weight);
    h_Ich[i]->Scale(weight);

    }
    


   fall->Write();


   cout<<"test"<<endl;

	
}
