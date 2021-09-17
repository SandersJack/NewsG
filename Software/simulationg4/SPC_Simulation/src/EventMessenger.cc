#include "EventMessenger.hh"

#include "EventAction.hh"
#include "G4UIdirectory.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcmdWithAnInteger.hh"
#include "G4UIcmdWith3VectorAndUnit.hh"
#include "G4UIcmdWithABool.hh"
#include "G4UIcmdWithADouble.hh"

EventMessenger::EventMessenger(EventAction* event)
  :m_eventAction(event)
{
  m_eventDir = new G4UIdirectory("/event/");
  m_eventDir->SetGuidance("Event commands.");

  m_garfieldDir = new G4UIdirectory("/event/garfield/");
  m_garfieldDir->SetGuidance("Garfield commands for the events.");

  m_setIonMobCmd = new G4UIcmdWithAString("/event/garfield/setIonMob", this);
  m_setIonMobCmd->SetGuidance("Set ion mobility directory.");
  m_setIonMobCmd->SetGuidance("Options are: BasicMobility, . (i.e current directory - for condor)");
  m_setIonMobCmd->SetParameterName("Type", false, false);
  m_setIonMobCmd->AvailableForStates(G4State_PreInit, G4State_Idle);

  m_setGasCmd = new G4UIcmdWithAString("/event/garfield/setGas", this);
  m_setGasCmd->SetGuidance("Set gas composition.");
  m_setGasCmd->SetGuidance("Options are: Sedine2018, SedineOld, ....");
  m_setGasCmd->SetParameterName("Gas", false, false);
  m_setGasCmd->AvailableForStates(G4State_PreInit, G4State_Idle);

  m_setSensorCmd = new G4UIcmdWithAString("/event/garfield/setSensor", this);
  m_setSensorCmd->SetGuidance("Set anode sensor.");
  m_setSensorCmd->SetGuidance("Options are: BasicSensor and UmbrellaSensor");
  m_setSensorCmd->SetParameterName("Type", false, false);
  m_setSensorCmd->AvailableForStates(G4State_PreInit, G4State_Idle);

  m_doSignalCmd = new G4UIcmdWithABool("/event/garfield/doSignal", this);
  m_doSignalCmd->SetGuidance("Turn signal calculation on (1) or off (0).");
  m_doSignalCmd->SetParameterName("State", false, false);
  m_doSignalCmd->AvailableForStates(G4State_PreInit, G4State_Idle);
    
  m_setSignalBinSizeCmd = new G4UIcmdWithADoubleAndUnit("/event/garfield/setSignalBinSize", this);
  m_setSignalBinSizeCmd->SetGuidance("Set the signal binning size.");
  m_setSignalBinSizeCmd->SetDefaultUnit("ns");
  m_setSignalBinSizeCmd->SetParameterName("Size", false, false);
  m_setSignalBinSizeCmd->AvailableForStates(G4State_PreInit, G4State_Idle);
    
  m_setnSignalBinsCmd = new G4UIcmdWithAnInteger("/event/garfield/setnSignalBins", this);
  m_setnSignalBinsCmd->SetGuidance("Set the number of signal bins.");
  m_setnSignalBinsCmd->SetParameterName("nBins", false, false);
  m_setnSignalBinsCmd->AvailableForStates(G4State_PreInit, G4State_Idle);

  m_doPulseCmd = new G4UIcmdWithABool("/event/garfield/doPulse", this);
  m_doPulseCmd->SetGuidance("Turn pulse calculation on (1) or off (0).");
  m_doPulseCmd->SetParameterName("State", false, false);
  m_doPulseCmd->AvailableForStates(G4State_PreInit, G4State_Idle);

  m_debugCmd = new G4UIcmdWithAnInteger("/event/garfield/debug", this);
  m_debugCmd->SetGuidance("Set debug level.");
  m_debugCmd->SetGuidance("Options: 0 (min), 1, 2 (max)");
  m_debugCmd->SetParameterName("Level", false, false);
  m_debugCmd->AvailableForStates(G4State_PreInit, G4State_Idle);

  m_pressureCmd = new G4UIcmdWithADouble("/event/garfield/setPressure", this);
  m_pressureCmd->SetGuidance("Set gas pressure (in Torr)");
  m_pressureCmd->SetParameterName("Gas", false, false);
  m_pressureCmd->AvailableForStates(G4State_PreInit, G4State_Idle);

  m_idealFieldCmd = new G4UIcmdWithABool("/event/garfield/idealField", this);
  m_idealFieldCmd->SetGuidance("Use ideal electric field (1) or ANSYS field (0).");
  m_idealFieldCmd->SetParameterName("State", false, false);
  m_idealFieldCmd->AvailableForStates(G4State_PreInit, G4State_Idle);
}

EventMessenger::~EventMessenger()
{
  delete m_setIonMobCmd;
  delete m_setGasCmd;
  delete m_setSensorCmd;
  delete m_doSignalCmd;
  delete m_setSignalBinSizeCmd;
  delete m_setnSignalBinsCmd;
  delete m_doPulseCmd;
  delete m_debugCmd;
  delete m_pressureCmd;
  delete m_idealFieldCmd;
  delete m_garfieldDir;
  delete m_eventDir;
}

void EventMessenger::SetNewValue(G4UIcommand* command, G4String newValue) {
  if (command == m_setIonMobCmd) {
    DeprecationWarning(command);
    // m_eventAction->SetIonMobDir(newValue);
  }
  if (command == m_setGasCmd) {
    DeprecationWarning(command);
    // m_eventAction->SetGas(newValue);
  }
  if (command == m_setSensorCmd) {
    DeprecationWarning(command);
    // m_eventAction->SetSensorDir(newValue);
  }
  if (command == m_doSignalCmd) {
    m_eventAction->SetSignalCalc(m_doSignalCmd->GetNewBoolValue(newValue));
  }
  if (command == m_setSignalBinSizeCmd) {
    m_eventAction->SetSignalBinSize(
        m_setSignalBinSizeCmd->GetNewDoubleValue(newValue));
  }
  if (command == m_setnSignalBinsCmd) {
    m_eventAction->SetnSignalBins(
        m_setnSignalBinsCmd->GetNewIntValue(newValue));
  }
  if (command == m_doPulseCmd) {
    m_eventAction->SetPulseCalc(m_doPulseCmd->GetNewBoolValue(newValue));
  }
  if (command == m_debugCmd) {
    m_eventAction->SetDebug(m_debugCmd->GetNewIntValue(newValue));
  }
  if (command == m_pressureCmd) {
    DeprecationWarning(command);
    // m_eventAction->SetPressure(m_pressureCmd->GetNewDoubleValue(newValue));
  }
  if (command == m_idealFieldCmd) {
    m_eventAction->SetIdealField(m_idealFieldCmd->GetNewBoolValue(newValue));
  }
}

void EventMessenger::DeprecationWarning(G4UIcommand* command) {
  G4cout << "WARNING: "
         << command->GetCommandPath() 
         << " is deprecated and does nothing!! "
         << "Set using the /det/ option instead! "
         << "This option will be removed in the future."
         << G4endl;
}
