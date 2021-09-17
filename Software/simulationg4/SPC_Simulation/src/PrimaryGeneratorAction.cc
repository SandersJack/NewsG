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

#include "G4Event.hh"
#include "G4GenericIon.hh"
#include "G4IonTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4RunManager.hh"
#include "G4SystemOfUnits.hh"
#include "Randomize.hh"

#include "PrimaryGeneratorMessenger.hh"

#include "TF1.h"
#include "TFile.h"
#include "TH1D.h"
#include "TVector3.h"


PrimaryGeneratorAction::PrimaryGeneratorAction()
    : G4VUserPrimaryGeneratorAction(),
      m_initialParticle("proton"),
      m_initialEnergy(10 * keV),
      m_minRadius(0.15 * cm),
      m_maxRadius(29.999 * cm),
      m_nInitialParticles(1),
      m_initialPosition(0, 0, 0),
      m_initialDirection(0, 0, 0),
      m_randomPosition(false),
      m_randomDirection(false),
      m_muonPosDir(false),
      m_radialDir(false),
      m_recoilSpectrum(false),
      m_incidentParticleMass(1. * GeV){
  m_primaryGeneratorMessenger = new PrimaryGeneratorMessenger(this);
  m_particleGun = new G4ParticleGun(m_nInitialParticles);
}

PrimaryGeneratorAction::~PrimaryGeneratorAction() {
  delete m_primaryGeneratorMessenger;
  delete m_particleGun;
}

void PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent) {
  if (m_initialPosition.mag() <
      1e-19)  // Flag for randomised position each event
  {
    m_randomPosition = true;
  }

  if (m_initialDirection.mag() <
      1e-19)  // Flag for randomised direction each event
  {
    m_randomDirection = true;
  }

  if (m_initialEnergy < 1e-19) m_random_energy = true;

  // Particle options: GenericIon, proton, neutron, e-, alpha, gamma
  if (m_initialParticle == "He4+") {
    // helium ion - can't define in constructor as ion table is not yet ready
    G4int Z = 2, A = 4;
    G4double ionCharge = 1. * eplus;
    G4double excitEnergy = 54.4 * eV;  // Second Ionisation energy
    G4ParticleDefinition* ion =
        G4IonTable::GetIonTable()->GetIon(Z, A, excitEnergy);
    m_particleGun->SetParticleDefinition(ion);
    m_particleGun->SetParticleCharge(ionCharge);
  } else if (m_initialParticle == "Ar37") {
    G4int Z = 18, A = 37;
    G4double ionCharge   = 0.*eplus;
    G4double excitEnergy = 0.*keV;

    G4ParticleDefinition* ion
      = G4IonTable::GetIonTable()->GetIon(Z,A,excitEnergy);
    m_particleGun->SetParticleDefinition(ion);
    m_particleGun->SetParticleCharge(ionCharge);
  } else if (m_initialParticle == "Pb210") {
    G4int Z = 82, A = 210;
    G4double ionCharge   = 0.*eplus;
    G4double excitEnergy = 0.*keV;

    G4ParticleDefinition* ion
      = G4IonTable::GetIonTable()->GetIon(Z,A,excitEnergy);
    m_particleGun->SetParticleDefinition(ion);
    m_particleGun->SetParticleCharge(ionCharge);
  } else {
    G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
    G4ParticleDefinition* particle =
        particleTable->FindParticle(m_initialParticle);
    m_particleGun->SetParticleDefinition(particle);
  }

  if (m_recoilSpectrum == true) {
    double minRecoilEnergy = 1.E-3;  // keV
    double maxRecoilEnergy = 10.;    // keV
    G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
    G4ParticleDefinition* particle =
        particleTable->FindParticle(m_initialParticle);
      double recoilParticleMass = particle->GetPDGMass() / GeV;
      //TF1* fRecoilSpectrum = new TF1("fRecoilSpectrum", PrimaryGeneratorAction::CalculatedRdEROverR0, minRecoilEnergy, maxRecoilEnergy, 2);
      //fRecoilSpectrum->SetParameters(m_incidentParticleMass/GeV, recoilParticleMass);
      //fRecoilSpectrum->SetNpx(10000);
      //      double tempEnergy = fRecoilSpectrum->GetRandom();


      //Instead of TF1 use rejection sampling to get energy
      bool energyAccepted = false;
      double maximumdRdEr = PrimaryGeneratorAction::CalculatedRdEROverR0(minRecoilEnergy, m_incidentParticleMass/GeV, recoilParticleMass);
      double tempEnergy=0.;
      //loop until an energy value is drawn from distribution
      while(energyAccepted==false)
	{
	  //generate a temp energy between
	  tempEnergy = G4RandFlat::shoot(minRecoilEnergy, maxRecoilEnergy);
	  //generate an acceptance for the value
	  double tempAcceptance = G4RandFlat::shoot(0., maximumdRdEr);
	  //check if acceptance is below evauated value; if so accept the energy
	  if(tempAcceptance<PrimaryGeneratorAction::CalculatedRdEROverR0(tempEnergy, m_incidentParticleMass/GeV, recoilParticleMass))
	     energyAccepted=true;
	}

      std::cout<<"tempEnergy"<<tempEnergy<<"   "<<m_incidentParticleMass/GeV<<"  "
	       <<recoilParticleMass<<"\n";
      SetInitialEnergy(tempEnergy * keV);
    }

  if (m_muonPosDir == true) {
    // Random position in a plane the size of the world just above the detector
    G4double x = G4RandFlat::shoot(-99.9, 99.9) * cm;
    G4double z = G4RandFlat::shoot(-99.9, 99.9) * cm;
    m_initialPosition.setX(x);
    m_initialPosition.setZ(z);
    m_initialPosition.setY(34 * cm);
    // Random direction with uniform phi dist. and cos^2(theta) theta
    // distribution - check whether this gives proper cos squared distribution
    double phiDir = G4RandFlat::shoot(-1. * M_PI, M_PI);
    TF1* func = new TF1("cosSq", "TMath::Cos(x)*TMath::Cos(x)", 0, M_PI / 2);
    double theta = func->GetRandom();
    double cosThetaDir = std::cos(theta);
    // Swap to our spherical coordinates
    G4ThreeVector directionPreSwap;
    directionPreSwap.setRThetaPhi(-1, std::acos(cosThetaDir), phiDir);
    m_initialDirection.setX(directionPreSwap.x());
    m_initialDirection.setY(directionPreSwap.z());
    m_initialDirection.setZ(directionPreSwap.y());
    m_initialDirection.unit();
    m_particleGun->SetParticleMomentumDirection(m_initialDirection);
  }

  if (m_randomPosition) {
    // Randomized position if initial position is at origin (default)
    double x0 = 0. * cm;
    double y0 = 0. * cm;
    double z0 = 0. * cm;
    do {
      double minCubed =
          (m_minRadius / cm) * (m_minRadius / cm) * (m_minRadius / cm);
      double maxCubed =
          (m_maxRadius / cm) * (m_maxRadius / cm) * (m_maxRadius / cm);

      double r0pos = std::cbrt(G4RandFlat::shoot(minCubed, maxCubed)) * cm;
      // double r0pos = m_rndm->Uniform(m_minRadius/cm,m_maxRadius/cm)*cm; //
      // Radius within detector <-- Uniform in radius
      double phi0pos = G4RandFlat::shoot(0.0, 2. * acos(-1));
      double cosTheta0pos = G4RandFlat::shoot(m_minCosTheta, m_maxCosTheta);
      x0 = r0pos * sqrt(1 - cosTheta0pos * cosTheta0pos) * cos(phi0pos);
      y0 = r0pos * sqrt(1 - cosTheta0pos * cosTheta0pos) * sin(phi0pos);
      z0 = r0pos * cosTheta0pos;
    } while (y0 < -0.15 &&
             sqrt(x0 * x0 + z0 * z0) <
                 0.3);  // Protection against initial position being in bar

    std::cout << "[PrimaryGeneratorAction] Initial Position is: x = " << x0 / cm
              << " cm,\t y = " << y0 / cm << " cm,\t z = " << z0 / cm << " cm"
              << std::endl;

    G4ThreeVector initPosition(x0, y0, z0);
    G4ThreeVector actualInitPosition(x0, z0, y0);
    std::cout << "[PrimaryGeneratorAction] Initial position is: r = "
              << initPosition.r() / cm
              << ", cosTheta = " << initPosition.cosTheta()
              << ", phi = " << initPosition.phi() << std::endl;
    m_particleGun->SetParticlePosition(actualInitPosition);
    m_initialPosition = actualInitPosition;
  } else
    m_particleGun->SetParticlePosition(m_initialPosition);

  // Radially inwards direction
  if (m_radialDir == true) {
    // Swap to our spherical coordinates
    G4ThreeVector positionPreSwap = G4ThreeVector(
        m_initialPosition.x(), m_initialPosition.z(), m_initialPosition.y());
    double cosThetaDir = positionPreSwap.cosTheta();
    double phiDir = positionPreSwap.phi();
    G4ThreeVector directionPreSwap;
    directionPreSwap.setRThetaPhi(-1, std::acos(cosThetaDir), phiDir);
    m_initialDirection.setX(directionPreSwap.x());
    m_initialDirection.setY(directionPreSwap.z());
    m_initialDirection.setZ(directionPreSwap.y());
    m_initialDirection.unit();
    m_particleGun->SetParticleMomentumDirection(m_initialDirection);
  }

  if (m_randomDirection && !m_radialDir) {  // Randomised initial direction
    double cosTheta0dir, phi0dir;
   // cosTheta0dir = G4RandFlat::shoot(-1.0, 1.0); // Comment out this if using thee dot product
   // phi0dir = G4RandFlat::shoot(0.0, 2. * acos(-1));
    double theta0pos = acos(m_initialPosition.cosTheta());
    double phi0pos = m_initialPosition.phi();
   // double cosTheta0dir, phi0dir;
if (true) {
    while(true) {
  	cosTheta0dir = G4RandFlat::shoot(-1.0, 1.0);
    	phi0dir = G4RandFlat::shoot(0.0, 2. * acos(-1));

    	double theta0dir = acos(cosTheta0dir);
    	//double dot = sin(theta0dir)*sin(theta0pos)*cos(phi0dir-phi0pos)+cos(theta0dir)*cos(theta0pos);
    	double dottheta = cos(theta0pos-theta0dir);
	double dotphi = cos(phi0pos-phi0dir);
	if( dottheta > 0 and dotphi > 0 ){
      	//if( dot > 0 ){
		break;
    	}else {
      		continue;
    }
    }
}
    std::cout << "[PrimaryGeneratorAction] cosTheta0dir = " << cosTheta0dir
              << ", phi0dir = " << phi0dir << std::endl;

    double dx0 = sqrt(1 - cosTheta0dir * cosTheta0dir) * cos(phi0dir);
    double dy0 = cosTheta0dir;
    double dz0 = sqrt(1 - cosTheta0dir * cosTheta0dir) * sin(phi0dir);
    G4ParticleMomentum initDirection(dx0, dy0, dz0);
    // std::cout << "[PrimaryGeneratorAction] Initial Direction is: dx = " <<
    // dx0
    //           << " cm,\t dy = " << dy0 << " cm,\t dz = " << dz0 << " cm, \t
    //           mag = "
    //	       << sqrt(dx0*dx0+dy0*dy0+dz0*dz0) << std::endl;
    m_particleGun->SetParticleMomentumDirection(initDirection);
  } else {
    m_particleGun->SetParticleMomentumDirection(m_initialDirection);
  }

  // if(m_initialParticle == "mu-")
  //   {
  //     TFile* muonFile = TFile::Open("./muonData/MuonDistribution.root");
  //     TH1D* muonDistribution = (TH1D*)muonFile->Get("h_muonDistribution");
  //     double muonEnergy = muonDistribution->GetRandom(); //Distribution is in
  //     GeV m_initialEnergy = muonEnergy*GeV; //Set initial energy taking into
  //     account that it is GeV std::cout << "Muon Energy is: " <<
  //     m_initialEnergy/GeV << " GeV" << std::endl;
  //    }
  if (!m_random_energy) {
    m_particleGun->SetParticleEnergy(m_initialEnergy);
  } else {
    double random_energy = G4RandFlat::shoot(m_minEnergy, m_maxEnergy);
    std::cout << "[PrimaryGeneratorAction] E = " << random_energy << std::endl;
    m_particleGun->SetParticleEnergy(random_energy);
  }
  m_particleGun->GeneratePrimaryVertex(anEvent);  // create vertex
}

