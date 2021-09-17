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
// $Id: PhysicsList.cc 66536 2012-12-19 14:32:36Z ihrivnac $
//
/// \file PhysicsList.cc
/// \brief Implementation of the PhysicsList class

#include "PhysicsList.hh"

#include "G4PhysListFactory.hh"

//Radioactive decay

//#include "G4DecayPhysics.hh"
//#include "G4RadioactiveDecayPhysics.hh"
#include "G4RadioactiveDecay.hh"

/// EM physics list 
#include "G4EmStandardPhysics.hh"
#include "G4EmPenelopePhysics.hh"
#include "G4EmLivermorePhysics.hh"
#include "G4EmLivermorePolarizedPhysics.hh"
//#include "PhysListEmPolarized.hh"
#include "G4EmLowEPPhysics.hh"
#include "G4EmParameters.hh"
#include "G4EmExtraPhysics.hh"
//#include "UserPhysicsList.hh"
#include "G4FastSimulationManagerProcess.hh"
#include "G4EmConfigurator.hh"
#include "G4LossTableManager.hh"
#include "G4PAIModel.hh"
#include "G4EmDNAPhysics_option4.hh"

// Hadron physics
#include "G4HadronPhysicsQGSP_BIC_HP.hh"
#include "G4HadronElasticPhysics.hh"
#include "G4StoppingPhysics.hh"
#include "G4IonBinaryCascadePhysics.hh"
#include "G4NeutronTrackingCut.hh"

#include "G4ProcessManager.hh"
#include "G4UserLimits.hh"
#include "StepMax.hh"
#include "G4StepLimiter.hh"
#include "G4VPhysicsConstructor.hh"

#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"

#include "PhysicsListMessenger.hh"


PhysicsList::PhysicsList() 
  : G4VModularPhysicsList()
{
  m_physicsListMessenger = new PhysicsListMessenger(this);
  
  SetVerboseLevel(1);
 
  // Default physics
  //RegisterPhysics(new G4DecayPhysics());
  // Radioactive decay
  //RegisterPhysics(new G4RadioactiveDecayPhysics());
  // EM physics
  emName = "standard" ;
  //RegisterPhysics(new G4EmStandardPhysics());
  //RegisterPhysics(new G4EmLivermorePhysics());
  //RegisterPhysics(new G4EmPenelopePhysics());
  //emPhysicsList = new G4EmPenelopePhysics();
  //emPhysicsList = new G4EmLivermorePhysics();
  emPhysicsList = new std::vector<G4VPhysicsConstructor*>;
  // emPhysicsList->push_back(new G4EmLivermorePhysics());
  emPhysicsList->push_back(new G4EmPenelopePhysics());
  //RegisterPhysics(new G4EmDNAPhysics_option4());


  // emPhysicsList = new G4EmDNAPhysics_option4();
  //RemovePhysics(2);
  //emName = "polarized";
  //RegisterPhysics(new G4EmLivermorePolarizedPhysics());
  //RegisterPhysics(new G4EmLowEPPhysics());
  //G4EmParameters::Instance();
  //emName = "polarized";
  //emPhysicsList = new PhysListEmPolarized();
  //emPhysicsList = new G4EmLivermorePolarizedPhysics();
  
  //this->RegisterPhysics(new G4RadioactiveDecay());

  hadPhysicsList = new std::vector<G4VPhysicsConstructor*>;
  (*hadPhysicsList).push_back( new G4HadronPhysicsQGSP_BIC_HP());
  (*hadPhysicsList).push_back( new G4EmExtraPhysics());
  (*hadPhysicsList).push_back( new G4HadronElasticPhysics());
  (*hadPhysicsList).push_back( new G4StoppingPhysics());
  (*hadPhysicsList).push_back( new G4IonBinaryCascadePhysics());
  //removed for nBLM
  //(*hadPhysicsList).push_back( new G4NeutronTrackingCut());     


  //G4PhysListFactory* physListFactory = new G4PhysListFactory(); 
  //G4VUserPhysicsList * =  physListFactory->GetReferencePhysList("QGSP_BERT");
  //runManager->SetUserInitialization(physicsList);
}



PhysicsList::~PhysicsList()
{ 
  delete m_physicsListMessenger;
}



void PhysicsList::SetCuts()
{
  //  G4VUserPhysicsList::SetCuts();
  std::cout << "[PhysicsList] In set cuts!" << std::endl;
  G4double cut = 20.;    //Need to optimise these
  G4double energy = 40.;
  G4ProductionCutsTable::GetProductionCutsTable()->SetEnergyRange(cut*eV, 1.*TeV);
  G4EmParameters* emParams = G4EmParameters::Instance();
  emParams->SetLowestElectronEnergy(energy*eV);
}  

// Bosons
#include "G4Gamma.hh"
// leptons
#include "G4Electron.hh"
#include "G4Positron.hh"



void PhysicsList::ConstructParticle()
{
  // G4Gamma::GammaDefinition();
  // G4Electron::ElectronDefinition();
  // G4Positron::PositronDefinition();
  // G4GenericIon::GenericIonDefinition();
  //G4Neutron::NeutronDefinition();
  //  emPhysicsList->ConstructParticle();
  for(unsigned int i=0;i<emPhysicsList->size();i++)
    emPhysicsList->at(i)->ConstructParticle();

  for(unsigned int i=0;i<(*hadPhysicsList).size();i++)
   (*hadPhysicsList).at(i)->ConstructParticle();
}



