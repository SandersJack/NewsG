#ifndef USERG4FASTSIMULATIONMODEL_h
#define USERG4FASTSIMULATIONMODEL_h 1

#include "G4VFastSimulationModel.hh"
#include "G4Electron.hh"
#include "G4SystemOfUnits.hh"

#include "TrackHeed.hh"
#include "AvalancheMicroscopic.hh"
#include "ComponentAnsys121.hh"
#include "Medium.hh"
#include "Sensor.hh"

#include "TCanvas.h"
#include "TH2F.h"
#include "TH1D.h"
#include "TStopwatch.h"
#include "TFile.h"
#include "TTree.h"
#include "TStopwatch.h"

#include "InitialisationParameters.hh"
#include "GasMixture.hh"
#include "FieldMap.hh"
#include "ChargeCarrier.hh"
#include "Ionisation.hh"
#include "ElectronAvalanche.hh"
#include "IonDrift.hh"
#include "Electronics.hh"

#include <string>

class UserG4FastSimulationModel: public G4VFastSimulationModel
{
public:
  UserG4FastSimulationModel(const G4String&, G4Region*, InitialisationParameters*);
  ~UserG4FastSimulationModel();
  
  virtual G4bool IsApplicable(const G4ParticleDefinition&) override;
  virtual G4bool ModelTrigger(const G4FastTrack&) override;
  virtual void DoIt(const G4FastTrack&, G4FastStep&) override;
  
  void Initialise(InitialisationParameters* params);

  
private:

  TFile* m_file;
  TTree* m_tree;
  bool m_doGeant4;
  bool m_doIons;
  bool m_doSignal;
  bool m_doElectronics;
  bool m_doElectrons;

  bool m_gotWFano;

  std::vector<Garfield::Sensor*> m_sensors;
  Garfield::Sensor* m_sensorIons=NULL;
  Garfield::Sensor* m_sensor;
  Ionisation* m_initialElectrons;
  ElectronAvalanche* m_avalanche;
  IonDrift* m_drift;
  Electronics* m_pulseProcess;

  const double m_signalt0 = 0;
  double m_signalBinSize = 50.; //ns
  int m_signalnBins  = 50000;

  double aBar  = 0.3;
  double aCube = 30.0;
  double sensor_radius = 0.15;
  double anode_voltage = 1850;
  double detector_radius = 30.;

  void FindAmplificationArea(Garfield::ComponentAnsys121* fm);
  void CreateSensors(Garfield::ComponentAnsys121* fm);
  void CalculateEFieldDiff(Garfield::ComponentAnsys121* fm);
  void SetDetectorParameters(std::string sensorName);
  void BookTree(int trackID);
  void ClearVariables();
  // Ntuple Variables
  int statusNt;
  double eventNt;
  std::vector<double> initElecRadiusNt;
  std::vector<double> initElecPhiNt;
  std::vector<double> initElecCosThetaNt;
  std::vector<double> initElecTimeNt;
  std::vector<double> initIonRadiusNt;
  std::vector<double> initIonPhiNt;
  std::vector<double> initIonCosThetaNt;
  std::vector<double> initIonTimeNt;
  std::vector<double> ionDriftTimeNt;
  std::vector<double> elecDriftTimeNt;
  double avalancheSizeNt;
  std::vector<double> signalNt;
  std::vector<double> signaltNt;
  std::vector<double> pulseNt;
  std::vector<double> pulsetNt;
  std::vector<double> nElecHeedNt;
  double averageGainNt;
  double integrateTownsendNt;
  std::vector<double> finElecRadiusNt;
  std::vector<double> finElecPhiNt;
  std::vector<double> finElecCosThetaNt;
  std::vector<double> finElecTimeNt;
  std::vector<double> finIonRadiusNt;
  std::vector<double> finIonPhiNt;
  std::vector<double> finIonCosThetaNt;
  std::vector<double> finIonTimeNt;
  double cpuTimeNt;
  double realTimeNt;

  TH1D* signalHistNt=NULL;
  TH1D* signalHistAvalNt=NULL;
};
#endif
