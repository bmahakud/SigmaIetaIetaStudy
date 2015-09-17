#include<iostream>
#include <fstream>
using namespace std;

void Create_jdlFineTree(){


ofstream writeSig_hadd("haddScriptSig");
writeSig_hadd<<"hadd "<<"Signal.root ";
ofstream writeBkg_hadd("haddScriptBkg");
writeBkg_hadd<<"hadd "<<"Bkg.root ";

float list_mc_sig_weights[2] = {0.132,0.0379};

float list_mc_bkg_weights[12] = {830.8,140.5,34.9,2.70,0.335,0.100,0.0174,0.00635,0.00431,0.000594,3.51e-5,8.84e-7};
//830.8,140.5,34.9,2.70
for(int is=0;is<2;is++){//loop over signal and bkg files
char sigFileName[100];

sprintf(sigFileName,"Sig_Files_%i.dat",is);

string line;
ifstream read(sigFileName);
int i=0;
while (!read.eof( ))  {//loop over files
read>>line;
char file_jdlName[100];
char output_fileName[100];
sprintf(file_jdlName,"jobExecCondor_Sig_Files_%i_%i_.jdl",is,i);
sprintf(output_fileName,"output_Sig_Files_%i_%i_.root",is,i);
i++;
ofstream write(file_jdlName);
write<<"universe = vanilla"<<endl;
write<<"Executable = jobExecCondorROOT.sh"<<endl;
write<<"Requirements = OpSys == \"LINUX\" && (Arch != \"DUMMY\" )"<<endl;
write<<"request_disk = 1000000"<<endl;
write<<"request_memory = 199"<<endl;
write<<"Should_Transfer_Files = YES"<<endl;
write<<"WhenToTransferOutput = ON_EXIT"<<endl;
write<<"Transfer_Input_Files = jobExecCondorROOT.sh,FineTreemaker.C,ClassReadTree.cc,FineTreemaker_C.so"<<endl;
write<<"Output = $(Cluster)_$(Process).stdout"<<endl;
write<<"Error = $(Cluster)_$(Process).stderr"<<endl;
write<<"Log = $(Cluster)_$(Process).condor"<<endl;
write<<"notification = Never"<<endl;
write<<"x509userproxy = $ENV(X509_USER_PROXY)"<<endl;
write<<"Arguments = root://cmsxrootd.fnal.gov"+line+" "+output_fileName<<" "<<list_mc_sig_weights[is]<<endl; 
writeSig_hadd<<output_fileName<<" ";
write<<"Queue 1"<<endl;
}//loop over files

}//loop over signal and bkg files




for(int is=0;is<12;is++){//loop over  and bkg files
char bkgFileName[100];

sprintf(bkgFileName,"Bkg_Files_%i.dat",is);

string line;
ifstream read(bkgFileName);
int i=0;
while (!read.eof( ))  {//loop over files
read>>line;
char file_jdlName[100];
char output_fileName[100];
sprintf(file_jdlName,"jobExecCondor_Bkg_Files_%i_%i_.jdl",is,i);
sprintf(output_fileName,"output_Bkg_Files_%i_%i_.root",is,i);
i++;
ofstream write(file_jdlName);
write<<"universe = vanilla"<<endl;
write<<"Executable = jobExecCondorROOT.sh"<<endl;
write<<"Requirements = OpSys == \"LINUX\" && (Arch != \"DUMMY\" )"<<endl;
write<<"request_disk = 1000000"<<endl;
write<<"request_memory = 199"<<endl;
write<<"Should_Transfer_Files = YES"<<endl;
write<<"WhenToTransferOutput = ON_EXIT"<<endl;
write<<"Transfer_Input_Files = jobExecCondorROOT.sh,FineTreemaker.C,ClassReadTree.cc,FineTreemaker_C.so"<<endl;
write<<"Output = $(Cluster)_$(Process).stdout"<<endl;
write<<"Error = $(Cluster)_$(Process).stderr"<<endl;
write<<"Log = $(Cluster)_$(Process).condor"<<endl;
write<<"notification = Never"<<endl;
write<<"x509userproxy = $ENV(X509_USER_PROXY)"<<endl;
write<<"Arguments = root://cmsxrootd.fnal.gov"+line+" "+output_fileName<<" "<<list_mc_bkg_weights[is]<<endl;
writeBkg_hadd<<output_fileName<<" ";
write<<"Queue 1"<<endl;
}//loop over files

}//loop over  bkg files



}