void PrimaryGeneratorAction::SetEnergyBeam(G4double val) {
  m_initialEnergy = val;
  G4RunManager::GetRunManager()->ReinitializeGeometry();
}

void PrimaryGeneratorAction::SetMinEnergyBeam(G4double val) {
  m_minEnergy = val;
  G4RunManager::GetRunManager()->ReinitializeGeometry();
}

void PrimaryGeneratorAction::SetMaxEnergyBeam(G4double val) {
  m_maxEnergy = val;
  G4RunManager::GetRunManager()->ReinitializeGeometry();
}

void PrimaryGeneratorAction::SetInitialPositionCartesian(
    G4ThreeVector position) {
  m_initialPosition = position;
}

void PrimaryGeneratorAction::SetInitialPositionSpherical(
    G4ThreeVector position,
    G4double
        unit) {  // Unit conversion on y and z to get input value from degrees
  // into radians <-- need to change this into my system of units
  G4ThreeVector positionPreSwap;
  positionPreSwap.setRThetaPhi(position.x(), std::acos(position.y() / unit),
                               position.z() / unit * M_PI / 180);

  m_initialPosition.setX(positionPreSwap.x());
  m_initialPosition.setY(positionPreSwap.z());
  m_initialPosition.setZ(positionPreSwap.y());
}