// #include "G4EmProcessOptions.hh"
void PhysicsList::ConstructProcess()
{
  std::cout << "PhysicsList::ConstructProcess()" << std::endl;
  // Transportation
  this->AddTransportation();
  // Electromagnetic physics list
  for(unsigned int i=0;i<emPhysicsList->size();i++)
    emPhysicsList->at(i)->ConstructProcess();


  // emPhysicsList->ConstructProcess();
  
  // G4EmDNAPhysics_option4* dnaPhysics = new G4EmDNAPhysics_option4();
  // dnaPhysics->ConstructProcess();

  // Hadronic physics list
  for(unsigned int i=0;i<(*hadPhysicsList).size();i++)
    (*hadPhysicsList).at(i)->ConstructProcess();
  
  
  G4RadioactiveDecay* radioactiveDecay = new G4RadioactiveDecay();
  // pmanager->AddProcess(radioactiveDecay);
  auto it=GetParticleIterator();
  it->reset();
  while((*it)())
    {
      G4ParticleDefinition*p = it->value();
      G4ProcessManager*manager = p->GetProcessManager();
      manager->AddProcess(radioactiveDecay);
    }

 
  this->AddParameterisation();
  // // step limitation (as a full process)
  this->AddStepMax();      
}

void PhysicsList::AddParameterisation()
{
  std::cout << "[PhysicsList] Adding Parameterisation!" << std::endl;
  G4FastSimulationManagerProcess* FSprocess = new G4FastSimulationManagerProcess("G4FSMP");
  auto it=GetParticleIterator();
  it->reset();
  while((*it)())
    {
      G4ParticleDefinition*p = it->value();
      G4ProcessManager*manager = p->GetProcessManager();
      G4EmConfigurator* config= (G4LossTableManager::Instance())->EmConfigurator();
      // manager->AddDiscreteProcess(FSprocess);
      	  

      if(p->GetParticleName()=="e-")
      	{
      	  manager->AddDiscreteProcess(FSprocess);
      	  G4PAIModel*pai=new G4PAIModel(p,"G4PAIModelElectron");
      	  config->SetExtraEmModel("e-", "eIoni", pai, "gas_region", 0.*eV, 1.*TeV, pai);
	  std::cout << "[PhysicsList] Added PAI model for e-" << std::endl;
	}
      // else if(p->GetParticleName()=="proton")
      // 	{
      // 	  manager->AddDiscreteProcess(FSprocess);
      	  // G4PAIModel*pai=new G4PAIModel(p,"G4PAIModelProton");
      	  // config->SetExtraEmModel("proton", "hIoni", pai, "gas_region", 0.*eV, 1.*TeV, pai); //Check if the names need to be different
	  // std::cout << "[PhysicsList] Added PAI model for proton" << std::endl;      	  
      // 	}
      // else if(p->GetParticleName()=="GenericIon")
      // 	{
	  // manager->AddDiscreteProcess(FSprocess);
      	  // G4PAIModel*pai=new G4PAIModel(p,"G4PAIModelIon");
      	  // config->SetExtraEmModel("GenericIon", "ionIoni", pai, "DefaultRegionForTheWorld", 0.*eV, 1.*TeV, pai); //Causes segFaults
	  // std::cout << "[PhysicsList] Added PAI model for GenericIon" << std::endl;
      // 	}
      // else if(p->GetParticleName()=="alpha")
      // 	{
      // 	  manager->AddDiscreteProcess(FSprocess);
      // 	  G4PAIModel*pai=new G4PAIModel(p,"G4PAIModelAlpha");
      // 	  config->SetExtraEmModel("alpha", "ionIoni", pai, "gas_region", 0.*eV, 1.*TeV, pai);
      // 	  std::cout << "[PhysicsList] Adding PAI model for alpha" << std::endl;
      // 	}
    }
}



void PhysicsList::AddPhysicsList(const G4String& name)
{
  std::cout << "[PhysicsList] In AddPhysicsList!" << std::endl;
  if (verboseLevel>0) 
    G4cout << "PhysicsList::AddPhysicsList: <" << name << ">" << G4endl;
  
  if (name == emName) return;

  if (name == "standard") 
    {
      // emName = name;
      // RemovePhysics(2);
      // emPhysicsList = new G4EmStandardPhysics();
      //RegisterPhysics(new G4EmStandardPhysics());
    } 
  else if (name == "polarized") 
    {
      // emName = name;
      // RemovePhysics(2);
      // emPhysicsList = new G4EmLivermorePolarizedPhysics(); 
      //RegisterPhysics(new G4EmLivermorePolarizedPhysics());
    } 
  else 
    {
      G4cout << "PhysicsList::AddPhysicsList: <" << name << ">"
	     << " is not defined"
	     << G4endl;
    }
}



//#include "G4ProcessManager.hh"
//#include "StepMax.hh"
//#include "G4VPhysicsConstructor.hh"
void PhysicsList::AddStepMax()
{
  std::cout << "PhysicsList::AddStepMax" << std::endl;
  //G4VPhysicsConstructor* physicsConstructor = new G4VPhysicsConstructor();
  
  // Step limitation seen as a process
  StepMax* stepMaxProcess   = new StepMax();
  G4StepLimiter* stepLimiter= new G4StepLimiter();

  auto theParticleIterator = GetParticleIterator(); 
  theParticleIterator->reset();
  while ((*theParticleIterator)())
    {
      G4ParticleDefinition* particle= theParticleIterator->value();
      G4ProcessManager* pmanager    = particle->GetProcessManager();
      if (stepMaxProcess->IsApplicable(*particle) && pmanager)
	pmanager->AddDiscreteProcess(stepLimiter);
    }
}  
