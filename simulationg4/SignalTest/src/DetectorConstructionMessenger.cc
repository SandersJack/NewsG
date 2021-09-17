#include "DetectorConstructionMessenger.hh"
 
#include "DetectorConstruction.hh"
#include "G4UIdirectory.hh"
#include "G4UIcmdWithAnInteger.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcmdWithADouble.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWithoutParameter.hh"
#include "G4UIcmdWithABool.hh"
//#include "G4UIcmdWith3VectorAndUnit.hh"
 
DetectorConstructionMessenger::DetectorConstructionMessenger(DetectorConstruction* det)
:m_detectorConstruction(det)
{  
  m_detDir = new G4UIdirectory("/det/");
  m_detDir->SetGuidance("Detector Construction Commands");

  m_garfieldDir = new G4UIdirectory("/det/garfield/");
  m_garfieldDir->SetGuidance("Garfield Initialisation Commands");
     
  m_updateCmd = new G4UIcmdWithoutParameter("/det/update",this);
  m_updateCmd->SetGuidance("Update converter geometry.");
  m_updateCmd->SetGuidance("This command MUST be applied before \"beamOn\" ");
  m_updateCmd->SetGuidance("if you changed geometrical value(s).");
  m_updateCmd->AvailableForStates(G4State_PreInit, G4State_Idle); 
 
  m_generationTypeCmd = new G4UIcmdWithAString("/det/garfield/generationType", this);
  m_generationTypeCmd->SetGuidance("Set generation type for initial electrons.");
  m_generationTypeCmd->SetGuidance("Options are: Geant4, Electrons, HEED and SRIM");
  m_generationTypeCmd->SetGuidance("(Options other than Geant4 replicate the standalone package)");
  m_generationTypeCmd->SetParameterName("Type", false, false);
  m_generationTypeCmd->AvailableForStates(G4State_PreInit, G4State_Idle);

  m_ar37CalibCmd = new G4UIcmdWithABool("/det/garfield/ar37Calib", this);
  m_ar37CalibCmd->SetGuidance("Turn Argon-37 calibration on (1) or off (0).");
  m_ar37CalibCmd->SetGuidance("(For \"HEED\" generation type only)");
  m_ar37CalibCmd->SetParameterName("State", false, false);
  m_ar37CalibCmd->AvailableForStates(G4State_PreInit, G4State_Idle);

  m_nElecCmd = new G4UIcmdWithAnInteger("/det/garfield/nElec", this);
  m_nElecCmd->SetGuidance("Set number of initial electrons.");
  m_nElecCmd->SetGuidance("(For \"Electrons\" generation type only)");
  m_nElecCmd->SetParameterName("nElec", false, false);
  m_nElecCmd->AvailableForStates(G4State_PreInit, G4State_Idle);

  m_gridPosCmd = new G4UIcmdWithAnInteger("/det/garfield/gridPos", this);
  m_gridPosCmd->SetGuidance("Set initial grid position (0-48).");
  m_gridPosCmd->SetGuidance("(For \"Electrons\" generation type only)");
  m_gridPosCmd->SetParameterName("GridPos", false, false);
  m_gridPosCmd->AvailableForStates(G4State_PreInit, G4State_Idle);
 
  m_avalTypeCmd = new G4UIcmdWithAString("/det/garfield/avalType", this);
  m_avalTypeCmd->SetGuidance("Set avalanche type.");
  m_avalTypeCmd->SetGuidance("Options are: Micro, MC and Custom");
  m_avalTypeCmd->SetParameterName("Type", false, false);
  m_avalTypeCmd->AvailableForStates(G4State_PreInit, G4State_Idle);
 
  m_avalMicMaxStateCmd = new G4UIcmdWithABool("/det/garfield/avalMicMaxState", this);
  m_avalMicMaxStateCmd->SetGuidance("Turn microscopic avalanche max gain on (1) or off (0).");
  m_avalMicMaxStateCmd->SetParameterName("State", false, false);
  m_avalMicMaxStateCmd->AvailableForStates(G4State_PreInit, G4State_Idle);
   
  m_avalMicMaxSizeCmd = new G4UIcmdWithAnInteger("/det/garfield/avalMicMaxSize", this);
  m_avalMicMaxSizeCmd->SetGuidance("Set microscopic avalanche max size.");
  m_avalMicMaxSizeCmd->SetParameterName("MaxAval", false, false);
  m_avalMicMaxSizeCmd->AvailableForStates(G4State_PreInit, G4State_Idle);
 
  m_avalMCStepTypeCmd = new G4UIcmdWithAString("/det/garfield/avalMCStepType", this);
  m_avalMCStepTypeCmd->SetGuidance("Set step type for MC avalanches.");
  m_avalMCStepTypeCmd->SetGuidance("Options are: nColl, tStep and dStep");
  m_avalMCStepTypeCmd->SetParameterName("Type", false, false);
  m_avalMCStepTypeCmd->AvailableForStates(G4State_PreInit, G4State_Idle);
   
  m_avalMCnCollCmd = new G4UIcmdWithAnInteger("/det/garfield/avalMCnColl", this);
  m_avalMCnCollCmd->SetGuidance("Set number of collisions step size for MC avalanches.");
  m_avalMCnCollCmd->SetParameterName("nColl", false, false);
  m_avalMCnCollCmd->AvailableForStates(G4State_PreInit, G4State_Idle);
   
  m_avalMCStepSizeCmd = new G4UIcmdWithADoubleAndUnit("/det/garfield/avalMCStepSize", this);
  m_avalMCStepSizeCmd->SetGuidance("Set MC avalanche step size.");
  m_avalMCStepSizeCmd->SetGuidance("(Make sure to specify time units if using tStep)");
  m_avalMCStepSizeCmd->SetDefaultUnit("cm");
  m_avalMCStepSizeCmd->SetParameterName("StepSize", false, false);
  m_avalMCStepSizeCmd->AvailableForStates(G4State_PreInit, G4State_Idle);
 
  m_avalCustomStepSizeCmd = new G4UIcmdWithADoubleAndUnit("/det/garfield/avalCustomStepSize", this);
  m_avalCustomStepSizeCmd->SetGuidance("Set custom avalanche step size.");
  m_avalCustomStepSizeCmd->SetDefaultUnit("cm");
  m_avalCustomStepSizeCmd->SetParameterName("StepSize", false, false);
  m_avalCustomStepSizeCmd->AvailableForStates(G4State_PreInit, G4State_Idle);
 
  m_setIonMobCmd = new G4UIcmdWithAString("/det/garfield/setIonMob", this);
  m_setIonMobCmd->SetGuidance("Set ion mobility directory.");
  m_setIonMobCmd->SetGuidance("Options are: BasicMobility, . (i.e current directory - for condor)");
  m_setIonMobCmd->SetParameterName("Type", false, false);
  m_setIonMobCmd->AvailableForStates(G4State_PreInit, G4State_Idle);

  m_setGasCmd = new G4UIcmdWithAString("/det/garfield/setGas", this);
  m_setGasCmd->SetGuidance("Set gas composition.");
  m_setGasCmd->SetGuidance("Options are: Sedine2018, SedineOld, ....");
  m_setGasCmd->SetParameterName("Gas", false, false);
  m_setGasCmd->AvailableForStates(G4State_PreInit, G4State_Idle);
   
  m_setSensorCmd = new G4UIcmdWithAString("/det/garfield/setSensor", this);
  m_setSensorCmd->SetGuidance("Set anode sensor.");
  m_setSensorCmd->SetGuidance("Options are: BasicSensor and UmbrellaSensor");
  m_setSensorCmd->SetParameterName("Type", false, false);
  m_setSensorCmd->AvailableForStates(G4State_PreInit, G4State_Idle);
   
  m_diffusionCmd = new G4UIcmdWithABool("/det/garfield/diffusion", this);
  m_diffusionCmd->SetGuidance("Turn diffusion on (1) or off (0).");
  m_diffusionCmd->SetParameterName("State", false, false);
  m_diffusionCmd->AvailableForStates(G4State_PreInit, G4State_Idle);
   
  m_ionTrackCmd = new G4UIcmdWithABool("/det/garfield/ionTrack", this);
  m_ionTrackCmd->SetGuidance("Turn ion tracking on (1) or off (0).");
  m_ionTrackCmd->SetParameterName("State", false, false);
  m_ionTrackCmd->AvailableForStates(G4State_PreInit, G4State_Idle);

  m_ionDriftTypeCmd = new G4UIcmdWithAString("/det/garfield/ionDriftType", this);
  m_ionDriftTypeCmd->SetGuidance("Set ion drift type.");
  m_ionDriftTypeCmd->SetGuidance("Options are: RKF and MC");
  m_ionDriftTypeCmd->SetParameterName("Type", false, false);
  m_ionDriftTypeCmd->AvailableForStates(G4State_PreInit, G4State_Idle);
   
  m_doSignalCmd = new G4UIcmdWithABool("/det/garfield/doSignal", this);
  m_doSignalCmd->SetGuidance("Turn signal calculation on (1) or off (0).");
  m_doSignalCmd->SetParameterName("State", false, false);
  m_doSignalCmd->AvailableForStates(G4State_PreInit, G4State_Idle);
   
  m_setSignalBinSizeCmd = new G4UIcmdWithADoubleAndUnit("/det/garfield/setSignalBinSize", this);
  m_setSignalBinSizeCmd->SetGuidance("Set the signal binning size.");
  m_setSignalBinSizeCmd->SetDefaultUnit("ns");
  m_setSignalBinSizeCmd->SetParameterName("Size", false, false);
  m_setSignalBinSizeCmd->AvailableForStates(G4State_PreInit, G4State_Idle);

  m_doPulseCmd = new G4UIcmdWithABool("/det/garfield/doPulse", this);
  m_doPulseCmd->SetGuidance("Turn pulse calculation on (1) or off (0).");
  m_doPulseCmd->SetParameterName("State", false, false);
  m_doPulseCmd->AvailableForStates(G4State_PreInit, G4State_Idle);
 
  m_setnSignalBinsCmd = new G4UIcmdWithAnInteger("/det/garfield/setnSignalBins", this);
  m_setnSignalBinsCmd->SetGuidance("Set the number of signal bins.");
  m_setnSignalBinsCmd->SetParameterName("nBins", false, false);
  m_setnSignalBinsCmd->AvailableForStates(G4State_PreInit, G4State_Idle);

  m_singleElecCmd = new G4UIcmdWithABool("/det/garfield/singleElec", this);
  m_singleElecCmd->SetGuidance("Turn single electron setting on (1) or off (0).");
  m_singleElecCmd->SetParameterName("State", false, false);
  m_singleElecCmd->AvailableForStates(G4State_PreInit, G4State_Idle);
   
  m_singleIonCmd = new G4UIcmdWithABool("/det/garfield/singleIon", this);
  m_singleIonCmd->SetGuidance("Turn single ion setting on (1) or off (0).");
  m_singleIonCmd->SetParameterName("State", false, false);
  m_singleIonCmd->AvailableForStates(G4State_PreInit, G4State_Idle);

  m_fieldPlotCmd = new G4UIcmdWithABool("/det/garfield/fieldPlot", this);
  m_fieldPlotCmd->SetGuidance("Turn field comparison plot on (1) or off (0).");
  m_fieldPlotCmd->SetParameterName("State", false, false);
  m_fieldPlotCmd->AvailableForStates(G4State_PreInit, G4State_Idle);

  m_setWValueCmd = new G4UIcmdWithADoubleAndUnit("/det/garfield/setWValue", this);
  m_setWValueCmd->SetGuidance("Set the W value of the gas (eV).");
  m_setWValueCmd->SetDefaultUnit("eV");
  m_setWValueCmd->SetParameterName("Value", false, false);
  m_setWValueCmd->AvailableForStates(G4State_PreInit, G4State_Idle);

  m_setFanoFactorCmd = new G4UIcmdWithADouble("/det/garfield/setFanoFactor", this);
  m_setFanoFactorCmd->SetGuidance("Set the Fano factor of the gas.");
  m_setFanoFactorCmd->SetParameterName("Value", false, false);
  m_setFanoFactorCmd->AvailableForStates(G4State_PreInit, G4State_Idle);

  m_debugCmd = new G4UIcmdWithAnInteger("/det/garfield/debug", this);
  m_debugCmd->SetGuidance("Set debug level.");
  m_debugCmd->SetGuidance("Options: 0 (min), 1, 2 (max)");
  m_debugCmd->SetParameterName("Level", false, false);
  m_debugCmd->AvailableForStates(G4State_PreInit, G4State_Idle);

  m_safetyCounterCmd = new G4UIcmdWithABool("/det/garfield/safetyCounter", this);
  m_safetyCounterCmd->SetGuidance("Turn the safety counter in electron avalanche on (1) or off (0).");
  m_safetyCounterCmd->SetParameterName("State", false, false);
  m_safetyCounterCmd->AvailableForStates(G4State_PreInit, G4State_Idle);

  m_pressureCmd = new G4UIcmdWithADouble("/det/garfield/setPressure", this);
  m_pressureCmd->SetGuidance("Set the pressure of the gas in Garfield in Torr - note that Geant4 needs to be hardcoded");
  m_pressureCmd->SetParameterName("Pressure", false, false);
  m_pressureCmd->AvailableForStates(G4State_PreInit, G4State_Idle);
}
 


