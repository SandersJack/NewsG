//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
// $Id: DetectorConstruction.hh 71079 2013-06-10 20:37:11Z ihrivnac $
//
/// \file DetectorConstruction.hh
/// \brief Definition of the DetectorConstruction class

#ifndef DetectorConstruction_h
#define DetectorConstruction_h 1

#include "G4VUserDetectorConstruction.hh"
#include "DetectorConstructionMessenger.hh"
#include "globals.hh"

#include "PrimaryGeneratorAction.hh"
#include "UserG4FastSimulationModel.hh"
#include "InitialisationParameters.hh"

#include "G4RunManager.hh"
#include "G4NistManager.hh"

#include <string>

class G4VPhysicalVolume;
class G4LogicalVolume;
class G4Material;
class GasMixture;
class FieldMap;

/// Detector construction class to define materials and geometry.

class DetectorConstruction: public G4VUserDetectorConstruction
{
public:
  explicit DetectorConstruction(PrimaryGeneratorAction*);
  virtual ~DetectorConstruction();

  // Methods required by Geant4
  virtual G4VPhysicalVolume* Construct() override;
  virtual void ConstructSDandField() override;

  inline void UpdateGeometry(){G4RunManager::GetRunManager()->ReinitializeGeometry();}

  //Garfield++ Initialisation Commands
  inline void SetGenerationType(std::string type)   {m_initParams->SetGenerationType(type);}
  inline void SetAr37Calib(bool state)          {m_initParams->SetAr37Calib(state);}
  inline void SetnElec(int nElec)               {m_initParams->SetnElec(nElec);}
  inline void SetGridPos(int gridPos)           {m_initParams->SetGridPos(gridPos);}
  inline void SetAvalType(std::string type)         {m_initParams->SetAvalType(type);}
  inline void SetMicroMaxState(bool state)      {m_initParams->SetMicroMaxState(state);}
  inline void SetMicroMaxSize(int avalSize)     {m_initParams->SetMicroMaxSize(avalSize);}
  inline void SetMCStepType(std::string type)       {m_initParams->SetMCStepType(type);}
  inline void SetMCnColl(int nColl)             {m_initParams->SetMCnColl(nColl);}
  inline void SetMCStepSize(double stepSize)    {m_initParams->SetMCStepSize(stepSize);}
  inline void SetCustomStepSize(double stepSize){m_initParams->SetCustomStepSize(stepSize);}
  inline void SetIonMobDir(std::string ionMobDir)   {m_initParams->SetIonMobDir(ionMobDir);}
  void SetSensorDir(std::string sensorDir);
  inline void SetDiffusion(bool state)          {m_initParams->SetDiffusion(state);}
  inline void SetIonTracking(bool state)        {m_initParams->SetIonTracking(state);}
  inline void SetIonDriftType(std::string type)     {m_initParams->SetIonDriftType(type);}
  inline void SetSignalCalc(bool state)         {m_initParams->SetSignalCalc(state);}
  inline void SetPulseCalc(bool state)          {m_initParams->SetPulseCalc(state);}
  inline void SetSignalBinSize(double size)     {m_initParams->SetSignalBinSize(size);}
  inline void SetSignalnBins(int nBins)         {m_initParams->SetSignalnBins(nBins);}
  inline void SetSingleElec(bool state)         {m_initParams->SetSingleElec(state);}
  inline void SetSingleIon(bool state)          {m_initParams->SetSingleIon(state);}
  inline void SetFieldPlot(bool state)          {m_initParams->SetFieldPlot(state);}
  inline void SetWValue(double value)           {m_initParams->SetWValue(value);}
  inline void SetFanoFactor(double value)       {m_initParams->SetFanoFactor(value);}
  inline void SetDebug(int level)               {m_initParams->SetDebug(level);}
  inline void SetSafetyCounter(bool state)      {m_initParams->SetSafetyCounter(state);}
  inline void SetPressure(double pressure)      {m_initParams->SetPressure(pressure);}
  inline void SetIdealField(bool state)         {m_initParams->SetIdealField(state);}
  inline void SetUseGarfield(bool state)        {m_initParams->SetUseGarfield(state);}
  inline void SetCathodeMaterial(std::string material) {
    m_cathodeMatName = material;
  }
  inline void SetDefaultMaterial(std::string material) {
    m_defaultMatName = material;
  }

  inline void SetDetectorRadius(double detectorRadius){m_initParams->SetDetectorRadius(detectorRadius);}

  inline void SetAnodeRadius(double anodeRadius){m_initParams->SetAnodeRadius(anodeRadius);}

  inline void SetSrimFile(std::string file){m_initParams->SetSrimFile(file);}

  void SetGas(std::string gasType);

  GasMixture* GetGasMixture() { return m_gas_mixture; }
  FieldMap* GetFieldMap() { return m_field_map; }

private:
  G4NistManager* nist;

  G4bool fCheckOverlaps;
  G4bool fStdConv;
  G4int  fNx;
  PrimaryGeneratorAction* primAction;

  //Garfield++ model initialisation parameters
  InitialisationParameters* m_initParams;

  DetectorConstructionMessenger* detectorConstructionMessenger;

  G4double fConverterThick;
  G4double fRotation;
  G4double fGap;
  G4double fGap_x;
  G4String fConverterMat;
  G4String fDetectorMat;

  G4int constructNBLM(G4LogicalVolume* World_log);
  void DefineMaterials();
  void SetGasMixture();
  G4double shieldingZ,leadZ,cadmiumZ,sourceZ;
  G4double fdriftDist, fpolyThickness1, fpolyThickness2, fCdThickness, fB4C_z, perAr, fAl_2_Thickness;
  G4bool fGasMixtureModified, fGeometryModified;
  G4ThreeVector sourcePosition;
  std::string m_cathodeMatName;
  std::string m_defaultMatName = "G4_AIR";
  GasMixture* m_gas_mixture = nullptr;
  FieldMap* m_field_map = nullptr;
};

#endif



// Commented out public function declarations

// void SetConverterThickness(G4double);
// void SetConverterMaterial(G4String);
// void SetDetectorMaterial(G4String);
// void SetRotation(G4double);
// void SetGap(G4double);
// void SetGapX(G4double);

// void SetCdThickness(G4double);
// void SetPolyThickness1(G4double);
// void SetPolyThickness2(G4double);
// void SetDriftDistance(G4double);
// void SetB4CThickness(G4double);

// inline G4double GetCdThickness() {return fCdThickness;};
// inline G4double GetPolyThickness1() {return fpolyThickness1;};
// inline G4double GetPolyThickness2() {return fpolyThickness2;};
// inline G4double GetDriftDistance() {return fdriftDist;};
// inline G4double GetB4CThickness() {return fB4C_z;};


//void SetArPercentage(G4double z)  {perAr=z;fGasMixtureModified=true;}
//inline G4double GetArPercentage() {return perAr;};
