./cmsvoProxy.sh
listSigSamples=0
for samplesig in "Sig_Files_0.dat" "Sig_Files_1.dat"
    do
        listsig=0
        for sigfiles in  `cat $samplesig`
            do
                echo  $listSigSamples $listsig 
                echo "submitting job .." "jobExecCondor_Sig_Files_"$listSigSamples"_"$listsig"_.jdl" 
                condor_submit jobExecCondor_Sig_Files_${listSigSamples}_${listsig}_.jdl 
                ((listsig+=1))
            done
        ((listSigSamples+=1))
   done
