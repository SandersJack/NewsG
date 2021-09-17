#include "RunMessenger.hh"

#include "RunAction.hh"
#include "G4UIdirectory.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcmdWithAnInteger.hh"
#include "G4UIcmdWith3VectorAndUnit.hh"
#include "G4UIcmdWithABool.hh"

RunMessenger::RunMessenger(RunAction* run)
  :m_runAction(run)
{
  m_runDir = new G4UIdirectory("/run/");
  m_runDir->SetGuidance("Run commands.");

  m_garfieldDir = new G4UIdirectory("/run/garfield/");
  m_garfieldDir->SetGuidance("Garfield commands for the runs.");

  m_setIonMobCmd = new G4UIcmdWithAString("/run/garfield/setIonMob", this);
  m_setIonMobCmd->SetGuidance("Set ion mobility directory.");
  m_setIonMobCmd->SetGuidance("Options are: BasicMobility, . (i.e current directory - for condor)");
  m_setIonMobCmd->SetParameterName("Type", false, false);
  m_setIonMobCmd->AvailableForStates(G4State_PreInit, G4State_Idle);

  m_setGasCmd = new G4UIcmdWithAString("/run/garfield/setGas", this);
  m_setGasCmd->SetGuidance("Set gas composition.");
  m_setGasCmd->SetGuidance("Options are: Sedine2018, SedineOld, ....");
  m_setGasCmd->SetParameterName("Gas", false, false);
  m_setGasCmd->AvailableForStates(G4State_PreInit, G4State_Idle);

  m_setSensorCmd = new G4UIcmdWithAString("/run/garfield/setSensor", this);
  m_setSensorCmd->SetGuidance("Set anode sensor.");
  m_setSensorCmd->SetGuidance("Options are: BasicSensor and UmbrellaSensor");
  m_setSensorCmd->SetParameterName("Type", false, false);
  m_setSensorCmd->AvailableForStates(G4State_PreInit, G4State_Idle);

  m_doSignalCmd = new G4UIcmdWithABool("/run/garfield/doSignal", this);
  m_doSignalCmd->SetGuidance("Turn signal calculation on (1) or off (0).");
  m_doSignalCmd->SetParameterName("State", false, false);
  m_doSignalCmd->AvailableForStates(G4State_PreInit, G4State_Idle);
    
  m_setSignalBinSizeCmd = new G4UIcmdWithADoubleAndUnit("/run/garfield/setSignalBinSize", this);
  m_setSignalBinSizeCmd->SetGuidance("Set the signal binning size.");
  m_setSignalBinSizeCmd->SetDefaultUnit("ns");
  m_setSignalBinSizeCmd->SetParameterName("Size", false, false);
  m_setSignalBinSizeCmd->AvailableForStates(G4State_PreInit, G4State_Idle);
    
  m_setnSignalBinsCmd = new G4UIcmdWithAnInteger("/run/garfield/setnSignalBins", this);
  m_setnSignalBinsCmd->SetGuidance("Set the number of signal bins.");
  m_setnSignalBinsCmd->SetParameterName("nBins", false, false);
  m_setnSignalBinsCmd->AvailableForStates(G4State_PreInit, G4State_Idle);

  m_doPulseCmd = new G4UIcmdWithABool("/run/garfield/doPulse", this);
  m_doPulseCmd->SetGuidance("Turn pulse calculation on (1) or off (0).");
  m_doPulseCmd->SetParameterName("State", false, false);
  m_doPulseCmd->AvailableForStates(G4State_PreInit, G4State_Idle);

  m_debugCmd = new G4UIcmdWithAnInteger("/run/garfield/debug", this);
  m_debugCmd->SetGuidance("Set debug level.");
  m_debugCmd->SetGuidance("Options: 0 (min), 1, 2 (max)");
  m_debugCmd->SetParameterName("Level", false, false);
  m_debugCmd->AvailableForStates(G4State_PreInit, G4State_Idle);
}

RunMessenger::~RunMessenger()
{
  delete m_setIonMobCmd;
  delete m_setGasCmd;
  delete m_setSensorCmd;
  delete m_doSignalCmd;
  delete m_setSignalBinSizeCmd;
  delete m_setnSignalBinsCmd;
  delete m_doPulseCmd;
  delete m_debugCmd;
  delete m_garfieldDir;
  delete m_runDir;
}

void RunMessenger::SetNewValue(G4UIcommand* command, G4String newValue)
{
  if(command == m_setIonMobCmd)
    {m_runAction->SetIonMobDir(newValue);}
  if(command == m_setGasCmd)
    {m_runAction->SetGas(newValue);}
  if(command == m_setSensorCmd)
    {m_runAction->SetSensorDir(newValue);}
  if(command == m_doSignalCmd)
    {m_runAction->SetSignalCalc(m_doSignalCmd->GetNewBoolValue(newValue));}
  if(command == m_setSignalBinSizeCmd)
    {m_runAction->SetSignalBinSize(m_setSignalBinSizeCmd->GetNewDoubleValue(newValue));}
  if(command == m_setnSignalBinsCmd)
    {m_runAction->SetnSignalBins(m_setnSignalBinsCmd->GetNewIntValue(newValue));}
  if(command == m_doPulseCmd)
    {m_runAction->SetPulseCalc(m_doPulseCmd->GetNewBoolValue(newValue));}
  if(command == m_debugCmd)
    {m_runAction->SetDebug(m_debugCmd->GetNewIntValue(newValue));}
}
