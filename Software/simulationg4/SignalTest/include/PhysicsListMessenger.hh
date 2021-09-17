#ifndef PHYSICSLISTMESSENGER_H
#define PHYSICSLISTMESSENGER_H

#include "G4UImessenger.hh"
#include "globals.hh"

class PhysicsList;
class G4UIdirectory;
class G4UIcmdWithoutParameter;
class G4UIcmdWithADoubleAndUnit;
class G4UIcmdWithAString;
class G4UIcmdWithAnInteger;
class G4UIcmdWith3VectorAndUnit;
class G4UIcmdWith3Vector;

class PhysicsListMessenger: public G4UImessenger
{
public:
  explicit PhysicsListMessenger(PhysicsList*);
  ~PhysicsListMessenger();
  
  virtual void SetNewValue(G4UIcommand*, G4String) override;
  
private:
  PhysicsList*     m_physicsList;
  
  G4UIdirectory* m_physicsDir;

  G4UIcmdWithAString* m_selectPhysicsCmd;
  
};

#endif //PHYSICSLISTMESSENGER_H

