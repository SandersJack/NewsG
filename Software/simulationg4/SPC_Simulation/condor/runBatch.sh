#!/bin/bash
INPUT_ProcessNumber=$1
INPUT_MacroName=$2
INPUT_TotalJobs=$3

#sl6
cp /home/$(whoami)/Software/simulationg4/SPC_Simulation/SPC_Simulation .
cp /home/$(whoami)/Software/simulationg4/env.sh .
cp -r /home/$(whoami)/Software/simulationg4/SPC_Simulation/condor/macros/ .
cp -r /home/$(whoami)/Software/simulationg4/SPC_Simulation/gasfiles .
cp -r /home/$(whoami)/Software/simulationg4/SPC_Simulation/sensors .
cp /home/$(whoami)/Software/garfieldpp/Data/IonMobility_He+_He.txt .

source env.sh
env

# if ! [ -d output_${MacroName} ]
# then 
#     echo Creating output directory
#     mkdir output_${MacroName}
# fi

./SPC_Simulation ./macros/${INPUT_MacroName}.mac

mv output.root output_${INPUT_MacroName}_${INPUT_ProcessNumber}.root
rm -rf gasfiles
rm -rf sensors
rm IonMobility_He+_He.txt
rm SPC_Simulation
rm env.sh
rm -rf macros