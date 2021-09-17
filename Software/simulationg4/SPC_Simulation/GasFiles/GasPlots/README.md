To compile the gasfile plotting code, adapt env.sh to your local version of garfieldpp, then:

- cc7
- source setup.sh
- make TransportParameters
- make PlotOxygenScale

To run the code with the R2D2 setup, do:


- ./PlotOxygenScale 1 #1.1 bar  
- ./PlotOxygenScale 0 #0.2 bar 

Note: you may get the error that -lGarfield can't be found. 
This depends on your garfield setup and you may have to hardcode the location of the library in the makefile.
It may be worth having garfield as a submodule here too to prepare a more 'out of the box' setup.


AVALANCHE PROBABILITY

To compile the code for the survivability plots do:

- cc7
- source setup.sh
- make AvalancheProbability

To run this, do: 

./AvalancheProbability --config 1 #1.1 bar 2000V
./AvalancheProbability --config 0 #200 mbar 720V

This generates several plots in the ``AvalancheProbabilityPlots'' folder, including the absolute avalanche probability, variance and standard deviation, as well as a version of each of these normalised such that the pure gas has a probability 100%.
The plots to use for the R2D2 paper are suffixed "_avalancheProbability_normalised.pdf"



OTHER VERSIONS

Compile posterPlots (more up to date code) or sedinePlots with:

make posterPlots
make sedinePlots

Then to run the code:

./posterPlots
./sedinePlots

The directory to save the plots will need to be updated in the code as well!