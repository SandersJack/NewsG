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
// $Id: PrimaryGeneratorAction.cc 73744 2013-09-09 20:25:07Z asaim $
//
/// \file PrimaryGeneratorAction.cc
/// \brief Implementation of the PrimaryGeneratorAction class

#include "PrimaryGeneratorAction.hh"

#include "G4RunManager.hh"
#include "G4Event.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4IonTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4GenericIon.hh"
#include "G4SystemOfUnits.hh"
#include "Randomize.hh"

#include "PrimaryGeneratorMessenger.hh"

#include "TRandom3.h"
#include "TVector3.h"

PrimaryGeneratorAction::PrimaryGeneratorAction()
 : G4VUserPrimaryGeneratorAction(),
   m_initialParticle("proton"),
   m_initialEnergy(10*keV),
   m_minRadius(0.15*cm),
   m_maxRadius(29.999*cm),
   m_nInitialParticles(1),
   m_initialPosition(0,0,0),
   m_initialDirection(0,0,0)
{
  m_primaryGeneratorMessenger = new PrimaryGeneratorMessenger(this);
  m_particleGun = new G4ParticleGun(m_nInitialParticles);
  m_rndm = new TRandom3(0);
}



PrimaryGeneratorAction::~PrimaryGeneratorAction()
{
  delete m_primaryGeneratorMessenger;
  delete m_particleGun;
  delete m_rndm;
}



void PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
  // Particle options: GenericIon, proton, neutron, e-, alpha, gamma
  if (m_initialParticle == "He4+") 
    {
      //helium ion - can't define in constructor as ion table is not yet ready
      G4int Z = 2, A = 4;
      G4double ionCharge   = 1.*eplus;
      G4double excitEnergy = 54.4*eV;   //Second Ionisation energy
      G4ParticleDefinition* ion = G4IonTable::GetIonTable()->GetIon(Z,A,excitEnergy);
      m_particleGun->SetParticleDefinition(ion);
      m_particleGun->SetParticleCharge(ionCharge);
    }
  else{
    G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
    G4ParticleDefinition* particle = particleTable->FindParticle(m_initialParticle);
    m_particleGun->SetParticleDefinition(particle);
  }

  if(m_initialPosition.mag() < 1e-19)
    { 
      // Randomized position if initial position is at origin (default)
      double x0 = 0.*cm;
      double y0 = 0.*cm;
      double z0 = 0.*cm;
      do
	{
	  // double r0pos = (m_minRadius/cm + (m_maxRadius/cm - m_minRadius/cm)*std::cbrt(m_rndm->Uniform(0,1)))*cm;
	  //double minCubed = (m_minRadius/cm)*(m_minRadius/cm)*(m_minRadius/cm);	
	  //double r0pos = std::cbrt(3*m_rndm->Uniform(0,1)+ minCubed/3);
	  double minCubed = (m_minRadius/cm)*(m_minRadius/cm)*(m_minRadius/cm);	
	  double maxCubed = (m_maxRadius/cm)*(m_maxRadius/cm)*(m_maxRadius/cm);
	  double r0pos = std::cbrt(m_rndm->Uniform(minCubed,maxCubed))*cm;
	  // double r0pos = m_rndm->Uniform(m_minRadius/cm,m_maxRadius/cm)*cm; // Radius within detector <-- Uniform in radius
	  double phi0pos = m_rndm->Uniform(0,2.*acos(-1));
	  double cosTheta0pos = m_rndm->Uniform(-1,1);
	  x0=r0pos*sqrt(1-cosTheta0pos*cosTheta0pos)*cos(phi0pos);
	  y0=r0pos*sqrt(1-cosTheta0pos*cosTheta0pos)*sin(phi0pos);
	  z0=r0pos*cosTheta0pos;     
	}
      while(y0 < -0.15 && sqrt(x0*x0 + z0*z0) < 0.3); // Protection against initial position being in bar
    
      std::cout << "[PrimaryGeneratorAction] Initial Position is: x = " << x0/cm 
		<< " cm,\t y = " << y0/cm << " cm,\t z = " << z0/cm << " cm" << std::endl;
      
      G4ThreeVector initPosition(x0,y0,z0);
      std::cout << "[PrimaryGeneratorAction] Initial position is: r = " << initPosition.r()/cm 
		<< ", cosTheta = " << initPosition.cosTheta()
		<< ", phi = " << initPosition.phi() << std::endl;
      m_particleGun->SetParticlePosition(initPosition);           
    }
  else
    {
      m_particleGun->SetParticlePosition(m_initialPosition);
    }

  if(m_initialDirection.mag() < 1e-19){ // Randomised initial direction
    double cosTheta0dir = m_rndm->Uniform(-1,1);
    double phi0dir = m_rndm->Uniform(0,2.*acos(-1));
    std::cout << "[PrimaryGeneratorAction] cosTheta0dir = " << cosTheta0dir
	      << ", phi0dir = " << phi0dir << std::endl;
    
    double dx0 = sqrt(1-cosTheta0dir*cosTheta0dir)*cos(phi0dir);
    double dy0 = cosTheta0dir;		    
    double dz0 = sqrt(1-cosTheta0dir*cosTheta0dir)*sin(phi0dir);
    G4ParticleMomentum initDirection(dx0,dy0,dz0);
    // std::cout << "[PrimaryGeneratorAction] Initial Direction is: dx = " << dx0 
    //           << " cm,\t dy = " << dy0 << " cm,\t dz = " << dz0 << " cm, \t mag = " 
    //	       << sqrt(dx0*dx0+dy0*dy0+dz0*dz0) << std::endl;
    m_particleGun->SetParticleMomentumDirection(initDirection);
  }
  else{
    m_particleGun->SetParticleMomentumDirection(m_initialDirection);
  }

  m_particleGun->SetParticleEnergy(m_initialEnergy);    
  m_particleGun->GeneratePrimaryVertex(anEvent);  //create vertex
}



