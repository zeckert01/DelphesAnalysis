

OLDDIR=`pwd`

#DAnalysis
DANALYSISPATH=/afs/cern.ch/user/j/jkiesele/public/DAnalysis_framework/v.1.1_rc2/DAnalysis

#CMSSW and Delphes
cd $DANALYSISPATH/../
cd CMSSW_8_0_4
eval `scramv1 runtime -sh`
cd ..
cd delphes
source DelphesEnv.sh
export DELPHES_PATH=`pwd`
cd $OLDDIR


export PYTHIA8=$CMSSW_RELEASE_BASE/../../../external/pythia8/212-ikhhed3
export LD_LIBRARY_PATH=$PYTHIA8/lib:$LD_LIBRARY_PATH
export DANALYSISPATH=$DANALYSISPATH
export LD_LIBRARY_PATH=$DANALYSISPATH:$LD_LIBRARY_PATH
export PATH=$PATH:$DANALYSISPATH
export LD_LIBRARY_PATH=/afs/cern.ch/user/z/zeckert/private/ttbarAna:$LD_LIBRARY_PATH
export PATH=/afs/cern.ch/user/z/zeckert/private/ttbarAna:$PATH