DetectorConstructionMessenger::~DetectorConstructionMessenger()
{
  delete m_updateCmd;
  delete m_generationTypeCmd;
  delete m_ar37CalibCmd;
  delete m_nElecCmd;
  delete m_gridPosCmd;
  delete m_avalTypeCmd;
  delete m_avalMicMaxStateCmd;
  delete m_avalMicMaxSizeCmd;
  delete m_avalMCStepTypeCmd;
  delete m_avalMCnCollCmd;
  delete m_avalMCStepSizeCmd;
  delete m_avalCustomStepSizeCmd;
  delete m_setGasCmd;
  delete m_setIonMobCmd;
  delete m_setSensorCmd;
  delete m_diffusionCmd;
  delete m_ionTrackCmd;
  delete m_ionDriftTypeCmd;
  delete m_doSignalCmd;
  delete m_doPulseCmd;
  delete m_setSignalBinSizeCmd;
  delete m_setnSignalBinsCmd;
  delete m_singleElecCmd;
  delete m_singleIonCmd;
  delete m_fieldPlotCmd;
  delete m_setWValueCmd;
  delete m_setFanoFactorCmd;
  delete m_debugCmd;
  delete m_safetyCounterCmd;
  delete m_pressureCmd;
  delete m_garfieldDir;
  delete m_detDir;
}
 


void DetectorConstructionMessenger::SetNewValue(G4UIcommand* command, G4String newValue)
{     
  if(command == m_updateCmd)
    m_detectorConstruction->UpdateGeometry(); 
 
  // Garfield++ Commands
 
  if(command == m_generationTypeCmd)
    {m_detectorConstruction->SetGenerationType(newValue);}
  if(command == m_ar37CalibCmd)
    {m_detectorConstruction->SetAr37Calib(m_ar37CalibCmd->GetNewBoolValue(newValue));}
  if(command == m_nElecCmd)
    {m_detectorConstruction->SetnElec(m_nElecCmd->GetNewIntValue(newValue));}
  if(command == m_gridPosCmd)
    {m_detectorConstruction->SetGridPos(m_gridPosCmd->GetNewIntValue(newValue));}
  if(command == m_avalTypeCmd)
    {m_detectorConstruction->SetAvalType(newValue);}
  if(command == m_avalMicMaxStateCmd)
    {m_detectorConstruction->SetMicroMaxState(m_avalMicMaxStateCmd->GetNewBoolValue(newValue));}
  if(command == m_avalMicMaxSizeCmd)
    {m_detectorConstruction->SetMicroMaxSize(m_avalMicMaxSizeCmd->GetNewIntValue(newValue));}
  if(command == m_avalMCStepTypeCmd)
    {m_detectorConstruction->SetMCStepType(newValue);}
  if(command == m_avalMCnCollCmd)
    {m_detectorConstruction->SetMCnColl(m_avalMCnCollCmd->GetNewIntValue(newValue));}
  if(command == m_avalMCStepSizeCmd)
    {m_detectorConstruction->SetMCStepSize(m_avalMCStepSizeCmd->GetNewDoubleValue(newValue));}
  if(command == m_avalCustomStepSizeCmd)
    {m_detectorConstruction->SetCustomStepSize(m_avalCustomStepSizeCmd->GetNewDoubleValue(newValue));}
  if(command == m_setGasCmd)
    {m_detectorConstruction->SetGas(newValue);}
  if(command == m_setIonMobCmd)
    {m_detectorConstruction->SetIonMobDir(newValue);}
  if(command == m_setSensorCmd)
    {m_detectorConstruction->SetSensorDir(newValue);}
  if(command == m_diffusionCmd)
    {m_detectorConstruction->SetDiffusion(m_diffusionCmd->GetNewBoolValue(newValue));}
  if(command == m_ionTrackCmd)
    {m_detectorConstruction->SetIonTracking(m_ionTrackCmd->GetNewBoolValue(newValue));}
  if(command == m_ionDriftTypeCmd)
    {m_detectorConstruction->SetIonDriftType(newValue);}
  if(command == m_doSignalCmd)
    {m_detectorConstruction->SetSignalCalc(m_doSignalCmd->GetNewBoolValue(newValue));}
  if(command == m_doPulseCmd)
    {m_detectorConstruction->SetPulseCalc(m_doPulseCmd->GetNewBoolValue(newValue));}
  if(command == m_setSignalBinSizeCmd)
    {m_detectorConstruction->SetSignalBinSize(m_setSignalBinSizeCmd->GetNewDoubleValue(newValue));}
  if(command == m_setnSignalBinsCmd)
    {m_detectorConstruction->SetSignalnBins(m_setnSignalBinsCmd->GetNewIntValue(newValue));}
  if(command == m_singleElecCmd)
    {m_detectorConstruction->SetSingleElec(m_singleElecCmd->GetNewBoolValue(newValue));}
  if(command == m_singleIonCmd)
    {m_detectorConstruction->SetSingleIon(m_singleIonCmd->GetNewBoolValue(newValue));}
  if(command == m_fieldPlotCmd)
    {m_detectorConstruction->SetFieldPlot(m_fieldPlotCmd->GetNewBoolValue(newValue));}
  if(command == m_setWValueCmd)
    {m_detectorConstruction->SetWValue(m_setWValueCmd->GetNewDoubleValue(newValue));}
  if(command == m_setFanoFactorCmd)
    {m_detectorConstruction->SetFanoFactor(m_setFanoFactorCmd->GetNewDoubleValue(newValue));}
  if(command == m_debugCmd)
    {m_detectorConstruction->SetDebug(m_debugCmd->GetNewIntValue(newValue));}
  if(command == m_safetyCounterCmd)
    {m_detectorConstruction->SetSafetyCounter(m_safetyCounterCmd->GetNewBoolValue(newValue));}
  if(command == m_pressureCmd)
    {m_detectorConstruction->SetPressure(m_pressureCmd->GetNewDoubleValue(newValue));}
}


