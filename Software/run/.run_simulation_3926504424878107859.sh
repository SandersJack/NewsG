
#!/usr/bin/env bash

# LCG now includes Garfield++ and this can interfere without version
export TMP_GARFIELD=$GARFIELD_HOME
source /cvmfs/sft.cern.ch/lcg/views/LCG_99/x86_64-centos7-gcc10-opt/setup.sh
export GARFIELD_HOME=$TMP_GARFIELD

# This is a bit tricky, but we try to replace a line containing
# /random/setSeeds with some random seeds.
#
# If there is no line with /random/setSeeds then we add one as the first
# line in the file

RANDOM1=$RANDOM
RANDOM2=$RANDOM

#sed "s=/random/setSeeds.*=/random/setSeeds $RANDOM1 $RANDOM2=" $1 > my_simulation.mac
if [ ! $(grep -q "/random/resetEngineFrom" $1) ];
then
	sed "s=/random/setSeeds.*=/random/setSeeds $RANDOM1 $RANDOM2=" $1 > my_simulation.mac
	if [ ! $(grep -q "/random/setSeeds" $1) ];
	then
   	 sed -i "1s=^=/random/setSeeds $RANDOM1 $RANDOM2\n=" my_simulation.mac
	fi
fi

>&2 echo "RANDOM SEEDS = ${RANDOM1} ${RANDOM2}"

cat my_simulation.mac

./SPC_Simulation my_simulation.mac

# Finally, check it exists
test -f output.root
mkdir rndmseeds
mv *.rndm rndmseeds/.

