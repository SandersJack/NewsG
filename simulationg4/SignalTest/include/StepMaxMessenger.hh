#ifndef StepMaxMessenger_h
#define StepMaxMessenger_h 1

#include "G4UImessenger.hh"
#include "globals.hh"

class StepMax;
class G4UIcmdWithADoubleAndUnit;

class StepMaxMessenger: public G4UImessenger
{
public:
  explicit StepMaxMessenger(StepMax*);
  ~StepMaxMessenger();
    
  void SetNewValue(G4UIcommand*, G4String) override;
    
private:
  StepMax* stepMax;
  G4UIcmdWithADoubleAndUnit* StepMaxCmd;
};

#endif