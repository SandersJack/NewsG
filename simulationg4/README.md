# Geant4 and Garfield++ Simulation
SPC detector (SEDINE) 30 cm in diameter - uses ANSYS E-field maps and Magboltz gas transport parameters

## First Time Installation ##
- __make a directory in your home folder and cd into it__
```bash
mkdir Software
cd Software
```

- __clone the simulation__
```bash
cc7 # if you haven't already done this
git clone https://gitlab.bham.ac.uk/nikolopk-bhamgaslab/simulationg4.git
cd simulationg4
#git checkout feature-easySetup
git submodule init
git submodule update
source env.sh
mkdir ../build
cd ../build
cmake ../simulationg4
make -j 64
```


## Everyday Setup - once in simulationg4 folder ##
```bash
git fetch #check for upstream changes
git pull #merge upstream changes if sutiable
git submodule update #update garfield if available
cd ../build
source setup.sh
make
```


## Simulation usage ##
```bash
./SPC_Simulation simulation.mac
```

- The macro file simulation.mac is a list of commands given to the simulation to tell it how to run.
- You can set the initial particle species, energy, position etc. from this .mac file, using commands from the "Messenger" classes
- The initial particles with 'working' physics at the moment are: proton, e-, neutron, alpha, photon and GenericIon (He4 1+ Note: different to an alpha)

## Running SRIM ##

following work from https://gitlab.com/costrouc/pysrim
*  brew cask install docker
*  docker pull costrouc/pysrim
*  docker run -v $PWD:/opt/pysrim/ -v /tmp/output:/tmp/output -it costrouc/pysrim sh -c "xvfb-run -a python3.6 /opt/pysrim/sr.py"
*  *  -v command maps local directory to docker image
*  sr.py needs to be at current directory, srim output will appear in /tmp/output
*  *  ni.py (and nik.py) is an example for TRIM provided by pysrim
*  *  sr.py is our example for SRIM range calculations 

during running, there is no progress bar, so just need to be patient. also there will be some errors of the type
```
0009:err:ole:CoGetClassObject class {f9043c85-f6f2-101a-a3c9-08002b2f49fb} not registered
0009:err:ole:CoGetClassObject class {f9043c85-f6f2-101a-a3c9-08002b2f49fb} not registered
0009:err:ole:CoGetClassObject no class object {f9043c85-f6f2-101a-a3c9-08002b2f49fb} could be created for context 0x3
0009:err:ole:CoGetClassObject class {6262d3a0-531b-11cf-91f6-c2863c385e30} not registered
0009:err:ole:CoGetClassObject class {6262d3a0-531b-11cf-91f6-c2863c385e30} not registered
0009:err:ole:CoGetClassObject no class object {6262d3a0-531b-11cf-91f6-c2863c385e30} could be created for context 0x3
```
just ignore them and wait. at some point output will appear in /tmp/output

## Look at profile results ##

### gprof (old)
```bash
gprof SPC_Simulation gmon.out > analysis.txt
```

- When running the simulation locally the profile of the code run will be added to gmon.out
- This file can be analysed with the above line to see which functions take up the most time


### callgrind
```bash
valgrind --tool=callgrind SPC_Simulation simulation.mac
```
This will create a file called `callgrind.out.XYZ` where `XYZ` is some long number.
You can visualise the results using
```bash
kcachegrind callgrind.out.XYZ
```

## Tracking down memory errors/leaks ##
have some issues with running valgrind still..
```bash
cmake . -DCMAKE_BUILD_TYPE=DEBUG
make
valgrind --leak-check=yes SPC_Simulation simulation.mac
```
also you may want to compile garfield with ```-O0``` and ```-g -pg```

some info here: http://valgrind.org/docs/manual/quick-start.html

## Continuous integration

Every time that you make a commit to this repo, a pipeline will run
that compiles the code, runs a test file
(`SPC_Simulation/simulation.mac`) and compares the output with a
reference file. Should any step fail, or there is a difference between
the output of the test run and the reference, the pipeline will fail.

### What do I do if my pipeline fails?

Don't panic. You can browse the outputs of the pipeline and try and
work out what went wrong. If the `diff` step fails and you know this
is because you made some change that affects the output (please be
100% about this), then you can download the `output.log` file from the
gitlab pipeline, and replace the reference file with this. The
pipeline should now run. The references can be found in
`ci/ref_logs/`.
