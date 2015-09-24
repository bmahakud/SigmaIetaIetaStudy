#include<iostream>
#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include "TLorentzVector.h"
#include<vector>
#include "TTree.h"
using namespace std;

class ReadTree {

public :

   TTree          *fChain;   //!pointer to the analyzed TTree or TChain

   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.

   double         HT;
   double         MHT;
   int           NJets;
   double         dPhi1;
   double         dPhi2;
   double         dPhi3;
   double         evWeight;
   int     nonPrompt;
   int     IchSR;
   int     IchSB;
   int     PGN;
   int     NGN;
   double  SigmaIetaIeta;
   double  photonPt;
   double  photonEta;

   // List of branches
   TBranch        *b_HT;   //!
   TBranch        *b_MHT;   //!
   TBranch        *b_NJets;   //!
   TBranch        *b_dPhi1;   //!
   TBranch        *b_dPhi2;   //!
   TBranch        *b_dPhi3;   //!
   TBranch        *b_evWeight;   //!
   TBranch        *b_nonPrompt;   //!
   TBranch        *b_IchSR;   //!
   TBranch        *b_IchSB;   //!
   TBranch        *b_PGN;   //!
   TBranch        *b_NGN;   //!

   TBranch        *b_SigmaIetaIeta;   //!
   TBranch        *b_photonPt;   //!
   TBranch        *b_photonEta;   //!

   ReadTree(TTree *tree);

   virtual ~ReadTree();
   bool BaseLine();

   bool HTlow();
   
   bool HThigh();


   bool NJetslow();

   bool NJetshigh();
  
   bool MHTlow();

   bool MHThigh();


  bool PassNminusOne(TString Var="");

  

};

ReadTree::~ReadTree()

{

   if (!fChain) return;

   delete fChain->GetCurrentFile();

}

 ReadTree::ReadTree(TTree *tree)

{


fChain=tree;
   

  

   // nonPrompt = 0;
   // IchSR = 0;
   // IchSB = 0;
   // SigmaIetaIeta = 0;
   // photonPt = 0;
   //photonEta = 0;
   // PGN=0;
   //NGN=0;
   
   fChain->SetBranchAddress("HT", &HT, &b_HT);
   fChain->SetBranchAddress("MHT", &MHT, &b_MHT);
   fChain->SetBranchAddress("NJets", &NJets, &b_NJets);
   fChain->SetBranchAddress("dPhi1", &dPhi1, &b_dPhi1);
   fChain->SetBranchAddress("dPhi2", &dPhi2, &b_dPhi2);
   fChain->SetBranchAddress("dPhi3", &dPhi3, &b_dPhi3);
   fChain->SetBranchAddress("evWeight", &evWeight, &b_evWeight);
   fChain->SetBranchAddress("nonPrompt", &nonPrompt, &b_nonPrompt);
   fChain->SetBranchAddress("IchSR", &IchSR, &b_IchSR);
   fChain->SetBranchAddress("IchSB", &IchSB, &b_IchSB);
   fChain->SetBranchAddress("PGN", &PGN, &b_PGN);
   fChain->SetBranchAddress("NGN", &NGN, &b_NGN);
   fChain->SetBranchAddress("SigmaIetaIeta", &SigmaIetaIeta, &b_SigmaIetaIeta);   
   fChain->SetBranchAddress("photonPt", &photonPt, &b_photonPt);
   fChain->SetBranchAddress("photonEta", &photonEta, &b_photonEta);
   

}


bool ReadTree::NJetslow(){

if(NJets < 4 || NJets >5 ){
return false;

}else{

return true;
}

}



bool ReadTree::NJetshigh(){

if(NJets <6 ){
return false;

}else{

return true;
}

}




bool ReadTree::HTlow(){

if( HT < 500. || HT > 800. ){
return false;

}else{

return true;
}

}



bool ReadTree::HThigh(){

if(HT < 800 ){
return false;

}else{

return true;
}

}

bool ReadTree::MHTlow(){

if( MHT > 250. || MHT <200. ){
return false;

}else{

return true;
}

}



bool ReadTree::MHThigh(){

if(MHT < 250. ){
return false;

}else{

return true;
}

}


bool ReadTree::BaseLine(){//baseline





if(NJets >=4  && HT > 500. && MHT >200. /*&& dPhi1>0.5 && dPhi2>0.5 && dPhi3 > 0.3 */&& PGN ==1){



return true;
}else{

return false;
}



}//baseline





bool ReadTree::PassNminusOne(TString Var=""){//N-1

    double HTcut=500;
    double MHTcut=200;
    int NJetscut=4;
    double dPhi1cut=0.5;
    double dPhi2cut=0.5;
    double dPhi3cut=0.3;


if(Var=="HT"){

if( MHT<MHTcut || NJets< NJetscut || dPhi1<dPhi1cut || dPhi2<dPhi2cut || dPhi3<dPhi3cut){return false;}

return true;

}

if(Var=="MHT"){

if(HT<HTcut || NJets< NJetscut || dPhi1<dPhi1cut || dPhi2<dPhi2cut || dPhi3<dPhi3cut){return false;}

return true;

}



if(Var=="NJets"){

if(HT<HTcut || MHT<MHTcut  || dPhi1<dPhi1cut || dPhi2<dPhi2cut || dPhi3<dPhi3cut){return false;}

return true;

}


if(Var=="dPhi1"){

if(HT<HTcut || MHT<MHTcut || NJets< NJetscut  || dPhi2<dPhi2cut || dPhi3<dPhi3cut){return false;}

return true;

}


if(Var=="dPhi2"){

if(HT<HTcut || MHT<MHTcut || NJets< NJetscut || dPhi1<dPhi1cut ||  dPhi3<dPhi3cut){return false;}

return true;

}

if(Var=="dPhi3"){

if(HT<HTcut || MHT<MHTcut || NJets< NJetscut || dPhi1<dPhi1cut || dPhi2<dPhi2cut ){return false;}

return true;

}








}//N-1












 
