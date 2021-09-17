# get the Geant4 stuff
source /cvmfs/sft.cern.ch/lcg/contrib/gcc/6.3/x86_64-centos7/setup.sh                    #set up compiler
source /cvmfs/geant4.cern.ch/geant4/10.5/x86_64-centos7-gcc63-opt-MT/CMake-setup.sh      #set up environment for Geant4

export CXX=`which g++`                                                                #tell CMake about compiler used 
export CC=`which gcc`

echo ${LD_LIBRARY_PATH}
echo ${PATH}

# setup ROOT
#source /cvmfs/sft.cern.ch/lcg/views/ROOT-latest/x86_64-centos7-gcc62-opt/setup.sh 
export LD_LIBRARY_PATH=/cvmfs/sft.cern.ch/lcg/views/ROOT-latest/x86_64-centos7-gcc62-opt/lib64/:$LD_LIBRARY_PATH
export PATH=/cvmfs/sft.cern.ch/lcg/views/ROOT-latest/x86_64-centos7-gcc62-opt/bin/:$PATH

# additional Garfield++ set up   
export ROOT_HOME=$(root-config --prefix)
export GARFIELD_HOME=/home/$(whoami)/Software/garfieldpp
export HEED_DATABASE=$GARFIELD_HOME/Heed/heed++/database/

# get the correct XercesC
#####export LD_LIBRARY_PATH=/cvmfs/sft.cern.ch/lcg/external/XercesC/3.1.1p2/x86_64-slc6-gcc47-opt/lib/:${LD_LIBRARY_PATH}
# get the correct QT                               
#####export LD_LIBRARY_PATH=/cvmfs/sft.cern.ch/lcg/external/qt/4.8.4/x86_64-slc6-gcc48-opt/lib/:${LD_LIBRARY_PATH}
#####export LD_LIBRARY_PATH=/cvmfs/pravda.egi.eu/PRaVDASuperSimulation/tags/${vSUSI}/tmp/Linux-g++/PRaVDASuperSimulation/:${LD_LIBRARY_PATH}:


