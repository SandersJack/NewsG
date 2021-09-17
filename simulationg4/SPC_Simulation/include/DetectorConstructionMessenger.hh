#ifndef DetectorConstructionMessenger_h
#define DetectorConstructionMessenger_h 1

#include "globals.hh"
#include "G4UImessenger.hh"

class DetectorConstruction;
class G4UIdirectory;
class G4UIcmdWithAnInteger;
class G4UIcmdWithADoubleAndUnit;
class G4UIcmdWithADouble;
class G4UIcmdWithAString;
class G4UIcmdWithoutParameter;
class G4UIcmdWithABool;
//class G4UIcmdWith3VectorAndUnit;



class DetectorConstructionMessenger: public G4UImessenger
{
public:
  explicit DetectorConstructionMessenger(DetectorConstruction* );
  ~DetectorConstructionMessenger();

  void SetNewValue(G4UIcommand*, G4String) override;

private:
  DetectorConstruction*      m_detectorConstruction;
  G4UIdirectory*             m_detDir;
  G4UIcmdWithoutParameter*   m_updateCmd;

  //Garfield++ simulation commands
  G4UIdirectory*             m_garfieldDir;
  G4UIcmdWithAString*        m_generationTypeCmd;
  G4UIcmdWithAString*        m_avalTypeCmd;
  G4UIcmdWithAString*        m_avalMCStepTypeCmd;
  G4UIcmdWithAString*        m_setIonMobCmd;
  G4UIcmdWithAString*        m_setGasCmd;
  G4UIcmdWithAString*        m_setSensorCmd;
  G4UIcmdWithAString*        m_ionDriftTypeCmd;
  G4UIcmdWithADoubleAndUnit* m_avalMCStepSizeCmd;
  G4UIcmdWithADoubleAndUnit* m_avalCustomStepSizeCmd;
  G4UIcmdWithADoubleAndUnit* m_setSignalBinSizeCmd;
  G4UIcmdWithADoubleAndUnit* m_setWValueCmd;
  G4UIcmdWithADouble*        m_setFanoFactorCmd;
  G4UIcmdWithAnInteger*      m_setnSignalBinsCmd;
  G4UIcmdWithAnInteger*      m_gridPosCmd;
  G4UIcmdWithAnInteger*      m_nElecCmd;
  G4UIcmdWithAnInteger*      m_avalMCnCollCmd;
  G4UIcmdWithAnInteger*      m_avalMicMaxSizeCmd;
  G4UIcmdWithAnInteger*      m_debugCmd;
  G4UIcmdWithABool*          m_ar37CalibCmd;
  G4UIcmdWithABool*          m_diffusionCmd;
  G4UIcmdWithABool*          m_ionTrackCmd;
  G4UIcmdWithABool*          m_doSignalCmd;
  G4UIcmdWithABool*          m_doPulseCmd;
  G4UIcmdWithABool*          m_singleIonCmd;
  G4UIcmdWithABool*          m_singleElecCmd;
  G4UIcmdWithABool*          m_avalMicMaxStateCmd;
  G4UIcmdWithABool*          m_fieldPlotCmd;
  G4UIcmdWithABool*          m_safetyCounterCmd;
  G4UIcmdWithABool*          m_idealFieldCmd;
  G4UIcmdWithABool*          m_useGarfieldCmd;
  G4UIcmdWithADouble*        m_pressureCmd;
  G4UIcmdWithAString*        m_cathodeMaterialCmd;
  G4UIcmdWithAString*        m_defaultMaterialCmd;
  G4UIcmdWithAString*        m_srimFileCmd;

  //  G4UIcmdWithADoubleAndUnit* m_detectorRadius;
  // G4UIcmdWithADoubleAndUnit* m_anodeRadius;
};

#endif //DetectorConstructionMessenger_h


// Commented out commands from Gamma Camera

// G4UIcmdWithADoubleAndUnit* ConverterThickCmd;
// G4UIcmdWithADoubleAndUnit* RotationCmd;
// G4UIcmdWithADoubleAndUnit* GapCmd;
// G4UIcmdWithADoubleAndUnit* GapXCmd;
// G4UIcmdWithAString* ConverterMatCmd;
// G4UIcmdWithAString* DetectorMatCmd;