void PrimaryGeneratorAction::SetInitialDirectionCartesian(
    G4ThreeVector direction) {
  m_initialDirection = direction.unit();
}

void PrimaryGeneratorAction::SetInitialDirectionSpherical(
    G4ThreeVector direction) {
  G4ThreeVector directionPreSwap;
  directionPreSwap.setRThetaPhi(direction.x(), std::acos(direction.y()),
                                direction.z() * M_PI / 180);
  // std::cout<< " Direction 00 = "<< directionPreSwap << std::endl;
  m_initialDirection.setX(directionPreSwap.x());
  m_initialDirection.setY(directionPreSwap.z());
  m_initialDirection.setZ(directionPreSwap.y());
  m_initialDirection.unit();
}


double  PrimaryGeneratorAction::CalculatedRdEROverR0(
  double ER, double mX, double mT){
  //double* x, double *par){

  //double ER = x[0];  //   keV
  ER*=1.E-6;  //          GeV
  //double mX = par[0];  // GeV/c2
  //double mT = par[1];  // GeV/c2

  double r = PrimaryGeneratorAction::CalculateMassFactor(mT, mX);
  double E0 = 0.5*mX*m_aveVelocity*m_aveVelocity; // GeV /c2 km2 /s2
  E0*=m_oneOverc2; //       GeV
  double vMin = m_aveVelocity*TMath::Sqrt(ER/(E0*r)); // km /s
  double dRdERVEaveVescOverR0=0;

  if(vMin<=(m_escVelocity-m_earthVelocity))
    {
      double term1 = PrimaryGeneratorAction::CalculatedRdERVEaveVescInfOverR0(ER , mX,  mT);// /keV, Lewin eqn 3.12/R0
      term1*=1E6 ;// /kg /day /GeV
      double term2 = TMath::Exp(-1.*m_vEscRatio*m_vEscRatio)/(E0*r);//  /GeV
      dRdERVEaveVescOverR0  = m_kRatio*(term1-term2);// /GeV
      dRdERVEaveVescOverR0*= 1E-6;//          /keV
    }

  //additional conditions from //eqn 19 from 0808.3607
  else if(vMin>(m_escVelocity-m_earthVelocity)&&vMin<(m_escVelocity+m_earthVelocity))
    {
      double term1 = (m_aveVelocity*TMath::Sqrt(TMath::Pi())/(m_earthVelocity*4.)) * (TMath::Erf(m_vEscRatio)-TMath::Erf((vMin-m_earthVelocity)/(m_aveVelocity)));
      double term2 = ((m_escVelocity+m_earthVelocity-vMin)/(2.*m_earthVelocity))*TMath::Exp(-1.*m_vEscRatio*m_vEscRatio);
      dRdERVEaveVescOverR0  = m_kRatio*(term1-term2)/(E0*r);//  /GeV
      dRdERVEaveVescOverR0*= 1E-6;//  /keV
    }
  else
    dRdERVEaveVescOverR0 = 0;

  if(dRdERVEaveVescOverR0<0.)
    {
    std::cout<<"dRdERVEaveVescOverR0 [PrimaryGeneratorAction::CalculatedRdEROverR0] has returned negative value! Returning 0 instead!\n";
    dRdERVEaveVescOverR0 = 0;
    }

  return dRdERVEaveVescOverR0;// /keV
}

double  PrimaryGeneratorAction::CalculatedRdERVEaveVescInfOverR0(
    double ER, double mX, double mT){

  double r = PrimaryGeneratorAction::CalculateMassFactor(mT, mX);
  double E0 = 0.5*mX*m_aveVelocity*m_aveVelocity; // GeV /c2 km2 /s2
  E0*=m_oneOverc2; //       GeV
  double vMin = m_aveVelocity*TMath::Sqrt(ER/(E0*r)); // km /s

  double coeff = TMath::Sqrt(TMath::Pi())*m_vEarthRatio/(E0*r*4);// /GeV
  double erfPlus = TMath::Erf((vMin+ m_earthVelocity)/(m_aveVelocity));
  double erfMinus = TMath::Erf((vMin- m_earthVelocity)/(m_aveVelocity));
  double dRdERVEaveVescInfOverR0 = coeff*(erfPlus-erfMinus);// /GeV
  dRdERVEaveVescInfOverR0*=1E-6;// /keV

  return dRdERVEaveVescInfOverR0;// /keV
}
