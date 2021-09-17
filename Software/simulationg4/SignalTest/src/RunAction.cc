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

#include "G4RunManager.hh"
#include "G4Run.hh"
#include "G4AccumulableManager.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"

#include "Analysis.hh"
#include "RunMessenger.hh"


#include "InitialisationParameters.hh"

RunAction::RunAction()
 : G4UserRunAction(),
   fGoodEvents(0),
   fGoodEvents2(0),
   fSumDose(0.)  
{  
  m_runMessenger = new RunMessenger(this);

  // Create analysis manager
  auto analysisManager = G4AnalysisManager::Instance();
  analysisManager->SetVerboseLevel(1);
  analysisManager->SetFirstHistoId(1);
  
  // Create ntuple
  analysisManager->CreateNtuple("simul", "energy");
  // analysisManager->CreateNtupleDColumn("energy_converter", converter_energy); //0
  // analysisManager->CreateNtupleDColumn("energy_detector", detector_energy); //1
  // analysisManager->CreateNtupleDColumn("energy"); //2
  // analysisManager->CreateNtupleDColumn("position_cog", detector_position_cog); //3
  // analysisManager->CreateNtupleDColumn("position_max", detector_position_max); //4
  // analysisManager->CreateNtupleDColumn("photon_energy_converter", photon_energy_converter); //5
  // analysisManager->CreateNtupleDColumn("photon_xpos_converter", photon_xpos_converter); //6
  // analysisManager->CreateNtupleDColumn("photon_ypos_converter", photon_ypos_converter); //7
  // analysisManager->CreateNtupleDColumn("photon_zpos_converter", photon_zpos_converter); //8
  // analysisManager->CreateNtupleDColumn("photon_xdir_converter", photon_xdir_converter); //9
  // analysisManager->CreateNtupleDColumn("photon_ydir_converter", photon_ydir_converter); //10
  // analysisManager->CreateNtupleDColumn("photon_zdir_converter", photon_zdir_converter); //11
  // analysisManager->CreateNtupleDColumn("photons_at_converter"); //12
  // analysisManager->CreateNtupleDColumn("proton_xpos_stop", xpos_stop); //13
  // analysisManager->CreateNtupleDColumn("proton_ypos_stop", ypos_stop); //14
  // analysisManager->CreateNtupleDColumn("proton_zpos_stop", zpos_stop); //15 
  // analysisManager->CreateNtupleDColumn("xpos_stop_rel"); //16
  // analysisManager->CreateNtupleDColumn("ypos_stop_rel"); //17 
  // analysisManager->CreateNtupleDColumn("zpos_stop_rel"); //18
  // analysisManager->CreateNtupleDColumn("protons_stopped"); //19
  // analysisManager->CreateNtupleDColumn("photons_produced_phantom"); //20
  // // analysisManager->CreateNtupleDColumn("energy_actdet");
  // // analysisManager->CreateNtupleDColumn("energy_actdet_photon");
  // // analysisManager->CreateNtupleDColumn("energy_actdet_electron");
  // //analysisManager->CreateNtupleDColumn("Egap");
  // analysisManager->CreateNtupleDColumn("photon_energy_phantom", photon_energy_phantom); //21
  // analysisManager->CreateNtupleIColumn("photon_creatorprocess", creatorprocess); //22
  // analysisManager->CreateNtupleDColumn("photon_xpos_phantom", xpos_production); //23
  // analysisManager->CreateNtupleDColumn("photon_ypos_phantom", ypos_production); //24 
  // analysisManager->CreateNtupleDColumn("photon_zpos_phantom", zpos_production); //25
  // analysisManager->CreateNtupleDColumn("photon_xdir_phantom", photon_xdir_production); //26
  // analysisManager->CreateNtupleDColumn("photon_ydir_phantom", photon_ydir_production); //27
  // analysisManager->CreateNtupleDColumn("photon_zdir_phantom", photon_zdir_production); //28
  // analysisManager->CreateNtupleDColumn("photons_produced_converter"); //29
  // analysisManager->CreateNtupleDColumn("photon_energy_production_converter", photon_energy_productionconverter);//30
  // analysisManager->CreateNtupleDColumn("photon_xpos_production_converter", photon_xpos_productionconverter); //31
  // analysisManager->CreateNtupleDColumn("photon_ypos_production_converter", photon_ypos_productionconverter); //32
  // analysisManager->CreateNtupleDColumn("photon_zpos_production_converter", photon_zpos_productionconverter); //33
  // analysisManager->CreateNtupleDColumn("photon_xdir_production_converter", photon_xdir_productionconverter); //34
  // analysisManager->CreateNtupleDColumn("photon_ydir_production_converter", photon_ydir_productionconverter); //35
  // analysisManager->CreateNtupleDColumn("photon_zdir_production_converter", photon_zdir_productionconverter); //36
  // analysisManager->CreateNtupleIColumn("photon_creatorprocess_converter", photon_creatorprocess_converter); //37
  // analysisManager->CreateNtupleDColumn("photons_produced_strips"); //38
  // analysisManager->CreateNtupleDColumn("photon_energy_production_strips", photon_energy_productionstrips); //39
  // analysisManager->CreateNtupleDColumn("photon_xpos_production_strips", photon_xpos_productionstrips); //40
  // analysisManager->CreateNtupleDColumn("photon_ypos_production_strips", photon_ypos_productionstrips); //41
  // analysisManager->CreateNtupleDColumn("photon_zpos_production_strips", photon_zpos_productionstrips); //42
  // analysisManager->CreateNtupleDColumn("photon_xdir_production_strips", photon_xdir_productionstrips); //43
  // analysisManager->CreateNtupleDColumn("photon_ydir_production_strips", photon_ydir_productionstrips); //44
  // analysisManager->CreateNtupleDColumn("photon_zdir_production_strips", photon_zdir_productionstrips); //45
  // analysisManager->CreateNtupleIColumn("photon_creatorprocess_strips", photon_creatorprocess_strips); //46
  // analysisManager->CreateNtupleDColumn("neutrons_produced_phantom"); //47
  // analysisManager->CreateNtupleDColumn("neutron_energy_production", neutronEnergy); //48
  // analysisManager->CreateNtupleIColumn("neutron_creatorprocess", neutronProcess); //49
  // analysisManager->CreateNtupleDColumn("neutron_xpos_production", neut_xpos); //50
  // analysisManager->CreateNtupleDColumn("neutron_ypos_production", neut_ypos); //51
  // analysisManager->CreateNtupleDColumn("neutron_zpos_production", neut_zpos); //52
  // analysisManager->CreateNtupleDColumn("neutron_xdir_production", neutron_xdir_production); //53
  // analysisManager->CreateNtupleDColumn("neutron_ydir_production", neutron_ydir_production); //54
  // analysisManager->CreateNtupleDColumn("neutron_zdir_production", neutron_zdir_production); //55
  // analysisManager->CreateNtupleDColumn("neutrons_at_converter"); //56
  // analysisManager->CreateNtupleDColumn("neutron_energy_converter", neutron_energy_converter); //57
  // analysisManager->CreateNtupleDColumn("neutron_xpos_converter", neutron_xpos_converter); //58
  // analysisManager->CreateNtupleDColumn("neutron_ypos_converter", neutron_ypos_converter); //59
  // analysisManager->CreateNtupleDColumn("neutron_zpos_converter", neutron_zpos_converter); //60
  // analysisManager->CreateNtupleDColumn("neutron_xdir_converter", neutron_xdir_converter); //61
  // analysisManager->CreateNtupleDColumn("neutron_ydir_converter", neutron_ydir_converter); //62
  // analysisManager->CreateNtupleDColumn("neutron_zdir_converter", neutron_zdir_converter); //63
  // analysisManager->CreateNtupleDColumn("electrons_produced"); //64
  // analysisManager->CreateNtupleDColumn("electron_energy_production", electron_energy_production); //65
  // analysisManager->CreateNtupleDColumn("electron_xpos_production", electron_xpos_production); //66
  // analysisManager->CreateNtupleDColumn("electron_ypos_production", electron_ypos_production); //67
  // analysisManager->CreateNtupleDColumn("electron_zpos_production", electron_zpos_production); //68
  // analysisManager->CreateNtupleDColumn("electron_xdir_production", electron_xdir_production); //69
  // analysisManager->CreateNtupleDColumn("electron_ydir_production", electron_ydir_production); //70
  // analysisManager->CreateNtupleDColumn("electron_zdir_production", electron_zdir_production); //71
  // analysisManager->CreateNtupleIColumn("electron_creatorprocess", electron_creatorprocess); //72
  // analysisManager->CreateNtupleDColumn("positrons_produced"); //73
  // analysisManager->CreateNtupleDColumn("positron_energy_production", positron_energy_production); //74
  // analysisManager->CreateNtupleDColumn("positron_xpos_production", positron_xpos_production); //75
  // analysisManager->CreateNtupleDColumn("positron_ypos_production", positron_ypos_production); //76
  // analysisManager->CreateNtupleDColumn("positron_zpos_production", positron_zpos_production); //77
  // analysisManager->CreateNtupleDColumn("positron_xdir_production", positron_xdir_production); //78
  // analysisManager->CreateNtupleDColumn("positron_ydir_production", positron_ydir_production); //79
  // analysisManager->CreateNtupleDColumn("positron_zdir_production", positron_zdir_production); //80
  // analysisManager->CreateNtupleIColumn("positron_creatorprocess", positron_creatorprocess); //81
  // analysisManager->CreateNtupleDColumn("particles_produced"); //82
  // analysisManager->CreateNtupleDColumn("particle_energy_production", particle_energy_production); //83
  // analysisManager->CreateNtupleDColumn("particle_xpos_production", particle_xpos_production); //84
  // analysisManager->CreateNtupleDColumn("particle_ypos_production", particle_ypos_production); //85
  // analysisManager->CreateNtupleDColumn("particle_zpos_production", particle_zpos_production); //86
  // analysisManager->CreateNtupleDColumn("particle_xdir_production", particle_xdir_production); //87
  // analysisManager->CreateNtupleDColumn("particle_ydir_production", particle_ydir_production); //88
  // analysisManager->CreateNtupleDColumn("particle_zdir_production", particle_zdir_production); //89
  // analysisManager->CreateNtupleIColumn("particle_creatorprocess", particle_creatorprocess); //90
  // analysisManager->CreateNtupleIColumn("particle_name", particle_name); //91

  // Primary vertex information
  analysisManager->CreateNtupleIColumn("InitialParticleType",        initialParticleTypeNt); //92
  analysisManager->CreateNtupleDColumn("InitialParticleEnergy",      initialParticleEnergyNt); //93
  analysisManager->CreateNtupleDColumn("InitialParticleRadius",      initialParticleRadiusNt); //94
  analysisManager->CreateNtupleDColumn("InitialParticleCosTheta",    initialParticleCosThetaNt); //95
  analysisManager->CreateNtupleDColumn("InitialParticlePhi",         initialParticlePhiNt); //96
  analysisManager->CreateNtupleDColumn("InitialParticleTime",        initialParticleTimeNt); //97
  analysisManager->CreateNtupleDColumn("InitialParticleDirRad",      initialParticleDirRadNt);
  analysisManager->CreateNtupleDColumn("InitialParticleDirCosTheta", initialParticleDirCosThetaNt);
  analysisManager->CreateNtupleDColumn("InitialParticleDirPhi",      initialParticleDirPhiNt);
  analysisManager->CreateNtupleDColumn("InitialParticleDirX",        initialParticleDirXNt);
  analysisManager->CreateNtupleDColumn("InitialParticleDirY",        initialParticleDirYNt);
  analysisManager->CreateNtupleDColumn("InitialParticleDirZ",        initialParticleDirZNt);
  
  // Garfield++ Values
  analysisManager->CreateNtupleDColumn("InitElecRadius",    initElecRadiusNt); //98
  analysisManager->CreateNtupleDColumn("InitElecPhi",       initElecPhiNt); //99
  analysisManager->CreateNtupleDColumn("InitElecCosTheta",  initElecCosThetaNt); //100
  analysisManager->CreateNtupleDColumn("InitElecTime",      initElecTimeNt); //101
  analysisManager->CreateNtupleDColumn("InitIonRadius",     initIonRadiusNt); //102
  analysisManager->CreateNtupleDColumn("InitIonPhi",        initIonPhiNt); //103
  analysisManager->CreateNtupleDColumn("InitIonCosTheta",   initIonCosThetaNt); //104
  analysisManager->CreateNtupleDColumn("InitIonTime",       initIonTimeNt); //105
  analysisManager->CreateNtupleDColumn("FinElecRadius",     finElecRadiusNt); //106
  analysisManager->CreateNtupleDColumn("FinElecPhi",        finElecPhiNt); //107
  analysisManager->CreateNtupleDColumn("FinElecCosTheta",   finElecCosThetaNt); //108
  analysisManager->CreateNtupleDColumn("FinElecTime",       finElecTimeNt); //109
  analysisManager->CreateNtupleDColumn("FinIonRadius",      finIonRadiusNt); //110
  analysisManager->CreateNtupleDColumn("FinIonPhi",         finIonPhiNt); //111
  analysisManager->CreateNtupleDColumn("FinIonCosTheta",    finIonCosThetaNt); //112
  analysisManager->CreateNtupleDColumn("FinIonTime",        finIonTimeNt); //113
  analysisManager->CreateNtupleDColumn("IonCharge",         ionChargeNt);
  analysisManager->CreateNtupleIColumn("AvalancheSize",     avalancheSizeNt); //114
  analysisManager->CreateNtupleDColumn("Signal",            signalNt); //115
  analysisManager->CreateNtupleDColumn("Signalt",           signaltNt); //116
  analysisManager->CreateNtupleDColumn("Pulse",             pulseNt); //117
  analysisManager->CreateNtupleDColumn("Pulset",            pulsetNt); //118
  analysisManager->CreateNtupleDColumn("ElecDriftTime",     elecDriftTimeNt); //119
  analysisManager->CreateNtupleDColumn("IonDriftTime",      ionDriftTimeNt); //120
  analysisManager->CreateNtupleIColumn("NumInitElecs",      nInitElecNt); //121
  analysisManager->CreateNtupleDColumn("AverageGain",       averageGainNt); //122
  analysisManager->CreateNtupleDColumn("IntegratedTownsend",integrateTownsendNt); //123

  // Primary interaction tracking
  analysisManager->CreateNtupleIColumn("PrimaryProcess", primaryProcess);
  analysisManager->CreateNtupleDColumn("PrimaryDeltaEnergy", primaryDeltaEnergy);
  analysisManager->CreateNtupleDColumn("PrimaryRadius", primaryRadius);
  analysisManager->CreateNtupleDColumn("PrimaryCosTheta", primaryCosTheta);
  analysisManager->CreateNtupleDColumn("PrimaryPhi", primaryPhi);
    
  analysisManager->FinishNtuple();

  // Create metadata tree
  analysisManager->CreateNtuple("treeMetadata", "info");
  analysisManager->CreateNtupleSColumn("Metadata");
  analysisManager->FinishNtuple();

  // analysisManager->CreateH1("h1","Photon energy detector", 10000, 0., 20e3*keV);
  // analysisManager->CreateH1("h2","Photon energy converter", 10000, 0., 20e3*keV);
  // analysisManager->CreateH1("h3","Photon energy phtantom", 10000, 0., 20e3*keV);
  // analysisManager->CreateH1("h4","entries", 10, 0., 10);

  //add new units for dose
  const G4double milligray = 1.e-3*gray;
  const G4double microgray = 1.e-6*gray;
  const G4double nanogray  = 1.e-9*gray;  
  const G4double picogray  = 1.e-12*gray;
   
  new G4UnitDefinition("milligray", "milliGy" , "Dose", milligray);
  new G4UnitDefinition("microgray", "microGy" , "Dose", microgray);
  new G4UnitDefinition("nanogray" , "nanoGy"  , "Dose", nanogray);
  new G4UnitDefinition("picogray" , "picoGy"  , "Dose", picogray);

  // Register accumulable to the accumulable manager
  G4AccumulableManager* accumulableManager = G4AccumulableManager::Instance();
  accumulableManager->RegisterAccumulable(fGoodEvents);
  accumulableManager->RegisterAccumulable(fGoodEvents2);
  accumulableManager->RegisterAccumulable(fSumDose);

  wValue = 0;
  fanoFactor = 0;
}



