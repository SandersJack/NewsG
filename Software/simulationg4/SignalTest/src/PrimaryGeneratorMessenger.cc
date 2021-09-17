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
/// \file electromagnetic/TestEm5/src/PrimaryGeneratorMessenger.cc
/// \brief Implementation of the PrimaryGeneratorMessenger class
//
// $Id: PrimaryGeneratorMessenger.cc 67268 2013-02-13 11:38:40Z ihrivnac $
//

#include "PrimaryGeneratorMessenger.hh"

#include "PrimaryGeneratorAction.hh"
#include "G4UIdirectory.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcmdWithAnInteger.hh"
#include "G4UIcmdWith3VectorAndUnit.hh"
#include "G4UIcmdWith3Vector.hh"
//#include "G4UIcmdWithADouble.hh"
//#include "G4UIcmdWithoutParameter.hh"


PrimaryGeneratorMessenger::PrimaryGeneratorMessenger(PrimaryGeneratorAction* gun)
  :m_primaryGeneratorAction(gun)
{
  m_gunDir = new G4UIdirectory("/gun/");
  m_gunDir->SetGuidance("Primary generator action commands.");
 
  m_initialParticleCmd = new G4UIcmdWithAString("/gun/initialParticle", this);
  m_initialParticleCmd->SetGuidance("Set the initial particle type.");
  m_initialParticleCmd->SetGuidance("Options are: e-, proton, photon, neutron, alpha, He4+");
  m_initialParticleCmd->SetParameterName("type",false,false);
  m_initialParticleCmd->AvailableForStates(G4State_PreInit, G4State_Idle);

  m_initialEnergyCmd = new G4UIcmdWithADoubleAndUnit("/gun/initialEnergy",this);
  m_initialEnergyCmd->SetGuidance("Set the energy of the initial particle.");
  m_initialEnergyCmd->SetGuidance("Default unit is: keV");
  m_initialEnergyCmd->SetParameterName("energy",false,false);
  m_initialEnergyCmd->SetRange("energy>0.");
  m_initialEnergyCmd->SetDefaultUnit("keV");
  m_initialEnergyCmd->AvailableForStates(G4State_PreInit, G4State_Idle);   

  m_minRadiusCmd = new G4UIcmdWithADoubleAndUnit("/gun/minRadius", this);
  m_minRadiusCmd->SetGuidance("Set the minimum radius for random generation.");
  m_minRadiusCmd->SetParameterName("minimum", false, false);
  m_minRadiusCmd->SetDefaultUnit("cm");
  m_minRadiusCmd->SetRange("minimum>0.");
  m_minRadiusCmd->AvailableForStates(G4State_PreInit, G4State_Idle);   
  
  m_maxRadiusCmd = new G4UIcmdWithADoubleAndUnit("/gun/maxRadius", this);
  m_maxRadiusCmd->SetGuidance("Set the maximum radius for random generation.");
  m_maxRadiusCmd->SetParameterName("maximum", false, false);
  m_maxRadiusCmd->SetDefaultUnit("cm");
  m_maxRadiusCmd->SetRange("maximum>0.");
  m_maxRadiusCmd->AvailableForStates(G4State_PreInit, G4State_Idle);   
  
  m_nInitialParticlesCmd = new G4UIcmdWithAnInteger("/gun/nInitParticles", this);
  m_nInitialParticlesCmd->SetGuidance("Set the number of initial particles.");
  m_nInitialParticlesCmd->SetParameterName("number", false, false);
  m_nInitialParticlesCmd->SetRange("number>0");
  m_nInitialParticlesCmd->AvailableForStates(G4State_PreInit, G4State_Idle);   

  m_initialPositionCartesianCmd = new G4UIcmdWith3VectorAndUnit("/gun/initialPositionCartesian", this);
  m_initialPositionCartesianCmd->SetGuidance("Set the inital position of the initial particle.");
  m_initialPositionCartesianCmd->SetGuidance("Cartesian co-ordinates (x, y, z).");
  m_initialPositionCartesianCmd->SetGuidance("Note: Bar is along negative y-axis; default unit is cm");
  m_initialPositionCartesianCmd->SetParameterName("x", "y", "z", false, false);
  m_initialPositionCartesianCmd->SetDefaultUnit("cm");
  m_initialPositionCartesianCmd->AvailableForStates(G4State_PreInit, G4State_Idle);

  m_initialPositionSphericalCmd = new G4UIcmdWith3VectorAndUnit("/gun/initialPositionSpherical", this);
  m_initialPositionSphericalCmd->SetGuidance("Set the inital position of the initial particle.");
  m_initialPositionSphericalCmd->SetGuidance("Cartesian co-ordinates (r, theta, phi).");
  m_initialPositionSphericalCmd->SetGuidance("theta and phi are in degrees.");
  m_initialPositionSphericalCmd->SetGuidance("Note: Bar is along negative y-axis; default unit is cm");
  m_initialPositionSphericalCmd->SetParameterName("r", "theta", "phi", false, false);
  m_initialPositionSphericalCmd->SetDefaultUnit("cm");
  m_initialPositionSphericalCmd->AvailableForStates(G4State_PreInit, G4State_Idle);

  m_initialDirectionCartesianCmd = new G4UIcmdWith3Vector("/gun/initialDirectionCartesian", this);
  m_initialDirectionCartesianCmd->SetGuidance("Set the inital position of the initial particle.");
  m_initialDirectionCartesianCmd->SetGuidance("Cartesian co-ordinates (x, y, z).");
  m_initialDirectionCartesianCmd->SetParameterName("x", "y", "z", false, false);
  m_initialDirectionCartesianCmd->AvailableForStates(G4State_PreInit, G4State_Idle);

  m_initialDirectionSphericalCmd = new G4UIcmdWith3Vector("/gun/initialDirectionSpherical", this);
  m_initialDirectionSphericalCmd->SetGuidance("Set the inital direction of the initial particle.");
  m_initialDirectionSphericalCmd->SetGuidance("Spherical co-ordinates (r, theta, phi).");
  m_initialDirectionSphericalCmd->SetGuidance("theta and phi are in degrees.");
  m_initialDirectionSphericalCmd->SetParameterName("r", "theta", "phi", false, false);
  m_initialDirectionSphericalCmd->AvailableForStates(G4State_PreInit, G4State_Idle);
}



