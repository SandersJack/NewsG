#ifndef USERG4FASTSIMULATIONMODEL_h
#define USERG4FASTSIMULATIONMODEL_h 1

#include "G4VFastSimulationModel.hh"
#include "G4Electron.hh"
#include "G4SystemOfUnits.hh"

#include "TCanvas.h"
#include "TH2F.h"
#include "TH1D.h"
#include "TStopwatch.h"
#include "TFile.h"
#include "TTree.h"
#include "TStopwatch.h"

#include "Garfield/TrackHeed.hh"

#include "InitialisationParameters.hh"
#include "GasMixture.hh"
#include "FieldMap.hh"
#include "ChargeCarrier.hh"
#include "Ionisation.hh"
#include "ElectronAvalanche.hh"
#include "IonDrift.hh"
#include "Electronics.hh"

#include <string>

namespace Garfield {
  class Component;
  class ComponentUser;
  class ComponentFieldMap;
  class Sensor;
  class TrackHeed;
}

class DetectorConstruction;

class UserG4FastSimulationModel: public G4VFastSimulationModel
{
public:
 UserG4FastSimulationModel(const G4String&, G4Region*,
                           InitialisationParameters*,
                           DetectorConstruction* detector);
 ~UserG4FastSimulationModel();

 virtual G4bool IsApplicable(const G4ParticleDefinition&) override;
 virtual G4bool ModelTrigger(const G4FastTrack&) override;
 virtual void DoIt(const G4FastTrack&, G4FastStep&) override;

 void Initialise(InitialisationParameters* params);


private:
 // These are ordered in the same way as the class constructor
 // The compiler will emit WARNINGS if this gets messed up. Please don't ignore
 // them!!!
 Garfield::Sensor* m_sensor;
 Ionisation* m_initialElectrons;
 ElectronAvalanche* m_avalanche;
 IonDrift* m_drift;
 bool m_debug;
 bool m_useGarfield;
 DetectorConstruction* m_detector_construction;

 TFile* m_file;
 TTree* m_tree;
 bool m_doGeant4;
 bool m_doIons;
 bool m_doSignal;
 bool m_doElectronics;
 bool m_doElectrons;
 // These should probably begin with m_ as they are member variables
 std::vector<double> signalNt;
 std::vector<double> signaltNt;

 bool m_gotWFano;

 std::vector<Garfield::Sensor*> m_sensors;
 Garfield::Sensor* m_sensorIons = NULL;

 // These are initialised in the .cc constructor
 Garfield::TrackHeed m_trackHeed;

 const double m_signalt0 = 0;
 double m_signalBinSize = 50.;  // ns
 int m_signalnBins = 50000;

 // aCube defines the dimensions of the outer sensors (sensors in the Garfield
 // notation; ie tracking regions) aBar defines the dimensions of the inner
 // sesnsors
 double aBar = 0.3;             // cm
 double aCube = 100.0;          // cm
 double sensor_radius = 0.15;   // cm
 double detector_radius = 30.;  // cm
 double anode_voltage = 1850;   // V

 void FindAmplificationArea(Garfield::ComponentFieldMap* fm);
 void CreateSensors(Garfield::Component* fm);
 void FindAmplificationArea(Garfield::ComponentUser* fm);
 void CalculateEFieldDiff(Garfield::ComponentFieldMap* fm);
 
};
#endif
