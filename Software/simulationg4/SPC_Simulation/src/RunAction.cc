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
// $Id: RunAction.cc 99559 2016-09-27 07:02:21Z gcosmo $
//
/// \file RunAction.cc
/// \brief Implementation of the RunAction class
#include "RunAction.hh"
#include "PrimaryGeneratorAction.hh"
#include "DetectorConstruction.hh"

#include "G4AccumulableManager.hh"
#include "G4Run.hh"
#include "G4RunManager.hh"
#include "G4SystemOfUnits.hh"
#include "G4UnitsTable.hh"

#include "Analysis.hh"
#include "RunMessenger.hh"

#include <fstream>
#include <string>
#include "InitialisationParameters.hh"

RunAction::RunAction(DetectorConstruction* detector)
    : G4UserRunAction(), fGoodEvents(0), fGoodEvents2(0), fSumDose(0.), 
    m_detector(detector) {
  m_runMessenger = new RunMessenger(this);

  

  /**
  //add new units for dose
  const G4double milligray = 1.e-3*gray;
  const G4double microgray = 1.e-6*gray;
  const G4double nanogray  = 1.e-9*gray;
  const G4double picogray  = 1.e-12*gray;

  new G4UnitDefinition("milligray", "milliGy" , "Dose", milligray);
  new G4UnitDefinition("microgray", "microGy" , "Dose", microgray);
  new G4UnitDefinition("nanogray" , "nanoGy"  , "Dose", nanogray);
  new G4UnitDefinition("picogray" , "picoGy"  , "Dose", picogray);
  **/

  // Register accumulable to the accumulable manager
  G4AccumulableManager* accumulableManager = G4AccumulableManager::Instance();
  accumulableManager->RegisterAccumulable(fGoodEvents);
  accumulableManager->RegisterAccumulable(fGoodEvents2);
  accumulableManager->RegisterAccumulable(fSumDose);

  wValue = 0;
  fanoFactor = 0;
}

RunAction::~RunAction() { delete G4AnalysisManager::Instance(); }