// ====== Commented out commands from constructor ======

// ConverterThickCmd = new G4UIcmdWithADoubleAndUnit("/det/setConverterThick",this);
  // ConverterThickCmd->SetGuidance("Set Thickness of converter");
  // ConverterThickCmd->SetParameterName("SizeZ",false,false);
  // ConverterThickCmd->SetDefaultUnit("mm");
  // ConverterThickCmd->SetRange("SizeZ>0.");
  // ConverterThickCmd->AvailableForStates(G4State_Idle);
 
  // RotationCmd = new G4UIcmdWithADoubleAndUnit("/det/setRotation",this);
  // RotationCmd->SetGuidance("Set Rotation");
  // RotationCmd->SetParameterName("Rot",false,false);
  // RotationCmd->SetDefaultUnit("deg");
  // RotationCmd->AvailableForStates(G4State_Idle);
 
  // GapCmd = new G4UIcmdWithADoubleAndUnit("/det/setGap",this);
  // GapCmd->SetGuidance("Set Gap");
  // GapCmd->SetParameterName("Gap",false,false);
  // GapCmd->SetDefaultUnit("mm");
  // GapCmd->AvailableForStates(G4State_Idle);
 
  // GapXCmd = new G4UIcmdWithADoubleAndUnit("/det/setGapX",this);
  // GapXCmd->SetGuidance("Set GapX");
  // GapXCmd->SetParameterName("GapX",false,false);
  // GapXCmd->SetDefaultUnit("mm");
  // GapXCmd->AvailableForStates(G4State_Idle);
 
  // ConverterMatCmd = new G4UIcmdWithAString("/det/setConverterMaterial",this);
  // ConverterMatCmd->SetGuidance("Set Material of converter");
  // ConverterMatCmd->SetParameterName("Mat",false,false);
  // ConverterMatCmd->AvailableForStates(G4State_Idle);
 
  // DetectorMatCmd = new G4UIcmdWithAString("/det/setDetectorMaterial",this);
  // DetectorMatCmd->SetGuidance("Set Material of detector");
  // DetectorMatCmd->SetParameterName("Mat",false,false);
  // DetectorMatCmd->AvailableForStates(G4State_Idle);
  


// ====== Commented commands from destructor ======

  // delete ConverterThickCmd; 
  // delete RotationCmd;
  // delete GapCmd;
  // delete GapXCmd;
  // delete ConverterMatCmd; 
  // delete DetectorMatCmd; 



// ====== Commented code from SetNewValue(...) ======

  // if( command == ConverterThickCmd )
  //   { m_detectorConstruction->SetConverterThickness(ConverterThickCmd->GetNewDoubleValue(newValue));}
  // if( command == RotationCmd )
  //   { m_detectorConstruction->SetRotation(RotationCmd->GetNewDoubleValue(newValue));}
  // if( command == GapCmd )
  //   { m_detectorConstruction->SetGap(GapCmd->GetNewDoubleValue(newValue));}
  // if( command == GapXCmd )
  //   { m_detectorConstruction->SetGapX(GapXCmd->GetNewDoubleValue(newValue));}
  // if( command == ConverterMatCmd )
  //   { m_detectorConstruction->SetConverterMaterial(newValue);}
  // if( command == DetectorMatCmd )
  //   { m_detectorConstruction->SetDetectorMaterial(newValue);}
