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


void MasterReaderROOT(TString InputFile="",TString OutputFile="", std::string Weight=""){
 

    
    if(InputFile=="" || OutputFile=="" || Weight==""){
    cout<<"You are missing input arguments,you should put arguments before running ..."<<endl;

    }




    TFile *fall=new TFile(OutputFile,"RECREATE");

    TTree *T=new TTree("SimpleTree","RA2PhotonTree");
   

   double weight = ::atof(Weight.c_str());

   int NJets,photonP;
   float HT,MHT,dPhi1,dPhi2,dPhi3,evWeight;
   std::vector<int> nonPrompt;
   std::vector<int> IchSR;
   std::vector<int> IchSB;
   std::vector<int> PGN;
   std::vector<int> NGN;
   std::vector<double>  SigmaIetaIeta;
   std::vector<double>  photonPt;
   std::vector<double> photonEta;
  
   T->Branch("HT",&HT);
   T->Branch("MHT",&MHT);
   T->Branch("NJets",&NJets);
   T->Branch("photonP",&photonP);
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
    for(int iEv=0;iEv < t->GetEntries();iEv++){//event loop 
    nonPrompt.clear();
    IchSR.clear();
    IchSB.clear();
    SigmaIetaIeta.clear();
    PGN.clear();
    NGN.clear();
    photonPt.clear();
    photonEta.clear();


	if( iEv % 500 == 0 ) cout << "event: " << iEv << endl;
        t->GetEntry(iEv);
      int storeif=0;
      float PhotonPt=0;
      int pPosition=-1;
     for(int iPh=0;iPh<read.photonCands->size();iPh++){//photon loop  1  
     if(read.photonCands->at(iPh).Pt() >100.  && read.photon_isEB->at(iPh)==1){//Barrel and high Pt Photons
       if(read.photonCands->at(iPh).Pt() > PhotonPt){
          PhotonPt=read.photonCands->at(iPh).Pt();
          pPosition=iPh;
           }       

       storeif++;
      }//Barrel and high Pt Photons
     } //photon loop 1
     photonP=pPosition;


     if(storeif!=0){
      


        HT=read.HTclean;
        MHT=read.MHTclean;
        NJets=read.NJetsclean;
        dPhi1=read.DeltaPhi1clean;
        dPhi2=read.DeltaPhi2clean;
        dPhi3=read.DeltaPhi3clean;
        evWeight=weight;

       }





    for(int photon=0;photon<read.photonCands->size();photon++){//photon loop  2 
     
     if(read.photonCands->at(photon).Pt() >100.  && read.photon_isEB->at(photon)==1){//Barrel and high Pt Photons
      if(read.PassGammaNeutral(photon)==true){
          PGN.push_back(1);
         }else{
          PGN.push_back(0);
           }
      if(read.NoGammaNeutral(photon)==true){
          NGN.push_back(1);
         }else{
          NGN.push_back(0);
           }
     



      if(read.photon_nonPrompt->at(photon)==true){ 
      nonPrompt.push_back(1);
          }else if(read.photon_nonPrompt->at(photon)!=true){
      nonPrompt.push_back(0);

            }



      if(read.Ich_SR(photon)==true){
      IchSR.push_back(1);
          }else{
      IchSR.push_back(0);
          }


      if(read.Ich_SB(photon)==true){
      IchSB.push_back(1);
          }else{
      IchSB.push_back(0);

           }
   
      SigmaIetaIeta.push_back(read.photon_sigmaIetaIeta->at(photon));
      photonPt.push_back(read.photonCands->at(photon).Pt());
      photonEta.push_back(read.photonCands->at(photon).Eta());

      }//Barrel and high Pt Photons
     } //photon loop 2



     T->Fill();


      }//event loop










   fall->Write();


   cout<<"test"<<endl;

	
}






