#!/bin/bash
INPUT_ProcessNumber=$1
INPUT_Macro=$2
INPUT_TotalJobs=$3



#/home/prk/NEWSG/simulationRepo/run

# Copy relevant stuff over
cp /home/prk/NEWSG/simulationRepo/build/SPC_Simulation/SPC_Simulation .
#cp /home/$(whoami)/Software/simulationg4/env.sh .
cp /home/prk/NEWSG/simulationRepo/build/setup.sh .
#cp -r /home/$(whoami)/Software/simulationg4/SPC_Simulation/condor/macros/ .
#cp -r /home/prk/NEWSG/simulationRepo/build/SPC_Simulation/output/macros/ .
cp -r /home/prk/NEWSG/simulationRepo/simulationg4/SPC_Simulation/gasfiles .
cp -r /home/prk/NEWSG/simulationRepo/simulationg4/SPC_Simulation/sensors .
cp -r /home/prk/NEWSG/simulationRepo/run/generalMacro.mac .
cp /home/$(whoami)/Software/garfieldpp/Data/IonMobility_He+_He.txt .


# ---Macro generator---

# Change to macro directory
##cd ./macros
#cd /home/prk/Software/simulationg4/SPC_Simulation/output/macros

# Set random seed - very important always need do not forget!
INPUT2=$(expr $INPUT_ProcessNumber + 560)
sed 's\/random/setSeeds/ 0 1\/random/setSeeds '$INPUT_ProcessNumber' '$INPUT2'\i' generalMacro.mac > temp.mac

# Enable fluorescence in physics processes
echo '' >> temp.mac
echo '/process/em/auger true' >> temp.mac
echo '/process/em/augerCascade true' >> temp.mac
echo '/process/em/pixe true' >> temp.mac

# Split the inputs into separate variables
IFS="_" read particle energy sensorType position direction events <<< $INPUT_Macro

# Split energy into values and units as separate variables
IFS="+" read eValue eUnit <<< $energy

# Replace initial particle type and energy in general macro with input values
sed 's\/gun/initialParticle e-\/gun/initialParticle '$particle'\i' temp.mac > temp3.mac
sed 's\/gun/initialEnergy 10 keV\/gun/initialEnergy '$eValue' '$eUnit'\i' temp3.mac > temp2.mac

# Temporary option for testing effect of changing step size
echo '' >> temp2.mac
echo '/det/garfield/avalMCnColl 50000' >> temp2.mac

# Temporary option for testing micro
#echo '' >> temp2.mac
#echo '/det/garfield/avalType Micro' >> temp2.mac

# Temporary option for disabling safety counter
#echo '' >> temp2.mac
#echo '/det/garfield/safetyCounter false' >> temp2.mac

# Temporary option for disabling diffusion
#echo '' >> temp2.mac
#echo '/det/garfield/diffusion false' >> temp2.mac

# Option to set gas composition and pressure in Garfield Ar_98_CH4
echo '' >> temp2.mac
echo '/det/garfield/setGas Ar_98_CH4' >> temp2.mac
echo '/det/garfield/setPressure 225' >> temp2.mac
echo '/event/garfield/setGas Ar_98_CH4' >> temp2.mac
echo '/event/garfield/setPressure 225' >> temp2.mac


#set the sensor type (added 28 08 2019 PK)
echo '' >> temp2.mac
echo '/det/garfield/setSensor '$sensorType >> temp2.mac
echo '/event/garfield/setSensor '$sensorType >> temp2.mac


# Set position to one of three options
# Random position in sphere
if [ "$position" == "anywhere" ]
then
    echo '' >> temp2.mac
    echo '/gun/minRadius 0.15 cm' >> temp2.mac
    echo '/gun/maxRadius 29.99 cm' >> temp2.mac
    mv temp2.mac run.mac
# Random position near sphere edge
elif [ "$position" == "edge" ]
then
    echo '' >> temp2.mac
    echo '/gun/minRadius 29.98 cm' >> temp2.mac
    echo '/gun/maxRadius 29.99 cm' >> temp2.mac
    mv temp2.mac run.mac
elif [ "$position" == "close" ]
then
    echo '' >> temp2.mac
    echo '/gun/minRadius 0.99 cm' >> temp2.mac
    echo '/gun/maxRadius 1 cm' >> temp2.mac
    mv temp2.mac run.mac
elif [ "$position" == "muon" ]
then
    echo '' >> temp2.mac
    echo '/gun/initialPositionDirectionMuons' >> temp2.mac
    mv temp2.mac run.mac
# Specific Cartesian/spherical position in sphere
else
    echo '' >> temp2.mac
    IFS="+" read system x y z pUnit <<< $position
    if [ "$system" == "cartesian" ]
    then
	echo '/gun/initialPositionCartesian ' $x ' ' $y ' ' $z ' ' $pUnit >> temp2.mac
    elif [ "$system" == "spherical" ]
    then
	echo '/gun/initialPositionSpherical ' $x ' ' $y ' ' $z ' ' $pUnit >>temp2.mac
    fi
    mv temp2.mac run.mac
fi

# Set direction in Cartesian/spherical coordinates if a specific direction is requested
if [ "$direction" != "any" ]
then
    if [ "$direction" == "radial" ]
    then
	echo '/gun/radialDirection' >> run.mac
    elif [ "$direction" == "muon" ]
    then
	echo '' >> run.mac
    else
	IFS="+" read system dx dy dz <<< $direction
	if [ "$system" == "cartesian" ]
	then
	    echo '/gun/initialDirectionCartesian ' $dx ' ' $dy ' ' $dz >> run.mac
	elif [ "$system" == "spherical" ]
	then
	    echo '/gun/initialDirectionSpherical ' $dx ' ' $dy ' ' $dz >> run.mac
	fi
    fi
fi

# Update and initialise Geant4
echo '/det/update' >> run.mac
echo '/run/initialize' >> run.mac

# Set number of events in macro
echo "/run/beamOn "$events >> run.mac

# Saves a copy of the macro to check the settings in the event of problems
cp run.mac /disk/moose/general/prk/output3/macros/.
mv /disk/moose/general/prk/output3/macros/run.mac /disk/moose/general/prk/output3/macros/$INPUT_Macro.mac
# Return to previous folder to run macro
cd -


source /home/prk/NEWSG/simulationRepo/build/setup.sh
setup


# Runs the simulation with the new macro
./SPC_Simulation run.mac

# Clean up at the end
rm -rf gasfiles
rm -rf sensors
rm IonMobility_He+_He.txt
rm SPC_Simulation
rm setup.sh
#rm -rf macros
rm generalMacro.mac
