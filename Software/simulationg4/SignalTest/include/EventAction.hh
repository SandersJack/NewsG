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
#include "Electronics.hh"
#include "FieldMap.hh"
#include "GasMixture.hh"
#include "Sensor.hh" 

#include "IonDrift.hh"
#include "ElectronDrift.hh"

class RunAction;
class EventMessenger;
/// Event action class
/// In EndOfEventAction() there is collected information event per event 
/// from Hits Collections, and accumulated statistic for 
/// RunAction::EndOfRunAction().

class EventAction : public G4UserEventAction
{
public:
  explicit EventAction(RunAction*);
  virtual ~EventAction();
  
  virtual void BeginOfEventAction(const G4Event*) override;
  virtual void EndOfEventAction(const G4Event*)   override;
  inline void IsPhoton(){bIsPhoton =true;}
  inline void IsProton(){bIsProton =true;}
  inline void IsElectron(){bIsElectron =true;}
  inline void IsPositron(){bIsPositron =true;}

  // void FillPhotonsAtConverter(G4double energy,G4double xpos, 
  // 			      G4double ypos, G4double zpos);
  // void FillPhotonsAtDetector(G4double energy,G4double xpos, G4double ypos, 
  // 			      G4double zpos, G4double xdir, G4double ydir, G4double zdir);
  // void FillPhotonsAtPhantom(G4double energy,G4double xpos, G4double ypos, G4double zpos, 
  // 			    G4double xdir, G4double ydir, G4double zdir, G4int createprocess);
  // void ProtonStoppedPhantom  (G4double ke_f, G4double xpos_f, G4double ypos_f, G4double zpos_f);
  // void PhotonDirectionConverter(G4double xdir, G4double ydir, G4double zdir);
  // void NeutronsProduced(G4double ke_neut, G4double x_neut, G4double y_neut, G4double z_neut, 
  // 			G4double xdir, G4double ydir, G4double zdir, G4int neutProcess);
  // void NeutronsConverter(G4double ke_neut, G4double x_neut, G4double y_neut, 
  // 			 G4double z_neut, G4double xdir, G4double ydir, G4double zdir);
  // void ElectronsProduced(G4double ke, G4double xpos, G4double ypos, G4double zpos, 
  // 			 G4double xdir, G4double ydir, G4double zdir, G4int creatorprocess);
  // void PositronsProduced(G4double ke, G4double xpos, G4double ypos, G4double zpos, 
  // 			 G4double xdir, G4double ydir, G4double zdir, G4int creatorprocess);
  // void PhotonsCreatedConverter(G4double ke, G4double xpos, G4double ypos, G4double zpos, 
  // 			       G4double xdir, G4double ydir, G4double zdir, G4int creatorprocess);
  // void PhotonsCreatedStrips(G4double ke, G4double xpos, G4double ypos, G4double zpos, 
  // 			    G4double xdir, G4double ydir, G4double zdir, G4int creatorprocess);
  // void ParticlesProduced(G4double ke, G4double xpos, G4double ypos, G4double zpos, G4double xdir, 
  // 			 G4double ydir, G4double zdir, G4int creatorprocess, G4int particle);

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
  inline void SetIonMobDir(std::string dir)     {m_ionMobDir = dir;}
  inline void SetGas(std::string gasType)       {m_gasType = gasType;} 
  inline void SetSensorDir(std::string dir)     {m_sensorDir = dir;}
  inline void SetSignalCalc(bool state)      {m_doSignal = state;}
  inline void SetPulseCalc(bool state)       {m_doPulse = state;}
  inline void SetSignalBinSize(double size)  {m_signalBinSize = size;}
  inline void SetnSignalBins(int nBins)      {m_nSignalBins = nBins;}
  inline void SetDebug(int level)            {m_debug = level;}
  inline void SetPressure(double pressure)   {m_pressure = pressure;}

  // Primary interaction tracking functions
  inline void PrimaryProcess(G4int process){primaryProcess->push_back(process);}
  inline void PrimaryDeltaEnergy(G4double energy){primaryDeltaEnergy->push_back(energy);}
  inline void PrimaryRadius(G4double radius){primaryRadius->push_back(radius);}
  inline void PrimaryCosTheta(G4double cosTheta){primaryCosTheta->push_back(cosTheta);}
  inline void PrimaryPhi(G4double phi){primaryPhi->push_back(phi);}
  

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
  double aCube; // cm 
  double signalt0; // ns

  EventMessenger* m_eventMessenger;
  std::string m_ionMobDir;
  std::string m_gasType;
  std::string m_sensorDir;
  bool     m_doSignal;
  bool     m_doPulse;
  double   m_signalBinSize;
  int      m_nSignalBins;
  int      m_debug;
  double   m_pressure;

  RunAction*  fRunAction;
  G4int fCollID_converter;
  G4int fCollID_detector;
  // G4int fCollID_actdet;

  G4bool bIsPhoton;
  G4bool bIsProton;
  G4bool bIsElectron;
  G4bool bIsPositron;
  
