//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
// $Id$
//
/// \file EventAction.hh
/// \brief Definition of the EventAction class

#ifndef EventAction_h
#define EventAction_h 1

#include <vector>
#include <string>

#include "G4UserEventAction.hh"
#include "globals.hh"
//#include "G4ProcessManager.hh"

class RunAction;
class EventMessenger;
class DetectorConstruction;
/// Event action class
/// In EndOfEventAction() there is collected information event per event
/// from Hits Collections, and accumulated statistic for
/// RunAction::EndOfRunAction().

class EventAction : public G4UserEventAction
{
public:
  EventAction(RunAction*, DetectorConstruction*);
  virtual ~EventAction();

  virtual void BeginOfEventAction(const G4Event*) override;
  virtual void EndOfEventAction(const G4Event*)   override;
  inline void IsPhoton(){bIsPhoton =true;}
  inline void IsProton(){bIsProton =true;}
  inline void IsElectron(){bIsElectron =true;}
  inline void IsPositron(){bIsPositron =true;}

  //Garfield++ value functions
  void InitialElectronNumber();
  void InitialElectrons();
  void InitialIons();
  void FinalElectrons();
  void FinalIons();
  void ElectronDriftTime();
  void IonDriftTime();
  void AvalancheSize();
  void AvalCustomValues();
  void GarfieldSignal();
  void GarfieldPulse();

  // Event messenger commands
  inline void SetSignalCalc(bool state)      {m_doSignal = state;}
  inline void SetPulseCalc(bool state)       {m_doPulse = state;}
  inline void SetPulseAnalysis(bool state)   {m_doAnalysis = state;}
  inline void SetSignalBinSize(double size)  {m_signalBinSize = size;}
  inline void SetnSignalBins(int nBins)      {m_nSignalBins = nBins;}
  inline void SetDebug(int level)            {m_debug = level;}
  inline void SetIdealField(bool state)      {m_useIdealField = state;}

  // Primary interaction tracking functions
  inline void PrimaryProcess(G4int process){primaryProcess->push_back(process);}
  inline void PrimaryDeltaEnergy(G4double energy){primaryDeltaEnergy->push_back(energy);}
  inline void PrimaryRadius(G4double radius){primaryRadius->push_back(radius);}
  inline void PrimaryCosTheta(G4double cosTheta){primaryCosTheta->push_back(cosTheta);}
  inline void PrimaryPhi(G4double phi){primaryPhi->push_back(phi);}
  inline void PrimaryVolume(G4int vol){primaryVolume->push_back(vol);}

  // Secondary particle tracking functions
  inline void SecondaryProcess(G4int process){secondaryProcess->push_back(process);}
  inline void SecondaryDeltaEnergy(G4double energy){secondaryDeltaEnergy->push_back(energy);}
  inline void SecondaryRadius(G4double radius){secondaryRadius->push_back(radius);}
  inline void SecondaryCosTheta(G4double cosTheta){secondaryCosTheta->push_back(cosTheta);}
  inline void SecondaryPhi(G4double phi){secondaryPhi->push_back(phi);}
  inline void SecondaryParent(G4int value){secondaryParent->push_back(value);}
  inline void SecondaryID(G4int value){secondaryID->push_back(value);}
  inline void SecondaryParticleName(G4int value){secondaryParticleName->push_back(value);}
  inline void SecondaryParticleNameString(G4String value){secondaryParticleNameString->push_back(value);}

  inline void AddGasEnergy(double energy) { m_gas_energy += energy; }
  inline void AddDetectorEnergy(double energy) { m_detector_energy += energy; }

  //other
  inline void SetaCube(G4double value){aCube=value;} // in cm

private:
  // Event messenger variables
  /**
  Electronics* pulseProcess;
  GasMixture* gas;
  FieldMap* fieldMap;
  Garfield::Sensor* sensor;
  IonDrift* ionDrift;
  ElectronDrift* electronDrift;
  **/

  EventMessenger* m_eventMessenger;
  bool     m_doSignal;
  bool     m_doPulse;
  bool     m_doAnalysis;
  double   m_signalBinSize;
  int      m_nSignalBins;
  double aCube; // cm
  double signalt0; // ns
  int      m_debug;
  bool m_useIdealField;

