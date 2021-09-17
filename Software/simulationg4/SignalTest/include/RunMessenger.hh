#ifndef RUNMESSENGER_H
#define RUNMESSENGER_H

#include "G4UImessenger.hh"
#include "globals.hh"

class RunAction;
class G4UIdirectory;
//class G4UIcmdWithoutParameter;
class G4UIcmdWithADoubleAndUnit;
class G4UIcmdWithAString;
class G4UIcmdWithAnInteger;
class G4UIcmdWithABool;
//class G4UIcmdWith3VectorAndUnit;

class RunMessenger: public G4UImessenger
{
public:
  explicit RunMessenger(RunAction*);
  ~RunMessenger();

  virtual void SetNewValue(G4UIcommand*, G4String) override;

private:
  RunAction*               m_runAction;
  
  G4UIdirectory*             m_runDir;
  G4UIdirectory*             m_garfieldDir;
 
  G4UIcmdWithAString*        m_setIonMobCmd;
  G4UIcmdWithAString*        m_setGasCmd;
  G4UIcmdWithAString*        m_setSensorCmd;
  G4UIcmdWithABool*          m_doSignalCmd;
  G4UIcmdWithADoubleAndUnit* m_setSignalBinSizeCmd;
  G4UIcmdWithAnInteger*      m_setnSignalBinsCmd;
  G4UIcmdWithABool*          m_doPulseCmd;
  G4UIcmdWithAnInteger*      m_debugCmd;
};

#endif //RUNMESSENGER_H