  // std::vector<double>* converter_energy;
  // std::vector<double>* detector_energy;
  // std::vector<double>* detector_position_cog;
  // std::vector<double>* detector_position_max;

  // std::vector<double>* photon_energy_converter;
  // std::vector<double>* photon_energy_detector;
  // std::vector<double>* photon_xpos_converter;
  // std::vector<double>* photon_ypos_converter;
  // std::vector<double>* photon_zpos_converter;
  // std::vector<double>* photon_xdir_converter;
  // std::vector<double>* photon_ydir_converter;
  // std::vector<double>* photon_zdir_converter;
  // std::vector<double>* photon_energy_phantom;
  // std::vector<double>* ke_stop;
  // std::vector<double>* xpos_stop;
  // std::vector<double>* ypos_stop;
  // std::vector<double>* zpos_stop;
  // std::vector<int>* creatorprocess;
  // std::vector<double>* xpos_production;
  // std::vector<double>* ypos_production;
  // std::vector<double>* zpos_production;
  // std::vector<double>* neutronEnergy;
  // std::vector<int>* neutronProcess;
  // std::vector<double>* neut_xpos;
  // std::vector<double>* neut_ypos;
  // std::vector<double>* neut_zpos;
  // std::vector<double>* photon_xdir_production;
  // std::vector<double>* photon_ydir_production;
  // std::vector<double>* photon_zdir_production;
  // std::vector<double>* neutron_xdir_production;
  // std::vector<double>* neutron_ydir_production;
  // std::vector<double>* neutron_zdir_production;
  // std::vector<double>* neutron_energy_converter;
  // std::vector<double>* neutron_xpos_converter;
  // std::vector<double>* neutron_ypos_converter;
  // std::vector<double>* neutron_zpos_converter;
  // std::vector<double>* neutron_xdir_converter;
  // std::vector<double>* neutron_ydir_converter;
  // std::vector<double>* neutron_zdir_converter;
  // std::vector<double>* electron_energy_production;
  // std::vector<double>* electron_xpos_production;
  // std::vector<double>* electron_ypos_production;
  // std::vector<double>* electron_zpos_production;
  // std::vector<double>* electron_xdir_production;
  // std::vector<double>* electron_ydir_production;
  // std::vector<double>* electron_zdir_production;
  // std::vector<int>* electron_creatorprocess;
  // std::vector<double>* positron_energy_production;
  // std::vector<double>* positron_xpos_production;
  // std::vector<double>* positron_ypos_production;
  // std::vector<double>* positron_zpos_production;
  // std::vector<double>* positron_xdir_production;
  // std::vector<double>* positron_ydir_production;
  // std::vector<double>* positron_zdir_production;
  // std::vector<int>* positron_creatorprocess;
  // std::vector<double>* photon_energy_productionconverter;
  // std::vector<double>* photon_energy_productiondetector;
  // std::vector<double>* photon_xpos_productionconverter;
  // std::vector<double>* photon_ypos_productionconverter;
  // std::vector<double>* photon_zpos_productionconverter;
  // std::vector<double>* photon_xdir_productionconverter;
  // std::vector<double>* photon_ydir_productionconverter;
  // std::vector<double>* photon_zdir_productionconverter;
  // std::vector<int>* photon_creatorprocess_converter;
  // std::vector<double>* photon_energy_productionstrips;
  // std::vector<double>* photon_xpos_productionstrips;
  // std::vector<double>* photon_ypos_productionstrips;
  // std::vector<double>* photon_zpos_productionstrips;
  // std::vector<double>* photon_xdir_productionstrips;
  // std::vector<double>* photon_ydir_productionstrips;
  // std::vector<double>* photon_zdir_productionstrips;
  // std::vector<int>* photon_creatorprocess_strips;
  // std::vector<double>* particle_energy_production;
  // std::vector<double>* particle_xpos_production;
  // std::vector<double>* particle_ypos_production;
  // std::vector<double>* particle_zpos_production;
  // std::vector<double>* particle_xdir_production;
  // std::vector<double>* particle_ydir_production;
  // std::vector<double>* particle_zdir_production;
  // std::vector<int>* particle_creatorprocess;
  // std::vector<int>* particle_name;
 
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
  std::vector<double>* initIonRadiusNt;
  std::vector<double>* initIonPhiNt;
  std::vector<double>* initIonCosThetaNt;
  std::vector<double>* initIonTimeNt;
  std::vector<double>* finElecRadiusNt;
  std::vector<double>* finElecPhiNt;
  std::vector<double>* finElecCosThetaNt;
  std::vector<double>* finElecTimeNt;
  std::vector<double>* finIonRadiusNt;
  std::vector<double>* finIonPhiNt;
  std::vector<double>* finIonCosThetaNt;
  std::vector<double>* finIonTimeNt;
  std::vector<double>* ionChargeNt;
  std::vector<int>*    avalancheSizeNt;     
  std::vector<double>* signalNt;
  std::vector<double>* signaltNt;
  std::vector<double>* pulseNt;
  std::vector<double>* pulsetNt;
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

};

#endif

    
