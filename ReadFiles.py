def getVarFromFile(filename):
    import imp
    f = open(filename)
    global data
    data = imp.load_source('data', '', f)
    f.close()
getVarFromFile('InputDetails.dat')


fp = open("Sig_Files_0.dat")


for i, x in enumerate(fp):
    #print data.XrootPath+line
    with open('jobExecCondor_Sig_Files_0_{0}.jdl'.format(i),'w') as f:
        f.write('universe = vanilla\n')
        f.write('Executable = jobExecCondor.sh\n')
        f.write('Requirements = OpSys == "LINUX" && (Arch != "DUMMY" )\n')
        f.write('request_disk = 1000000\n')
        f.write('request_memory = 199\n')
        f.write('Should_Transfer_Files = YES\n')
        f.write('WhenToTransferOutput = ON_EXIT\n')
        f.write('Transfer_Input_Files = jobExecCondor.sh,MasterReaderAdvanced.C,ClassReadTree.cc,MasterReaderAdvanced_C.so\n')
        f.write('Output = $(Cluster)_$(Process).stdout\n')
        f.write('Error = $(Cluster)_$(Process).stderr\n')   
        f.write('Log = $(Cluster)_$(Process).condor\n')
        f.write('notification = Never\n')
        f.write('x509userproxy = $ENV(X509_USER_PROXY)\n')
        filepath=data.XrootPath+x+"bibhu"  #'SigmaIetaIeta_signal0_{0}'.format(i)
        print filepath
        f.write('Arguments = {0}'.format(filepath))
        f.write('Queue 1\n')




