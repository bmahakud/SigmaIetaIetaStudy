listBkgSamples=0
for samplebkg in "Bkg_Files_0.dat" "Bkg_Files_1.dat" "Bkg_Files_2.dat" "Bkg_Files_3.dat" "Bkg_Files_4.dat" "Bkg_Files_5.dat" "Bkg_Files_6.dat" "Bkg_Files_7.dat" "Bkg_Files_8.dat" "Bkg_Files_9.dat" "Bkg_Files_10.dat" "Bkg_Files_11.dat"
    do
        listbkg=0
        for bkgfiles in  `cat $samplebkg`
            do
                echo "submitting job .." "jobExecCondor_Bkg_Files_"$listBkgSamples"_"$listbkg"_.jdl"
                condor_submit jobExecCondor_Bkg_Files_${listBkgSamples}_${listbkg}_.jdl 
                ((listbkg+=1))
            done
        ((listBkgSamples+=1))
   done