PrimaryGeneratorMessenger::~PrimaryGeneratorMessenger()
{
  delete m_initialParticleCmd;
  delete m_initialEnergyCmd;
  delete m_minRadiusCmd;
  delete m_maxRadiusCmd;
  delete m_nInitialParticlesCmd;
  delete m_initialPositionCartesianCmd;
  delete m_initialPositionSphericalCmd;
  delete m_initialDirectionCartesianCmd;
  delete m_initialDirectionSphericalCmd;
  delete m_gunDir;    
}



void PrimaryGeneratorMessenger::SetNewValue(G4UIcommand* command, G4String newValue)
{ 
  if (command == m_initialParticleCmd)
    {m_primaryGeneratorAction->SetInitialParticle(newValue);}
  if (command == m_initialEnergyCmd)
    {m_primaryGeneratorAction->SetEnergyBeam(m_initialEnergyCmd->GetNewDoubleValue(newValue));}       
  if (command == m_minRadiusCmd)
    {m_primaryGeneratorAction->SetMinGenerationRadius(m_minRadiusCmd->GetNewDoubleValue(newValue));}
  if (command == m_maxRadiusCmd)
    {m_primaryGeneratorAction->SetMaxGenerationRadius(m_maxRadiusCmd->GetNewDoubleValue(newValue));}
  if (command == m_nInitialParticlesCmd)
    {m_primaryGeneratorAction->SetnInitialParticles(m_nInitialParticlesCmd->GetNewIntValue(newValue));}
  if (command == m_initialPositionCartesianCmd)
    {m_primaryGeneratorAction->SetInitialPositionCartesian(m_initialPositionCartesianCmd->GetNew3VectorValue(newValue));}
  if (command == m_initialPositionSphericalCmd)
    {m_primaryGeneratorAction->SetInitialPositionSpherical(m_initialPositionSphericalCmd->GetNew3VectorValue(newValue), m_initialPositionSphericalCmd->GetNewUnitValue(newValue));}
  if (command == m_initialDirectionCartesianCmd)
    {m_primaryGeneratorAction->SetInitialDirectionCartesian(m_initialDirectionCartesianCmd->GetNew3VectorValue(newValue));}
  if (command == m_initialDirectionSphericalCmd)
    {m_primaryGeneratorAction->SetInitialDirectionSpherical(m_initialDirectionSphericalCmd->GetNew3VectorValue(newValue));}
}
