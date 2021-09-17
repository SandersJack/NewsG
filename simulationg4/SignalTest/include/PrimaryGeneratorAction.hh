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
// $Id: PrimaryGeneratorAction.hh 89901 2015-05-04 09:28:53Z ihrivnac $
//
/// \file PrimaryGeneratorAction.hh
/// \brief Definition of the PrimaryGeneratorAction class

#ifndef PrimaryGeneratorAction_h
#define PrimaryGeneratorAction_h 1

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4ParticleGun.hh"
#include "globals.hh"

class G4ParticleGun;
class G4Event;
class TRandom3;
class PrimaryGeneratorMessenger;

class PrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
public:
  PrimaryGeneratorAction();    
  virtual ~PrimaryGeneratorAction();

  virtual void GeneratePrimaries(G4Event*) override;         

  inline const G4ParticleGun* GetParticleGun() const {return m_particleGun;}

  void SetEnergyBeam(G4double);
  void BeamPos(G4double);
  
  // Primary generator messenger commands
  inline void SetInitialParticle(G4String name)       {m_initialParticle = name;}
  inline void SetInitialEnergy(G4double energy)       {m_initialEnergy = energy;}
  inline void SetMinGenerationRadius(G4double radius) {m_minRadius = radius;}
  inline void SetMaxGenerationRadius(G4double radius) {m_maxRadius = radius;}
  inline void SetnInitialParticles(G4int number)      {m_nInitialParticles = number;}

  // Commands to set a specific starting position - if not used 
  // the position will be NULL and will be generated randomly 
  // instead, using the min and max generation radii
  void SetInitialPositionCartesian(G4ThreeVector position);
  void SetInitialPositionSpherical(G4ThreeVector position, G4double unit);
  void SetInitialDirectionCartesian(G4ThreeVector direction);
  void SetInitialDirectionSpherical(G4ThreeVector direction);

  void SetInitialPositionDirectionMuons();

private:
  // Primary generator messenger and variables
  PrimaryGeneratorMessenger* m_primaryGeneratorMessenger;
  
  G4String      m_initialParticle;
  G4double      m_initialEnergy;
  G4double      m_minRadius;
  G4double      m_maxRadius;
  G4int         m_nInitialParticles;
  G4ThreeVector m_initialPosition;
  G4ThreeVector m_initialDirection;

  G4ParticleGun*  m_particleGun;
  TRandom3* m_rndm;
};

#endif
