#!/bin/bash

#
# variables from arguments string in jdl
#


INPUTFILE=$1
OUTPUTFILE=$2
WEIGHT=$3


echo ""
echo "parameter set:"
echo "INPUTFILE:   $INPUTFILE"
echo "OUTPUTFILE:  $OUTPUTFILE"
echo "WEIGHT:     $WEIGHT"


source /cvmfs/cms.cern.ch/cmsset_default.sh

scram p CMSSW CMSSW_7_4_6_patch6
# cmsenv
cd CMSSW_7_4_6_patch6/src
eval `scramv1 runtime -sh`
cd -




#run macro
echo "run: root -b -q -l 'FineTreemaker.C+("$INPUTFILE","$OUTPUTFILE","$WEIGHT")' 2>&1"
root -b -q -l 'FineTreemaker.C+("'$INPUTFILE'","'$OUTPUTFILE'","'$WEIGHT'")' 
