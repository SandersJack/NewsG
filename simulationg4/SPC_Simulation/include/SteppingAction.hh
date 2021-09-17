#ifndef SteppingAction_h
#define SteppingAction_h 1

#include "G4UserSteppingAction.hh"
#include "DetectorConstruction.hh"
//#include "HistoManager.hh"
#include "RunAction.hh"
#include "EventAction.hh"

#include "G4ProcessManager.hh"

#define PI 3.14159265

class SteppingAction : public G4UserSteppingAction
{
public:
  SteppingAction(DetectorConstruction*, RunAction*, EventAction*, G4int verbosity=0);
  ~SteppingAction(){};

  void UserSteppingAction(const G4Step*) override;

private:
  DetectorConstruction* detector;
  RunAction*            runAction;
  EventAction*          eventAction;
  //G4double absorber_eDep;      // total energy deposited per event in the absorber
  G4int verboseLevel;
};

#endif