void RunAction::BeginOfRunAction(const G4Run* run) {
  G4cout << "### Run " << run->GetRunID() << " start." << G4endl;
if(true) {	
  	std::ofstream outfile ("data.txt");
	outfile << "Volume, Process, Particle, Process, Radius, theta, phi, SecondaryParent, EnergyDeposit" << std::endl;
	outfile << " \\\\\\\\\\\\\\\\\\\\  Run " << run->GetRunID() << " start. ////////////////////" <<  std::endl;
        outfile.close();
}; 
  // reset accumulables to their initial values
  G4AccumulableManager* accumulableManager = G4AccumulableManager::Instance();
  accumulableManager->Reset();

  // inform the runManager to save random number seed
  G4RunManager::GetRunManager()->SetRandomNumberStore(true);

  // Create analysis manager
  auto analysisManager = G4AnalysisManager::Instance();
  analysisManager->SetVerboseLevel(1);
  analysisManager->SetFirstHistoId(1);

  // Create ntuple
  analysisManager->CreateNtuple("simul", "energy");

  // Primary vertex information
  analysisManager->CreateNtupleIColumn("InitialParticleType",
                                       initialParticleTypeNt);  // 92
  analysisManager->CreateNtupleDColumn("InitialParticleEnergy",
                                       initialParticleEnergyNt);  // 93
  analysisManager->CreateNtupleDColumn("InitialParticleRadius",
                                       initialParticleRadiusNt);  // 94
  analysisManager->CreateNtupleDColumn("InitialParticleCosTheta",
                                       initialParticleCosThetaNt);  // 95
  analysisManager->CreateNtupleDColumn("InitialParticlePhi",
                                       initialParticlePhiNt);  // 96
  analysisManager->CreateNtupleDColumn("InitialParticleTime",
                                       initialParticleTimeNt);  // 97
  analysisManager->CreateNtupleDColumn("InitialParticleDirRad",
                                       initialParticleDirRadNt);
  analysisManager->CreateNtupleDColumn("InitialParticleDirCosTheta",
                                       initialParticleDirCosThetaNt);
  analysisManager->CreateNtupleDColumn("InitialParticleDirPhi",
                                       initialParticleDirPhiNt);
  analysisManager->CreateNtupleDColumn("InitialParticleDirX",
                                       initialParticleDirXNt);
  analysisManager->CreateNtupleDColumn("InitialParticleDirY",
                                       initialParticleDirYNt);
  analysisManager->CreateNtupleDColumn("InitialParticleDirZ",
                                       initialParticleDirZNt);

  // Garfield++ Values
  analysisManager->CreateNtupleDColumn("InitElecRadius",
                                       initElecRadiusNt);              // 98
  analysisManager->CreateNtupleDColumn("InitElecPhi", initElecPhiNt);  // 99
  analysisManager->CreateNtupleDColumn("InitElecCosTheta",
                                       initElecCosThetaNt);              // 100
  analysisManager->CreateNtupleDColumn("InitElecTime", initElecTimeNt);  // 101
  analysisManager->CreateNtupleDColumn("InitElecStatus", initElecStatusNt);  // 101
  analysisManager->CreateNtupleDColumn("InitIonRadius", initIonRadiusNt);  // 102
  analysisManager->CreateNtupleDColumn("InitIonPhi", initIonPhiNt);  // 103
  analysisManager->CreateNtupleDColumn("InitIonCosTheta",
                                       initIonCosThetaNt);             // 104
  analysisManager->CreateNtupleDColumn("InitIonTime", initIonTimeNt);  // 105
  analysisManager->CreateNtupleDColumn("InitIonStatus", initIonStatusNt);  // 105
  analysisManager->CreateNtupleDColumn("FinElecRadius", finElecRadiusNt);  // 106
  analysisManager->CreateNtupleDColumn("FinElecPhi", finElecPhiNt);  // 107
  analysisManager->CreateNtupleDColumn("FinElecCosTheta",
                                       finElecCosThetaNt);               // 108
  analysisManager->CreateNtupleDColumn("FinElecTime", finElecTimeNt);    // 109
  analysisManager->CreateNtupleDColumn("FinElecStatus", finElecStatusNt);    // 109
  analysisManager->CreateNtupleDColumn("FinIonRadius", finIonRadiusNt);  // 110
  analysisManager->CreateNtupleDColumn("FinIonPhi", finIonPhiNt);        // 111
  analysisManager->CreateNtupleDColumn("FinIonCosTheta",
                                       finIonCosThetaNt);            // 112
  analysisManager->CreateNtupleDColumn("FinIonTime", finIonTimeNt);  // 113
  analysisManager->CreateNtupleDColumn("FinIonStatus", finIonStatusNt);  // 113
  analysisManager->CreateNtupleDColumn("IonCharge", ionChargeNt);
  analysisManager->CreateNtupleIColumn("AvalancheSize", avalancheSizeNt);  // 114

  // Signal & Pulse
  analysisManager->CreateNtupleDColumn("Signal", signalNt);    // 115
  analysisManager->CreateNtupleDColumn("Signalt", signaltNt);  // 116
  analysisManager->CreateNtupleDColumn("Pulse", pulseNt);      // 117
  analysisManager->CreateNtupleDColumn("Pulset", pulsetNt);    // 118

  analysisManager->CreateNtupleDColumn("NorthSignal", north_signalNt);    // 115
  analysisManager->CreateNtupleDColumn("NorthPulse", north_pulseNt);      // 117

  analysisManager->CreateNtupleDColumn("SouthSignal", south_signalNt);    // 115
  analysisManager->CreateNtupleDColumn("SouthPulse", south_pulseNt);      // 117

  analysisManager->CreateNtupleDColumn("ElecDriftTime", elecDriftTimeNt);  // 119
  analysisManager->CreateNtupleDColumn("IonDriftTime", ionDriftTimeNt);  // 120
  analysisManager->CreateNtupleIColumn("NumInitElecs", nInitElecNt);     // 121
  analysisManager->CreateNtupleDColumn("AverageGain", averageGainNt);    // 122
  analysisManager->CreateNtupleDColumn("IntegratedTownsend",
                                       integrateTownsendNt);  // 123
  
  m_ntuple_column_ids["Rt"] = analysisManager->CreateNtupleFColumn("Rt");
  m_ntuple_column_ids["Dt"] = analysisManager->CreateNtupleFColumn("Dt");

  for (const auto& readout :
       m_detector->GetFieldMap()->GetWeightingFieldNames()) {
         std::string rname = readout == "readout" ? "" : readout;       
    analysisManager->CreateNtupleFColumn(rname + "CurrentIntegral", weightingCurrentIntegralNt[readout]);
    analysisManager->CreateNtupleFColumn(rname + "PulseIntegral", weightingPulseIntegralNt[readout]);
    analysisManager->CreateNtupleFColumn(rname + "Amplitude", weightingAmplitudeNt[readout]);
    analysisManager->CreateNtupleFColumn(rname + "Risetime", weightingRisetimeNt[readout]);
    analysisManager->CreateNtupleFColumn(rname + "PulseWidth", weightingPulseWidthNt[readout]);
    analysisManager->CreateNtupleFColumn(rname + "IntegratedCurrentRisetime", weightingIntegratedCurrentRisetimeNt[readout]);
    analysisManager->CreateNtupleFColumn(rname + "CurrentPeakTime", weightingCurrentPeakTimeNt[readout]);
  }

  // Primary interaction tracking
  analysisManager->CreateNtupleIColumn("PrimaryProcess", primaryProcess);
  analysisManager->CreateNtupleDColumn("PrimaryDeltaEnergy",
                                       primaryDeltaEnergy);
  analysisManager->CreateNtupleDColumn("PrimaryRadius", primaryRadius);
  analysisManager->CreateNtupleDColumn("PrimaryCosTheta", primaryCosTheta);
  analysisManager->CreateNtupleDColumn("PrimaryPhi", primaryPhi);
  analysisManager->CreateNtupleIColumn("PrimaryVolume", primaryVolume);

  // Secondary particle tracking
  analysisManager->CreateNtupleIColumn("SecondaryProcess", secondaryProcess);
  analysisManager->CreateNtupleIColumn("SecondaryParent", secondaryParent);
  analysisManager->CreateNtupleIColumn("SecondaryID", secondaryID);
  analysisManager->CreateNtupleIColumn("SecondaryParticleName",
                                       secondaryParticleName);
//  analysisManager->CreateNtupleSColumn("SecondaryParticleNameString",secondaryParticleNameString);
  analysisManager->CreateNtupleDColumn("SecondaryDeltaEnergy",
                                       secondaryDeltaEnergy);
  analysisManager->CreateNtupleDColumn("SecondaryRadius", secondaryRadius);
  analysisManager->CreateNtupleDColumn("SecondaryCosTheta", secondaryCosTheta);
  analysisManager->CreateNtupleDColumn("SecondaryPhi", secondaryPhi);

  m_ntuple_column_ids["energy_deposited_gas"] = analysisManager->CreateNtupleFColumn("EnergyDepositedGas");
  m_ntuple_column_ids["energy_deposited_detector"] = analysisManager->CreateNtupleFColumn("EnergyDepositedDetector");

  analysisManager->FinishNtuple();

  // Create metadata tree
  analysisManager->CreateNtuple("treeMetadata", "info");
  analysisManager->CreateNtupleSColumn("Metadata");
  analysisManager->FinishNtuple();

  // Get analysis manager
  // auto analysisManager = G4AnalysisManager::Instance();
  // Open an output file
  analysisManager->OpenFile("output");
}

