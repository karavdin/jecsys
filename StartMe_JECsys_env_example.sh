#!/bin/bash
#export SCRAM_ARCH=slc6_amd64_gcc493
export SCRAM_ARCH=slc6_amd64_gcc630
#module use -a /afs/desy.de/group/cms/modulefiles/
#module load root6/6.02
#source /afs/cern.ch/sw/lcg/external/gcc/4.9/x86_64-slc6-gcc49-opt/setup.sh
#source /afs/cern.ch/sw/lcg/app/releases/ROOT/6.06.02/x86_64-slc6-gcc49-opt/root/bin/thisroot.sh

source /cvmfs/sft.cern.ch/lcg/contrib/gcc/6.3.0/x86_64-slc6/setup.sh
gcc --version
source /cvmfs/cms.cern.ch/slc6_amd64_gcc630/cms/cmssw/CMSSW_10_1_4/external/slc6_amd64_gcc630/bin/thisroot.sh 
export LD_LIBRARY_PATH=/cvmfs/cms.cern.ch/slc6_amd64_gcc630/external/boost/1.63.0/lib/:/cvmfs/cms.cern.ch/slc6_amd64_gcc630/cms/cmssw/CMSSW_10_1_4/lib/slc6_amd64_gcc630/:$LD_LIBRARY_PATH
export LIBRARY_PATH=/cvmfs/cms.cern.ch/slc6_amd64_gcc630/external/boost/1.63.0/lib/:/cvmfs/cms.cern.ch/slc6_amd64_gcc630/cms/cmssw/CMSSW_10_1_4/lib/slc6_amd64_gcc630/:$LIBRARY_PATH
export CPLUS_INCLUDE_PATH=/cvmfs/cms.cern.ch/slc6_amd64_gcc630/external/boost/1.63.0/include/:/cvmfs/cms.cern.ch/slc6_amd64_gcc630/cms/cmssw/CMSSW_10_1_4/src/:$CPLUS_INCLUDE_PATH
cd /afs/desy.de/user/k/karavdia/xxl/af-cms/JECsys_myfork