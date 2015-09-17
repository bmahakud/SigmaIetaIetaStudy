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


void FineTreemaker(TString InputFile="",TString OutputFile="", std::string Weight=""){//main programme
 
    
   if(InputFile=="" || OutputFile=="" || Weight==""){
   cout<<"You are missing input arguments,you should put arguments before running ..."<<endl;
   }

   TFile *fall=new TFile(OutputFile,"RECREATE");

   TTree *T=new TTree("SimpleTree","RA2PhotonTree");
 
   double weight = ::atof(Weight.c_str());

   int NJets;
   double HT,MHT,dPhi1,dPhi2,dPhi3,evWeight;
   int nonPrompt;
   int IchSR;
   int IchSB;
   int PGN;
   int NGN;
   double SigmaIetaIeta;
   double photonPt;
   double photonEta;
  
   T->Branch("HT",&HT);
   T->Branch("MHT",&MHT);
   T->Branch("NJets",&NJets);
   T->Branch("dPhi1",&dPhi1);
   T->Branch("dPhi2",&dPhi2);
   T->Branch("dPhi3",&dPhi3);
   T->Branch("evWeight",&evWeight);
   T->Branch("nonPrompt",&nonPrompt);
   T->Branch("IchSR",&IchSR);
   T->Branch("IchSB",&IchSB);
   T->Branch("PGN",&PGN);
   T->Branch("NGN",&NGN);
   T->Branch("SigmaIetaIeta",&SigmaIetaIeta);
   T->Branch("photonPt",&photonPt);
   T->Branch("photonEta",&photonEta);
      
  
   TChain* t = new TChain("TreeMaker2/PreSelection");
   t->Add(InputFile);
   ClassReadTree read(t);


   int maxEvents=t->GetEntries();

   for(int iEv=0;iEv <t->GetEntries();iEv++){//event loop 
   if( iEv % 100000 == 0 ) cout << "event: " << iEv << endl;
   t->GetEntry(iEv);
   //cout<<"bibhu"<<endl;
   if(read.BestPhoton()!=-1 ){//best photon event

   if(read.recomputeNJets(read.BestPhoton()) >=2){//store only events after NJets cut

    
   NJets=read.recomputeNJets(read.BestPhoton());
   HT=read.recomputeHT(read.BestPhoton());
   MHT=read.recomputeMHT(read.BestPhoton());
   dPhi1=read.recomputeDPhiI(1,read.BestPhoton());
   dPhi2=read.recomputeDPhiI(2,read.BestPhoton());
   dPhi3=read.recomputeDPhiI(3,read.BestPhoton());
   evWeight=weight;
   if(read.photon_nonPrompt->at(read.BestPhoton())==true){
    nonPrompt=1;
    }else{
    nonPrompt=0;
    }


   if(read.Ich_SR(read.BestPhoton())==true){
      IchSR=1;
          }else{
      IchSR=0;
          }


      if(read.Ich_SB(read.BestPhoton())==true){
      IchSB=1;
          }else{
      IchSB=0;

           }


     if(read.PassGammaNeutral(read.BestPhoton())==true){
          PGN=1;
         }else{
          PGN=0;
           }
      if(read.NoGammaNeutral(read.BestPhoton())==true){
          NGN=1;
         }else{
          NGN=0;
           }
 




   SigmaIetaIeta=read.photon_sigmaIetaIeta->at(read.BestPhoton());
   photonPt=read.photonCands->at(read.BestPhoton()).Pt();
   photonEta=read.photonCands->at(read.BestPhoton()).Eta();

    T->Fill();

    }//Store only events after Njets cut

    }//best photon event

   }//event loop



   fall->Write();



}
