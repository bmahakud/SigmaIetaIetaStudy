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


void FineTreeMaker(TString InputFile="",TString OutputFile="", std::string Weight=""){//main programme
 

    
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

   for(int iEv=0;iEv <maxEvents ;iEv++){//event loop 
   // if( iEv % 500 == 0 ) cout << "event: " << iEv << endl;
    t->GetEntry(iEv);
    

   
    if(read.BestPhoton()!=-1 ){//best photon event

    cout<<"event number : "<<iEv<<endl;
    // cout<<"Best Photon Pt: "<<read.photonCands->at(read.BestPhoton()).Pt()<<endl;
    double HTtmp=0;
    double DPhi_1=0;
    double DPhi_2=0;
    double DPhi_3=0;
    
    TLorentzVector MHTvector(0,0,0,0);
    std::vector<TLorentzVector> ak4Jetsclean;
    //cout<<"NJets: "<<read.NJetsclean<<endl;//read.ak4Jets->size()<<endl;
    int NJettmp=0;
    int Jet1=0;
    int Jet2=0;
    int Jet3=0;
    int ithJet=0;
    for(int i=0;i<read.ak4Jets->size();i++){//clean jet loop
    if( read.ak4Jets->at(i).Pt() > 30.){//basic jet pt cut     

    //cout<<"Jet Pt:  "<<read.ak4Jets->at(i).Pt()<<endl;
    double DeltaR=read.ak4Jets->at(i).DeltaR(read.photonCands->at(read.BestPhoton()));

    //cout<<"DeltaR : "<<DeltaR<<endl;
    if(DeltaR >0.4  && read.photon_isEB->at(read.BestPhoton())==1 ){//reject overlaping jets  
        if(ithJet==0){
           Jet1=i;

            }
        if(ithJet==1){
           Jet2=i;

            }         

         if(ithJet==2){
           Jet3=i;

            }



        if(fabs(read.ak4Jets->at(i).Eta()) < 2.4 ){//eta range
        NJettmp++;
        HTtmp=HTtmp+read.ak4Jets->at(i).Pt();
            }//eta range
        MHTvector=MHTvector+read.ak4Jets->at(i);     
        ithJet++;
         } //basic jet pt cut
        }//reject overlaping jets
    }//clean jet loop
 
     if(NJettmp>3){//minimum 4 NJets
    
           DPhi_1=read.ak4Jets->at(Jet1).DeltaPhi(MHTvector);
          

       
           DPhi_2=read.ak4Jets->at(Jet2).DeltaPhi(MHTvector);
           

       
           DPhi_3=read.ak4Jets->at(Jet3).DeltaPhi(MHTvector);
          

         

//if(HTtmp !=read.HTclean){
//    cout<<"HT: "<<read.HT<<endl;
//    cout<<"recomputeHT: "<<HTtmp<<endl;
//    cout<<"HTclean: "<<read.HTclean<<endl;    
//     }
    NJets=NJettmp;
    HT=HTtmp;
    MHT=MHTvector.Pt();
    dPhi1=fabs(DPhi_1);
    dPhi2=fabs(DPhi_2);
    dPhi3=fabs(DPhi_3);
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





    }//minimum 4 NJets


      T->Fill();

      }//best photon event 

   


   }//event loop




   fall->Write();


}//main programme