  RunAction*  fRunAction;
  DetectorConstruction* m_detector_construction;
  G4int fCollID_converter;
  G4int fCollID_detector;

  G4bool bIsPhoton;
  G4bool bIsProton;
  G4bool bIsElectron;
  G4bool bIsPositron;

  // Primary vertex information
  std::vector<int>*    initialParticleTypeNt;
  std::vector<double>* initialParticleEnergyNt;
  std::vector<double>* initialParticleRadiusNt;
  std::vector<double>* initialParticleCosThetaNt;
  std::vector<double>* initialParticlePhiNt;
  std::vector<double>* initialParticleTimeNt;
  std::vector<double>* initialParticleDirRadNt;
  std::vector<double>* initialParticleDirCosThetaNt;
  std::vector<double>* initialParticleDirPhiNt;
  std::vector<double>* initialParticleDirXNt;
  std::vector<double>* initialParticleDirYNt;
  std::vector<double>* initialParticleDirZNt;

  // Garfield++ values
  std::vector<double>* initElecRadiusNt;
  std::vector<double>* initElecPhiNt;
  std::vector<double>* initElecCosThetaNt;
  std::vector<double>* initElecTimeNt;
  std::vector<double>* initElecStatusNt;
  std::vector<double>* initIonRadiusNt;
  std::vector<double>* initIonPhiNt;
  std::vector<double>* initIonCosThetaNt;
  std::vector<double>* initIonTimeNt;
  std::vector<double>* initIonStatusNt;
  std::vector<double>* finElecRadiusNt;
  std::vector<double>* finElecPhiNt;
  std::vector<double>* finElecCosThetaNt;
  std::vector<double>* finElecTimeNt;
  std::vector<double>* finElecStatusNt;
  std::vector<double>* finIonRadiusNt;
  std::vector<double>* finIonPhiNt;
  std::vector<double>* finIonCosThetaNt;
  std::vector<double>* finIonTimeNt;
  std::vector<double>* finIonStatusNt;
  std::vector<double>* ionChargeNt;
  std::vector<int>*    avalancheSizeNt;

  // Signal & Pulse
  std::vector<double>* signalNt;
  std::vector<double>* signaltNt;
  std::vector<double>* pulseNt;
  std::vector<double>* pulsetNt;

  std::vector<double>* north_signalNt;
  std::vector<double>* north_pulseNt;
  std::vector<double>* south_signalNt;
  std::vector<double>* south_pulseNt;

  std::vector<double>* elecDriftTimeNt;
  std::vector<double>* ionDriftTimeNt;
  std::vector<int>*    nInitElecNt;
  std::vector<double>* averageGainNt;
  std::vector<double>* integrateTownsendNt;

  // Primary interaction tracking
  std::vector<int>*    primaryProcess;
  std::vector<double>* primaryDeltaEnergy;
  std::vector<double>* primaryRadius;
  std::vector<double>* primaryCosTheta;
  std::vector<double>* primaryPhi;
  std::vector<int>*    primaryVolume;

  // Secondary particle tracking
  std::vector<int>*    secondaryProcess;
  std::vector<int>*    secondaryParent;
  std::vector<int>*    secondaryID;
  std::vector<int>*    secondaryParticleName;
  std::vector<std::string>* secondaryParticleNameString;
  std::vector<double>* secondaryDeltaEnergy;
  std::vector<double>* secondaryRadius;
  std::vector<double>* secondaryCosTheta;
  std::vector<double>* secondaryPhi;

  std::map<std::string, std::vector<float>>* weightingCurrentIntegralNt;
  std::map<std::string, std::vector<float>>* weightingPulseIntegralNt;
  std::map<std::string, std::vector<float>>* weightingAmplitudeNt;
  std::map<std::string, std::vector<float>>* weightingRisetimeNt;
  std::map<std::string, std::vector<float>>* weightingPulseWidthNt;
  std::map<std::string, std::vector<float>>* weightingIntegratedCurrentRisetimeNt;
  std::map<std::string, std::vector<float>>* weightingCurrentPeakTimeNt;

  double m_gas_energy = 0;
  double m_detector_energy = 0;

};

#endif
