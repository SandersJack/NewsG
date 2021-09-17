#include "PhysicsListMessenger.hh"

#include "PhysicsList.hh"
#include "G4UIdirectory.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWithABool.hh"
// #include "G4UIcmdWithADoubleAndUnit.hh"
// #include "G4UIcmdWithAnInteger.hh"
// #include "G4UIcmdWith3VectorAndUnit.hh"
// #include "G4UIcmdWith3Vector.hh"

PhysicsListMessenger::PhysicsListMessenger(PhysicsList* phys)
  :m_physicsList(phys)
{
  m_physicsDir = new G4UIdirectory("/physics/");
  m_physicsDir->SetGuidance("Physics list commands.");

  m_selectPhysicsCmd = new G4UIcmdWithAString("/physics/selectPhysics", this);
  m_selectPhysicsCmd->SetGuidance("Set the physics to be used in the simulation.");
  m_selectPhysicsCmd->SetGuidance("Options are: Livermore, DNA_Option4, PAI");
  m_selectPhysicsCmd->SetParameterName("physics",false,false);
  m_selectPhysicsCmd->AvailableForStates(G4State_PreInit, G4State_Idle);

  m_srimDir = new G4UIdirectory("/physics/srim/");
  m_srimDir->SetGuidance("Physics list commands.");

  m_srimAlphasCmd = new G4UIcmdWithABool("/physics/srim/alphas", this);
  m_srimAlphasCmd->SetGuidance("Use SRIM for alpha particles");
  m_srimAlphasCmd->SetParameterName("State", false, false);
  m_srimAlphasCmd->AvailableForStates(G4State_PreInit, G4State_Idle);

  m_srimProtonsCmd = new G4UIcmdWithABool("/physics/srim/protons", this);
  m_srimProtonsCmd->SetGuidance("Use SRIM for protons");
  m_srimProtonsCmd->SetParameterName("State", false, false);
  m_srimProtonsCmd->AvailableForStates(G4State_PreInit, G4State_Idle);
}

PhysicsListMessenger::~PhysicsListMessenger()
{
  delete m_selectPhysicsCmd;
  delete m_physicsDir;
  delete m_srimAlphasCmd;
  delete m_srimProtonsCmd;
}

void PhysicsListMessenger::SetNewValue(G4UIcommand* command, G4String /*newValue*/)
{
  if(command == m_selectPhysicsCmd)
    {/*m_physicsList->SelectPhysics(newValue);*/}
  if (command == m_srimAlphasCmd) {
    m_physicsList->UseSRIMAlphas(true);
    std::cout << "[PhysicsListMessenger] Using SRIM to model alpha particles" << std::endl;
  }
  if (command == m_srimProtonsCmd) {
    m_physicsList->UseSRIMProtons(true);
    std::cout << "[PhysicsListMessenger] Using SRIM to model protons" << std::endl;
  }

}