void RunAction::EndOfRunAction(const G4Run* run) {
  std::cout << "[RunAction] End of run action is entered!" << std::endl;
  G4int nofEvents = run->GetNumberOfEvent();
  if (nofEvents == 0) return;

  // Merge accumulables
  G4AccumulableManager* accumulableManager = G4AccumulableManager::Instance();
  accumulableManager->Merge();

  // Run conditions
  //  note: There is no primary generator action object for "master"
  //        run manager for multi-threaded mode.
  const PrimaryGeneratorAction* generatorAction =
      static_cast<const PrimaryGeneratorAction*>(
          G4RunManager::GetRunManager()->GetUserPrimaryGeneratorAction());

  G4String partName;
  if (generatorAction) {
    G4ParticleDefinition* particle =
        generatorAction->GetParticleGun()->GetParticleDefinition();
    partName = particle->GetParticleName();
  }

  // Get metadata from macro and from wValue and Fano passthrough
  G4String metadata = "";
  if (wValue > 1e-19) {
    metadata += "; W value is: ";
    metadata += std::to_string(wValue);
    metadata += " eV; Fano factor is: ";
    metadata += std::to_string(fanoFactor);
  }
  // File reading to get metadata out of macro
  std::string line;
  std::ifstream myfile(macro);
  std::string delimiter = " ";
  std::string delimiter2 = "#";
  std::string command = "";
  size_t pos = 0;
  if (myfile.is_open()) {
    while (getline(myfile, line)) {
      if (std::to_string(line.front()) != "#") {
        if ((pos = line.find(delimiter)) != std::string::npos) {
          command = line.substr(0, pos);
          line.erase(0, pos + delimiter.length());
          if ((pos = line.find(delimiter2)) != std::string::npos) {
            line = line.substr(0, pos);
          }
          if (command == "/det/garfield/setGas") {
            metadata += "; Det. Gas: ";
            metadata += line;
          } else if (command == "/event/garfield/setGas") {
            metadata += "; Event Gas: ";
            metadata += line;
          } else if (command == "/event/garfield/setPressure") {
            metadata += "; Event Gas Pressure: ";
            metadata += line;
            metadata += " Torr";
          } else if (command == "/det/garfield/avalType") {
            metadata += "; Aval Type: ";
            metadata += line;
          } else if (command == "/det/garfield/setPressure") {
            metadata += "; Det. Gas Pressure: ";
            metadata += line;
            metadata += " Torr";
          } else if (command == "/gun/minRadius") {
            metadata += "; Min. Prod. Rad.: ";
            metadata += line;
          } else if (command == "/gun/maxRadius") {
            metadata += "; Max. Prod. Rad.: ";
            metadata += line;
          } else if (command == "/event/garfield/setIonMob") {
            metadata += "; Ion Mob.: ";
            metadata += line;
          } else if (command == "/det/garfield/generationType") {
            metadata += "; Gen. Type: ";
            metadata += line;
          } else if (command == "/det/garfield/avalMCStepType") {
            metadata += "; Aval. Step Type: ";
            metadata += line;
          } else if (command == "/det/garfield/avalMCnColl") {
            metadata += "; Aval. nColl: ";
            metadata += line;
          } else if (command == "/det/garfield/debug") {
            metadata += "; Debug: ";
            metadata += line;
          } else if (command == "/det/garfield/singleElec") {
            metadata += "; Single Electron: ";
            metadata += line;
          } else if (command == "/det/garfield/singleIon") {
            metadata += "; Single Ion: ";
            metadata += line;
          } else if (command == "/det/garfield/diffusion") {
            metadata += "; Diffusion: ";
            metadata += line;
          } else if (command == "/event/garfield/setnSignalBins") {
            metadata += "; Signal Bins: ";
            metadata += line;
          } else if (command == "/event/garfield/setSignalBinSize") {
            metadata += "; Signal Bin Size: ";
            metadata += line;
          } else if (command == "/random/setSeeds") {
            metadata += "; Random Seeds: ";
            metadata += line;
          }
        }
      }
      pos = 0;
      command = "";
    }
    myfile.close();
  }

  else
    std::cout << "Unable to open file";

  // Save metadata
  auto analysisManager = G4AnalysisManager::Instance();
  analysisManager->FillNtupleSColumn(1, 0, metadata);
  analysisManager->AddNtupleRow(1);

  // Save histograms/ntuple
  analysisManager->Write();
  analysisManager->CloseFile();

  // Print results
  if (IsMaster()) {
    G4cout << G4endl
           << "--------------------End of Global Run-----------------------"
           << G4endl << "  The run was " << nofEvents << " events ";
  } else {
    G4cout << G4endl
           << "--------------------End of Local Run------------------------"
           << G4endl << "  The run was " << nofEvents << " " << partName;
  }
  G4cout
      << "; Nb of 'good' e+ annihilations: " << fGoodEvents.GetValue()
      << "; Nb of 'good' e+ annihilations: " << fGoodEvents2.GetValue()
      << G4endl
      //<< " Total dose in patient : " << G4BestUnit(fSumDose.GetValue(),"Dose")
      << G4endl
      << "------------------------------------------------------------"
      << G4endl << G4endl;
}
