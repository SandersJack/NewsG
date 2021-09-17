#include "PhysicsListMessenger.hh"

#include "PhysicsList.hh"
#include "G4UIdirectory.hh"
#include "G4UIcmdWithAString.hh"
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
}

PhysicsListMessenger::~PhysicsListMessenger()
{
  delete m_selectPhysicsCmd;
  delete m_physicsDir;
}

void PhysicsListMessenger::SetNewValue(G4UIcommand* command, G4String newValue)
{
  if(command == m_selectPhysicsCmd)
    {/*m_physicsList->SelectPhysics(newValue);*/}
}
