DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
# get the Geant4 stuff
source /cvmfs/sft.cern.ch/lcg/views/LCG_99/x86_64-centos7-gcc10-opt/setup.sh

export CXX=`which g++`                                                                #tell CMake about compiler used 
export CC=`which gcc`

echo ${LD_LIBRARY_PATH}
echo ${PATH}


# additional Garfield++ set up   
# export ROOT_HOME=$(root-config --prefix)

export GARFIELD_HOME=$DIR/garfieldpp
export HEED_DATABASE=$GARFIELD_HOME/Heed/heed++/database/


                   


