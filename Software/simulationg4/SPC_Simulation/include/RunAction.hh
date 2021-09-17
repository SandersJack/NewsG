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
// $Id: RunAction.hh 99559 2016-09-27 07:02:21Z gcosmo $
//
/// \file RunAction.hh
/// \brief Definition of the RunAction class
#ifndef RunAction_h
#define RunAction_h 1

#include <vector>
#include <string>
#include <map>

#include "G4UserRunAction.hh"
#include "G4Accumulable.hh"
#include "globals.hh"

/// Run action class
class RunMessenger;
class DetectorConstruction;

class RunAction : public G4UserRunAction
{
public:
  RunAction(DetectorConstruction*);
  virtual ~RunAction();

  virtual void BeginOfRunAction(const G4Run*) override;
  virtual void EndOfRunAction(const G4Run*) override;

  inline void CountEvent()           {fGoodEvents += 1;}
  inline void CountEvent2()          {fGoodEvents2 += 1;}
  inline void SumDose(G4double dose) {fSumDose += dose;}

  // Run messenger commands
  inline void SetIonMobDir(std::string dir)     {m_ionMobDir = dir;}
  inline void SetGas(std::string gasType)       {m_gasType = gasType;}
  inline void SetSensorDir(std::string dir)     {m_sensorDir = dir;}
  inline void SetSignalCalc(bool state)      {m_doSignal = state;}
  inline void SetPulseCalc(bool state)       {m_doPulse = state;}
  inline void SetSignalBinSize(double size)  {m_signalBinSize = size;}
  inline void SetnSignalBins(int nBins)      {m_nSignalBins = nBins;}
  inline void SetDebug(int level)            {m_debug = level;}
  inline void Macro(G4String file) {macro = file;}
  inline void SetWFano(double w, double fano){wValue = w; fanoFactor = fano;}

  // Primary vertex information
  std::vector<int>    initialParticleTypeNt;
  std::vector<double> initialParticleEnergyNt;
  std::vector<double> initialParticleRadiusNt;
  std::vector<double> initialParticleCosThetaNt;
  std::vector<double> initialParticlePhiNt;
  std::vector<double> initialParticleTimeNt;
  std::vector<double> initialParticleDirRadNt;
  std::vector<double> initialParticleDirCosThetaNt;
  std::vector<double> initialParticleDirPhiNt;
  std::vector<double> initialParticleDirXNt;
  std::vector<double> initialParticleDirYNt;
  std::vector<double> initialParticleDirZNt;

  // Garfield++ Values
  std::vector<double> initElecRadiusNt;
  std::vector<double> initElecPhiNt;
  std::vector<double> initElecCosThetaNt;
  std::vector<double> initElecTimeNt;
  std::vector<double> initElecStatusNt;
  std::vector<double> initIonRadiusNt;
  std::vector<double> initIonPhiNt;
  std::vector<double> initIonCosThetaNt;
  std::vector<double> initIonTimeNt;
  std::vector<double> initIonStatusNt;
  std::vector<double> finElecRadiusNt;
  std::vector<double> finElecPhiNt;
  std::vector<double> finElecCosThetaNt;
  std::vector<double> finElecTimeNt;
  std::vector<double> finElecStatusNt;
  std::vector<double> finIonRadiusNt;
  std::vector<double> finIonPhiNt;
  std::vector<double> finIonCosThetaNt;
  std::vector<double> finIonTimeNt;
  std::vector<double> finIonStatusNt;
  std::vector<double> ionChargeNt;
  std::vector<int> avalancheSizeNt;        //Check if needs to be vector

  // Signal & pulse
  std::vector<double> signalNt;
  std::vector<double> signaltNt;
  std::vector<double> pulseNt;
  std::vector<double> pulsetNt;

  std::vector<double> north_signalNt;
  std::vector<double> north_pulseNt;

  std::vector<double> south_signalNt;
  std::vector<double> south_pulseNt;

  std::vector<double> elecDriftTimeNt;
  std::vector<double> ionDriftTimeNt;
  std::vector<int>    nInitElecNt;
  std::vector<double> averageGainNt;       //Check if needs to be vector
  std::vector<double> integrateTownsendNt; //Check if needs to be vector

  double Rt;  // These variables are for the R2D2 studies
  double Dt;  // These variables are for the R2D2 studies

  std::map<std::string, std::vector<float>> weightingCurrentIntegralNt;
  std::map<std::string, std::vector<float>> weightingPulseIntegralNt;
  std::map<std::string, std::vector<float>> weightingAmplitudeNt;
  std::map<std::string, std::vector<float>> weightingRisetimeNt;
  std::map<std::string, std::vector<float>> weightingPulseWidthNt;
  std::map<std::string, std::vector<float>> weightingIntegratedCurrentRisetimeNt;
  std::map<std::string, std::vector<float>> weightingCurrentPeakTimeNt;

  // Primary interaction tracking
  std::vector<int> primaryProcess;
  std::vector<double> primaryDeltaEnergy;
  std::vector<double> primaryRadius;
  std::vector<double> primaryCosTheta;
  std::vector<double> primaryPhi;
  std::vector<int> primaryVolume;

  // Secondary particle tracking
  std::vector<int> secondaryProcess;
  std::vector<int> secondaryParent;
  std::vector<int> secondaryID;
  std::vector<int> secondaryParticleName;
  std::vector<std::string> secondaryParticleNameString;
  std::vector<double> secondaryDeltaEnergy;
  std::vector<double> secondaryRadius;
  std::vector<double> secondaryCosTheta;
  std::vector<double> secondaryPhi;

  double energy_deposited_detector;
  double energy_deposited_gas;

  std::map<std::string, int> m_ntuple_column_ids;


private:
  G4Accumulable<G4int>    fGoodEvents;
  G4Accumulable<G4int>    fGoodEvents2;
  G4Accumulable<G4double> fSumDose;

  DetectorConstruction* m_detector;
  RunMessenger* m_runMessenger;
  std::string m_ionMobDir;
  std::string m_gasType;
  std::string m_sensorDir;
  bool     m_doSignal;
  bool     m_doPulse;
  double   m_signalBinSize;
  int      m_nSignalBins;
  int      m_debug;

  // Metadata
  std::string macro;
  double wValue;
  double fanoFactor;

  // double m_aCube; // cm
  // double m_signalt0; // ns
};

#endif
