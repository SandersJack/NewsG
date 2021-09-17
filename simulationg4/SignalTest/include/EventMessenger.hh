#ifndef EVENTMESSENGER_H
#define EVENTMESSENGER_H

#include "G4UImessenger.hh"
#include "globals.hh"

class EventAction;
class G4UIdirectory;
//class G4UIcmdWithoutParameter;
class G4UIcmdWithADoubleAndUnit;
class G4UIcmdWithAString;
class G4UIcmdWithAnInteger;
class G4UIcmdWithABool;
class G4UIcmdWithADouble;
//class G4UIcmdWith3VectorAndUnit;

class EventMessenger: public G4UImessenger
{
public:
  explicit EventMessenger(EventAction*);
  ~EventMessenger();

  virtual void SetNewValue(G4UIcommand*, G4String) override;

private:
  EventAction*               m_eventAction;
  
  G4UIdirectory*             m_eventDir;
  G4UIdirectory*             m_garfieldDir;
 
  G4UIcmdWithAString*        m_setIonMobCmd;
  G4UIcmdWithAString*        m_setGasCmd;
  G4UIcmdWithAString*        m_setSensorCmd;
  G4UIcmdWithABool*          m_doSignalCmd;
  G4UIcmdWithADoubleAndUnit* m_setSignalBinSizeCmd;
  G4UIcmdWithAnInteger*      m_setnSignalBinsCmd;
  G4UIcmdWithABool*          m_doPulseCmd;
  G4UIcmdWithAnInteger*      m_debugCmd;
  G4UIcmdWithADouble*        m_pressureCmd;
};

#endif //EVENTMESSENGER_H