void PrimaryGeneratorAction::SetEnergyBeam(G4double val)
{
  m_initialEnergy = val;
  G4RunManager::GetRunManager()->ReinitializeGeometry();
}


void PrimaryGeneratorAction::SetInitialPositionCartesian(G4ThreeVector position)
{
  m_initialPosition = position;
}



void PrimaryGeneratorAction::SetInitialPositionSpherical(G4ThreeVector position, G4double unit)
{ // Unit conversion on y and z to get input value from degrees into radians <-- need to change this into my system of units
  G4ThreeVector positionPreSwap;
  positionPreSwap.setRThetaPhi(position.x(), std::acos(position.y()/unit), position.z()/unit*M_PI/180);
  
  m_initialPosition.setX(positionPreSwap.x());
  m_initialPosition.setY(positionPreSwap.z());
  m_initialPosition.setZ(positionPreSwap.y());
}



void PrimaryGeneratorAction::SetInitialDirectionCartesian(G4ThreeVector direction)
{
  m_initialDirection = direction.unit();
}



void PrimaryGeneratorAction::SetInitialDirectionSpherical(G4ThreeVector direction)
{ 
  G4ThreeVector directionPreSwap;
  directionPreSwap.setRThetaPhi(direction.x(), std::acos(direction.y()), direction.z()*M_PI/180);
  //std::cout<< " Direction 00 = "<< directionPreSwap << std::endl;
  m_initialDirection.setX(directionPreSwap.x());
  m_initialDirection.setY(directionPreSwap.y());
  m_initialDirection.setZ(directionPreSwap.z());
  m_initialDirection.unit();
}

void PrimaryGeneratorAction::SetInitialPositionDirectionMuons()
{
  // Random position in a plane the size of the world just above the detector - not finished yet
  m_initialPosition.setX(m_rndm->Uniform(-49.9, 49.9)*cm);
  G4double zpos = m_rndm->Uniform(-49.9, 49.9)*cm;
  G4double ypos = 34*cm;
}