RunAction::~RunAction()
{ 
  delete G4AnalysisManager::Instance();  
}



void RunAction::BeginOfRunAction(const G4Run* run)
{ 
  G4cout << "### Run " << run->GetRunID() << " start." << G4endl;
  
  // reset accumulables to their initial values
  G4AccumulableManager* accumulableManager = G4AccumulableManager::Instance();
  accumulableManager->Reset();
  
  //inform the runManager to save random number seed
  G4RunManager::GetRunManager()->SetRandomNumberStore(false);

  // Get analysis manager
  auto analysisManager = G4AnalysisManager::Instance();
  // Open an output file
  analysisManager->OpenFile("output");
}



void RunAction::EndOfRunAction(const G4Run* run)
{
  std::cout << "[RunAction] End of run action is entered!" << std::endl;
  G4int nofEvents = run->GetNumberOfEvent();
  if (nofEvents == 0) return;
  
  // Merge accumulables 
  G4AccumulableManager* accumulableManager = G4AccumulableManager::Instance();
  accumulableManager->Merge();

  // Run conditions
  //  note: There is no primary generator action object for "master"
  //        run manager for multi-threaded mode.
  const PrimaryGeneratorAction* generatorAction
    = static_cast<const PrimaryGeneratorAction*>(
        G4RunManager::GetRunManager()->GetUserPrimaryGeneratorAction());

  G4String partName;
  if (generatorAction) 
    {
      G4ParticleDefinition* particle = generatorAction->GetParticleGun()->GetParticleDefinition();
      partName = particle->GetParticleName();
    }  

  // Get metadata - macro filename has been passed to here just need to read in relevant settings from it
  G4String metadata = "";
  if(wValue>1e-19)
    {
    metadata+="; W value is: ";
    metadata+=std::to_string(wValue);
    metadata+=" eV; Fano factor is: ";
    metadata+=std::to_string(fanoFactor);
    }
  
  // Save metadata
  auto analysisManager = G4AnalysisManager::Instance();
  analysisManager->FillNtupleSColumn(1, 0, metadata);
  analysisManager->AddNtupleRow(1);
  
  // Save histograms
  analysisManager->Write();
  analysisManager->CloseFile();
       
  // Print results
  if (IsMaster())
    {
      G4cout
	<< G4endl
	<< "--------------------End of Global Run-----------------------"
	<< G4endl
	<< "  The run was " << nofEvents << " events ";
    }
  else
    {
      G4cout
	<< G4endl
	<< "--------------------End of Local Run------------------------"
	<< G4endl
	<< "  The run was " << nofEvents << " "<< partName;
    }      
  G4cout
    << "; Nb of 'good' e+ annihilations: " << fGoodEvents.GetValue() << "; Nb of 'good' e+ annihilations: " << fGoodEvents2.GetValue()  << G4endl
    //<< " Total dose in patient : " << G4BestUnit(fSumDose.GetValue(),"Dose") 
    << G4endl 
    << "------------------------------------------------------------" << G4endl 
    << G4endl;
}
