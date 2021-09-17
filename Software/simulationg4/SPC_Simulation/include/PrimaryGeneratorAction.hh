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
#include "TMath.h"

class G4ParticleGun;
class G4Event;
class PrimaryGeneratorMessenger;

class PrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
public:
  PrimaryGeneratorAction();
  virtual ~PrimaryGeneratorAction();

  virtual void GeneratePrimaries(G4Event*) override;

  inline const G4ParticleGun* GetParticleGun() const {return m_particleGun;}

  void SetEnergyBeam(G4double);
  void SetMinEnergyBeam(G4double);
  void SetMaxEnergyBeam(G4double);
  void BeamPos(G4double);

  // Primary generator messenger commands
  inline void SetInitialParticle(G4String name)       {m_initialParticle = name;}
  inline void SetInitialEnergy(G4double energy)       {m_initialEnergy = energy;}
  inline void SetMinGenerationRadius(G4double radius) {m_minRadius = radius;}
  inline void SetMaxGenerationRadius(G4double radius) {m_maxRadius = radius;}

  inline void SetMinGenerationCosTheta(G4double cos_theta) {m_minCosTheta = cos_theta;}
  inline void SetMaxGenerationCosTheta(G4double cos_theta) {m_maxCosTheta = cos_theta;}

  inline void SetnInitialParticles(G4int number)      {m_nInitialParticles = number;}
  // Commands to set initial particle energy from recoil distribution
  inline void SetEnergyFromRecoilSpectrum()           {m_recoilSpectrum=true;}
  inline void SetIncidentParticleMass(G4double mass)  {m_incidentParticleMass=mass;}

  // Commands to set a specific starting position - if not used
  // the position will be NULL and will be generated randomly
  // instead, using the min and max generation radii
  void SetInitialPositionCartesian(G4ThreeVector position);
  void SetInitialPositionSpherical(G4ThreeVector position, G4double unit);
  void SetInitialDirectionCartesian(G4ThreeVector direction);
  void SetInitialDirectionSpherical(G4ThreeVector direction);

  inline void SetInitialPositionDirectionMuons()      {m_muonPosDir = true;}
  inline void SetInitialDirectionRadial()             {m_radialDir = true;}

  //Functions to calculate the recoil energy spectrum
  // Lewin eqn 3.13/RO
  //double CalculatedRdEROverR0(double* x, double *par);
  double CalculatedRdEROverR0(double ER, double mX, double mT);
  // Lewin eqn 3.12/RO
  double CalculatedRdERVEaveVescInfOverR0(double ER, double mX, double mTm);
  double CalculateMassFactor(double mT, double mX){ return 4.*mX*mT/((mX+mT)*(mX+mT));}

private:
  // Primary generator messenger and variables
  PrimaryGeneratorMessenger* m_primaryGeneratorMessenger;

  G4String      m_initialParticle;
  G4double      m_initialEnergy;
  G4double      m_minEnergy = 0;
  G4double      m_maxEnergy = 1000;
  G4double      m_minRadius;
  G4double      m_maxRadius;
  // Min/max cos(theta) used for random generation
  G4double      m_minCosTheta = -1.0;
  G4double      m_maxCosTheta = +1.0;
  G4int         m_nInitialParticles;
  G4ThreeVector m_initialPosition;
  G4ThreeVector m_initialDirection;
  G4bool        m_randomPosition;
  G4bool        m_random_energy = false;
  G4bool        m_randomDirection;
  G4bool        m_muonPosDir;
  G4bool        m_radialDir;
  G4bool        m_recoilSpectrum;
  G4double      m_incidentParticleMass;

  G4double      m_lightSpeed    = 299792.458;// km/s
  G4double      m_oneOverc2     = 1./(m_lightSpeed*m_lightSpeed);// /km2 s2
  G4double      m_escVelocity   = 544.;//   km/s
  G4double      m_aveVelocity   = 220.;//   km/s
  G4double      m_earthVelocity = 232.;// km/s
  G4double     m_vEscRatio      = m_escVelocity/m_aveVelocity;
  G4double      m_vEarthRatio   = m_aveVelocity/m_earthVelocity;
  G4double      m_k0            = TMath::Power(TMath::Pi()*m_aveVelocity*m_aveVelocity, 3./2);// km^3/2 /s^3/2
  G4double      m_k1            = m_k0*(TMath::Erf(m_vEscRatio)-2*m_vEscRatio*TMath::Exp(-1.*m_vEscRatio*m_vEscRatio)/TMath::Sqrt(TMath::Pi()));// km^3/2 /s^3/2
  G4double      m_kRatio        = m_k0/m_k1;

  G4ParticleGun*  m_particleGun;

};

#endif
