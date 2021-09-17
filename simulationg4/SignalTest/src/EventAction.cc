#//
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
// $Id$
//
/// \file EventAction.cc
/// \brief Implementation of the EventAction class
#include "EventAction.hh"
#include "EventMessenger.hh"
#include "RunAction.hh"

#include "G4RunManager.hh"
#include "G4Event.hh"

#include "G4SDManager.hh"
#include "G4HCofThisEvent.hh"
#include "G4THitsMap.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"
#include "G4VUserEventInformation.hh"
#include "G4TrajectoryContainer.hh"
#include "Trajectory.hh"
#include "Analysis.hh"

#include "MyHit.hh"

#include "ChargeCarrier.hh"


EventAction::EventAction(RunAction* runAction)
 : G4UserEventAction(), 
   m_ionMobDir("BasicMobility"),
   m_gasType("sedine2018"),
   m_sensorDir("UmbrellaSensor"),
   m_doSignal(1),
   m_doPulse(1),
   m_signalBinSize(50.*ns),
   m_nSignalBins(50000),
   aCube(30.), // cm 
   signalt0(0.*ns), // ns
   m_debug(1),
   fRunAction(runAction),
   fCollID_converter(-1),
  fCollID_detector(-1)
   // fCollID_actdet(-1)
{
  m_eventMessenger = new EventMessenger(this);

  /**
  pulseProcess = new Electronics();
  pulseProcess->SetTimeConstant(140.);
  pulseProcess->SetSamplingTime(0.48);
  pulseProcess->SetfCtomV(-1.);  
  std::cout<< "Setting up Event Action "<< m_gasType<<std::endl;
  gas = new GasMixture();
  gas->SetIonMobilityDir(m_ionMobDir);
  gas->SetGas(m_gasType);
  
  fieldMap = new FieldMap();
  fieldMap->SetGas(gas->GetGas());
  fieldMap->SetSensorDir(m_sensorDir);
  fieldMap->Initialise();

  
  sensor = new Garfield::Sensor();
  sensor->AddComponent(fieldMap->GetFieldMap());
  sensor->AddElectrode(fieldMap->GetFieldMap(), "readout");
  sensor->SetArea(-aCube,-aCube,-aCube, aCube, aCube, aCube);
  sensor->SetTimeWindow(signalt0/ns, m_signalBinSize/ns, m_nSignalBins);
	   
  ionDrift = new IonDrift();
  ionDrift->SetSensor(sensor);
  ionDrift->SetDriftType(DriftType::RKF);
  ionDrift->SetDebug(m_debug);
       
  electronDrift = new ElectronDrift();
  electronDrift->SetSensor(sensor);
  electronDrift->SetDriftType(ElectronDriftType::RKF);
  electronDrift->SetDebug(m_debug);
  **/
  // converter_energy= &runAction->converter_energy;
  // detector_energy= &runAction->detector_energy;
  // detector_position_cog= &runAction->detector_position_cog;
  // detector_position_max= &runAction->detector_position_max;

  // photon_energy_converter= &runAction->photon_energy_converter;
  // photon_energy_detector = &runAction->photon_energy_detector;
  // photon_energy_phantom  = &runAction->photon_energy_phantom;
  // photon_xpos_converter = &runAction->photon_xpos_converter;
  // photon_ypos_converter = &runAction->photon_ypos_converter ;
  // photon_zpos_converter = &runAction->photon_zpos_converter;
  // photon_xdir_converter = &runAction->photon_xdir_converter;
  // photon_ydir_converter = &runAction->photon_ydir_converter;
  // photon_zdir_converter = &runAction->photon_zdir_converter;
  // xpos_stop = &runAction->xpos_stop;
  // ypos_stop = &runAction->ypos_stop;
  // zpos_stop = &runAction->zpos_stop;
  // ke_stop   = &runAction->ke_stop;
  // creatorprocess = &runAction->creatorprocess;
  // xpos_production = &runAction->xpos_production;
  // ypos_production = &runAction->ypos_production;
  // zpos_production = &runAction->zpos_production;
  // neutronEnergy   = &runAction->neutronEnergy;
  // neutronProcess  = &runAction->neutronProcess;
  // neut_xpos = &runAction->neut_xpos;
  // neut_ypos = &runAction->neut_ypos;
  // neut_zpos = &runAction->neut_zpos;
  // photon_xdir_production = &runAction->photon_xdir_production;
  // photon_ydir_production = &runAction->photon_ydir_production;
  // photon_zdir_production = &runAction->photon_zdir_production;
  // neutron_xdir_production = &runAction->neutron_xdir_production;
  // neutron_ydir_production = &runAction->neutron_ydir_production;
  // neutron_zdir_production = &runAction->neutron_zdir_production;
  // neutron_energy_converter = &runAction->neutron_energy_converter;
  // neutron_xpos_converter = &runAction->neutron_xpos_converter;
  // neutron_ypos_converter = &runAction->neutron_ypos_converter;
  // neutron_zpos_converter = &runAction->neutron_zpos_converter;
  // neutron_xdir_converter = &runAction->neutron_xdir_converter;
  // neutron_ydir_converter = &runAction->neutron_ydir_converter;
  // neutron_zdir_converter = &runAction->neutron_zdir_converter;
  // electron_energy_production = &runAction->electron_energy_production;
  // electron_xpos_production = &runAction->electron_xpos_production;
  // electron_ypos_production = &runAction->electron_ypos_production;
  // electron_zpos_production = &runAction->electron_zpos_production;
  // electron_xdir_production = &runAction->electron_xdir_production;
  // electron_ydir_production = &runAction->electron_ydir_production;
  // electron_zdir_production = &runAction->electron_zdir_production;
  // electron_creatorprocess = &runAction->electron_creatorprocess;
  // positron_energy_production = &runAction->positron_energy_production;
  // positron_xpos_production = &runAction->positron_xpos_production;
  // positron_ypos_production = &runAction->positron_ypos_production;
  // positron_zpos_production = &runAction->positron_zpos_production;
  // positron_xdir_production = &runAction->positron_xdir_production;
  // positron_ydir_production = &runAction->positron_ydir_production;
  // positron_zdir_production = &runAction->positron_zdir_production;
  // positron_creatorprocess = &runAction->positron_creatorprocess;
  // photon_energy_productionconverter = &runAction->photon_energy_productionconverter;
  // photon_xpos_productionconverter = &runAction->photon_xpos_productionconverter;
  // photon_ypos_productionconverter = &runAction->photon_ypos_productionconverter;
  // photon_zpos_productionconverter = &runAction->photon_zpos_productionconverter;
  // photon_xdir_productionconverter = &runAction->photon_xdir_productionconverter;
  // photon_ydir_productionconverter = &runAction->photon_ydir_productionconverter;
  // photon_zdir_productionconverter = &runAction->photon_zdir_productionconverter;
  // photon_creatorprocess_converter = &runAction->photon_creatorprocess_converter;
  // photon_energy_productionstrips = &runAction->photon_energy_productionstrips;
  // photon_xpos_productionstrips = &runAction->photon_xpos_productionstrips;
  // photon_ypos_productionstrips = &runAction->photon_ypos_productionstrips;
  // photon_zpos_productionstrips = &runAction->photon_zpos_productionstrips;
  // photon_xdir_productionstrips = &runAction->photon_xdir_productionstrips;
  // photon_ydir_productionstrips = &runAction->photon_ydir_productionstrips;
  // photon_zdir_productionstrips = &runAction->photon_zdir_productionstrips;
  // photon_creatorprocess_strips = &runAction->photon_creatorprocess_strips;
  // particle_energy_production = &runAction->particle_energy_production;
  // particle_xpos_production = &runAction->particle_xpos_production;
  // particle_ypos_production = &runAction->particle_ypos_production;
  // particle_zpos_production = &runAction->particle_zpos_production;
  // particle_xdir_production = &runAction->particle_xdir_production;
  // particle_ydir_production = &runAction->particle_ydir_production;
  // particle_zdir_production = &runAction->particle_zdir_production;
  // particle_creatorprocess = &runAction->particle_creatorprocess;
  // particle_name = &runAction->particle_name;
  
  // Primary Vertex information
  initialParticleTypeNt        = &runAction->initialParticleTypeNt;
  initialParticleEnergyNt      = &runAction->initialParticleEnergyNt;
  initialParticleRadiusNt      = &runAction->initialParticleRadiusNt;
  initialParticleCosThetaNt    = &runAction->initialParticleCosThetaNt;
  initialParticlePhiNt         = &runAction->initialParticlePhiNt;
  initialParticleTimeNt        = &runAction->initialParticleTimeNt;
  initialParticleDirRadNt      = &runAction->initialParticleDirRadNt;
  initialParticleDirCosThetaNt = &runAction->initialParticleDirCosThetaNt;
  initialParticleDirPhiNt      = &runAction->initialParticleDirPhiNt;
  initialParticleDirXNt        = &runAction->initialParticleDirXNt;
  initialParticleDirYNt        = &runAction->initialParticleDirYNt;
  initialParticleDirZNt        = &runAction->initialParticleDirZNt;
  
  // Garfield++ values
  initElecRadiusNt   = &runAction->initElecRadiusNt;
  initElecPhiNt      = &runAction->initElecPhiNt;
  initElecCosThetaNt = &runAction->initElecCosThetaNt;
  initElecTimeNt    = &runAction->initElecTimeNt;
  initIonRadiusNt   = &runAction->initIonRadiusNt;
  initIonPhiNt      = &runAction->initIonPhiNt;
  initIonCosThetaNt = &runAction->initIonCosThetaNt;
  initIonTimeNt     = &runAction->initIonTimeNt;
  finElecRadiusNt   = &runAction->finElecRadiusNt;
  finElecPhiNt      = &runAction->finElecPhiNt;
  finElecCosThetaNt = &runAction->finElecCosThetaNt;
  finElecTimeNt     = &runAction->finElecTimeNt;
  finIonRadiusNt   = &runAction->finIonRadiusNt;
  finIonPhiNt      = &runAction->finIonPhiNt;
  finIonCosThetaNt = &runAction->finIonCosThetaNt;
  finIonTimeNt     = &runAction->finIonTimeNt;
  ionChargeNt      = &runAction->ionChargeNt;
  avalancheSizeNt  = &runAction->avalancheSizeNt;   
  signalNt    = &runAction->signalNt;
  signaltNt   = &runAction->signaltNt;
  pulseNt     = &runAction->pulseNt;
  pulsetNt    = &runAction->pulsetNt;
  elecDriftTimeNt = &runAction->elecDriftTimeNt;
  ionDriftTimeNt  = &runAction->ionDriftTimeNt;
  nInitElecNt     = &runAction->nInitElecNt;
  averageGainNt   = &runAction->averageGainNt;      
  integrateTownsendNt = &runAction->integrateTownsendNt;

  // Primary interaction tracking
  primaryProcess = &runAction->primaryProcess;
  primaryDeltaEnergy = &runAction->primaryDeltaEnergy;
  primaryRadius = &runAction->primaryRadius;
  primaryCosTheta = &runAction->primaryCosTheta;
  primaryPhi = &runAction->primaryPhi;
}



EventAction::~EventAction()
{
  /**
  delete fieldMap;
  //delete gas; //<--- belongs to fieldMap
  delete pulseProcess;
  delete sensor;
  delete ionDrift;
  delete electronDrift;
  **/
  delete m_eventMessenger;
}



void EventAction::BeginOfEventAction(const G4Event* evt)
{ 
  // converter_energy->clear();
  // detector_energy->clear();
  // detector_position_cog->clear();
  // detector_position_max->clear();

  // photon_energy_converter->clear();
  // photon_energy_detector->clear();
  // photon_energy_phantom->clear();
  // photon_xpos_converter->clear();
  // photon_ypos_converter->clear();
  // photon_zpos_converter->clear();
  // photon_xdir_converter->clear();
  // photon_ydir_converter->clear();
  // photon_zdir_converter->clear();
  // xpos_stop->clear();
  // ypos_stop->clear();
  // zpos_stop->clear();
  // ke_stop->clear();
  // creatorprocess->clear();
  // xpos_production->clear();
  // ypos_production->clear();
  // zpos_production->clear();
  // neutronEnergy->clear();
  // neutronProcess->clear();
  // neut_xpos->clear();
  // neut_ypos->clear();
  // neut_zpos->clear();
  // photon_xdir_production->clear();
  // photon_ydir_production->clear();
  // photon_zdir_production->clear();
  // neutron_energy_converter->clear();
  // neutron_xpos_converter->clear();
  // neutron_ypos_converter->clear();
  // neutron_zpos_converter->clear();
  // neutron_xdir_converter->clear();
  // neutron_ydir_converter->clear();
  // neutron_zdir_converter->clear();
  // electron_energy_production->clear();
  // electron_xpos_production->clear() ;
  // electron_ypos_production->clear();
  // electron_zpos_production->clear();
  // electron_xdir_production->clear();
  // electron_ydir_production->clear();
  // electron_zdir_production->clear();
  // electron_creatorprocess->clear();
  // positron_energy_production->clear();
  // positron_xpos_production->clear() ;
  // positron_ypos_production->clear();
  // positron_zpos_production->clear();
  // positron_xdir_production->clear();
  // positron_ydir_production->clear();
  // positron_zdir_production->clear();
  // positron_creatorprocess->clear();
  // photon_energy_productionconverter->clear();
  // photon_xpos_productionconverter->clear();
  // photon_ypos_productionconverter->clear();
  // photon_zpos_productionconverter->clear();
  // photon_xdir_productionconverter->clear();
  // photon_ydir_productionconverter->clear();
  // photon_zdir_productionconverter->clear();
  // photon_creatorprocess_converter->clear();
  // photon_energy_productionstrips->clear();
  // photon_xpos_productionstrips->clear();
  // photon_ypos_productionstrips->clear();
  // photon_zpos_productionstrips->clear();
  // photon_xdir_productionstrips->clear();
  // photon_ydir_productionstrips->clear();
  // photon_zdir_productionstrips->clear();
  // photon_creatorprocess_strips->clear();
  // particle_energy_production->clear();
  // particle_xpos_production->clear();
  // particle_ypos_production->clear();
  // particle_zpos_production->clear();
  // particle_xdir_production->clear();
  // particle_ydir_production->clear();
  // particle_zdir_production->clear();
  // particle_creatorprocess->clear();
  // particle_name->clear();

  // Primary vertex information
  initialParticleTypeNt->clear();
  initialParticleEnergyNt->clear();
  initialParticleRadiusNt->clear();
  initialParticleCosThetaNt->clear();
  initialParticlePhiNt->clear();
  initialParticleTimeNt->clear();
  initialParticleDirRadNt->clear();
  initialParticleDirCosThetaNt->clear();
  initialParticlePhiNt->clear();
  initialParticleDirXNt->clear();
  initialParticleDirYNt->clear();
  initialParticleDirZNt->clear();
  
  // Garfield++ values
  initElecRadiusNt->clear();
  initElecPhiNt->clear();
  initElecCosThetaNt->clear();
  initElecTimeNt->clear();
  initIonRadiusNt->clear();
  initIonPhiNt->clear();
  initIonCosThetaNt->clear();
  initIonTimeNt->clear();
  finElecRadiusNt->clear();
  finElecPhiNt->clear();
  finElecCosThetaNt->clear();
  finElecTimeNt->clear();
  finIonRadiusNt->clear();
  finIonPhiNt->clear();
  finIonCosThetaNt->clear();
  finIonTimeNt->clear();
  ionChargeNt->clear();
  avalancheSizeNt->clear();       
  signalNt->clear();
  signaltNt->clear();
  pulseNt->clear();
  pulsetNt->clear();
  elecDriftTimeNt->clear();
  ionDriftTimeNt->clear();
  nInitElecNt->clear();
  averageGainNt->clear();      
  integrateTownsendNt->clear();

  // Primary interaction tracking
  primaryProcess->clear();
  primaryDeltaEnergy->clear();
  primaryRadius->clear();
  primaryCosTheta->clear();
  primaryPhi->clear();

  G4int evtNb = evt->GetEventID();
  std::cout << "================= EVENT " << evtNb+1 << " =================" << std::endl;
  bIsPhoton =false;
  //G4int evtNb2 = evt->GetEventID();
  //bIsProton =false;
  // G4int evtNb3 = evt->GetEventID();
  bIsElectron =false;
  // G4cout<< " NEW EVENT " <<G4endl;
  /**
  if (evtNb == 0)
    {
      G4SDManager* SDMan = G4SDManager::GetSDMpointer();  
      fCollID_converter = SDMan->GetCollectionID("converter/edep");
      fCollID_detector  = SDMan->GetCollectionID("detector/edep");
      //fCollID_actdet = SDMan->GetCollectionID("actdet_photon/edep");
      //fCollID_actdet = SDMan->GetCollectionID("actdet_electron/edep");
    }
  **/

}



void EventAction::EndOfEventAction(const G4Event* evt )
{
  //PrimaryVertex information
  G4ThreeVector initPos = evt->GetPrimaryVertex()->GetPosition();
  std::cout << "[EventAction] Initial position: r = " << initPos.r()/cm 
	    << " cm, cosTheta = " << initPos.cosTheta()
	    << ", phi = " << initPos.phi() << std::endl;

  std::cout << "[EventAction] Initial position: x = " << initPos.x()/cm 
	    << " cm, y = " << initPos.y()/cm
	    << " cm, z = " << initPos.z()/cm << " cm" << std::endl;
  
  // Swap to our spherical co-ordinates
  G4ThreeVector initPosSwapped{initPos.x(), initPos.z(), initPos.y()};

  // Need to swap y and z so that the G4ThreeVector functions give the correct values (z is usually the phi axis, not y as in our case because of the bar)
  initialParticleRadiusNt->push_back(initPosSwapped.r()/cm);
  initialParticleCosThetaNt->push_back(initPosSwapped.cosTheta());
  initialParticlePhiNt->push_back(initPosSwapped.phi());

  G4ThreeVector initDir = evt->GetPrimaryVertex()->GetPrimary()->GetMomentumDirection();

  initialParticleDirRadNt->push_back(initDir.r());
  initialParticleDirCosThetaNt->push_back(initDir.cosTheta());
  initialParticleDirPhiNt->push_back(initDir.phi());
  initialParticleDirXNt->push_back(initDir.x());
  initialParticleDirYNt->push_back(initDir.y());
  initialParticleDirZNt->push_back(initDir.z());

  G4double initTime = evt->GetPrimaryVertex()->GetT0();
  std::cout << "[EventAction] Initial time is: " << initTime/ns << std::endl;
  
  initialParticleTimeNt->push_back(initTime/ns);

  G4String initParticle = evt->GetPrimaryVertex()->GetPrimary()->GetParticleDefinition()->GetParticleName();
  std::cout << "[EventAction] Name of initial particle is: " << initParticle << std::endl;
  
  if (initParticle == "e-")
    {initialParticleTypeNt->push_back(1);}
  else if (initParticle == "proton")
    {initialParticleTypeNt->push_back(2);}
  else if (initParticle == "neutron")
    {initialParticleTypeNt->push_back(3);}
  else if (initParticle == "gamma")
    {initialParticleTypeNt->push_back(4);}
  else if (initParticle == "alpha")
    {initialParticleTypeNt->push_back(5);}
  else if (initParticle == "GenericIon") // Need to flesh this out
    {initialParticleTypeNt->push_back(6);}
  else if (initParticle == "mu-")
    {initialParticleTypeNt->push_back(7);}
  else
    {initialParticleTypeNt->push_back(-1);} // Unsupported particle
    
  
  G4double initEnergy = evt->GetPrimaryVertex()->GetPrimary()->GetKineticEnergy();
  std::cout << "[EventAction] Initial energy is: " << initEnergy/keV << " keV" << std::endl;

  initialParticleEnergyNt->push_back(initEnergy/keV);

  G4ThreeVector initDirection = evt->GetPrimaryVertex()->GetPrimary()->GetMomentumDirection();
  // std::cout << "[EventAction] Initial direction spherical: r = " << initDirection.r() 
  // 	    << ", theta = " << initDirection.cosTheta()*180/acos(-1)
  // 	    << "deg, phi = " << initDirection.phi()*180/acos(-1) << " deg" << std::endl;

  std::cout << "[EventAction] Initial direction cartesian: x = " << initDirection.x() 
  	    << ", y = " << initDirection.y()
  	    << ", z = " << initDirection.z() << std::endl;

  // std::cout << "[EventAction] Total energy deposited is: " << evt->GetPrimaryVertex()->GetPrimary()->GetTotalEnergyDeposit()/keV << "keV" << std::endl;
   

  //Hits collections
  G4HCofThisEvent* HCE = evt->GetHCofThisEvent();
  if(!HCE) return;
               
  // Get hits collections IDs
  G4SDManager* SDMan = G4SDManager::GetSDMpointer(); 
  // if (fCollID_converter < 0) 
  //   fCollID_converter   = SDMan->GetCollectionID("converter/edep");


  // G4double energyConverter=0;
  // G4double energyAbsorber=0;
  // G4double edepTot=0;
  // G4double position_cog = 0;
  // G4double position_max = 0;
  // G4double energy_max = 0;
  // std::vector<double> *energy_strips =new std::vector<double>();


  // //Energy in crystals : identify 'good events'
  // const G4double eThreshold = 0*keV;
  // G4int nbOfFired = 0;
  // G4int nbOfFired2 = 0;

  fCollID_detector   = SDMan->GetCollectionID("gasDetector/MyHitCollection");
  MyHitsCollection* HitsColl = 0;
  if(HCE){
    HitsColl = (MyHitsCollection*)(HCE->GetHC(fCollID_detector)); 
    std::cout << "[EventAction] Retrieved hit collection!" << std::endl;
  }
  if(HitsColl) 
     {
       int nHit = HitsColl->entries();
       G4cout<<"My detector has "<<nHit<<" hits."<<G4endl;

       int nGarfieldHits = 0;
       for (int i = 0; i < nHit; ++i)
	 {
	   MyHit* aHit = (*HitsColl)[i];
	   G4String label = aHit->GetLabel();
	   if(label == "GarfieldHit")  
	     {
	       ++nGarfieldHits;
	     }
	 }
       
       if (nGarfieldHits > 0)
       {
	 for(int i=0; i<nHit; i++)
	   {
	     MyHit* aHit = (*HitsColl)[i];
	     G4ThreeVector elecPos = aHit->GetElecPos();
	     G4double elecTime = aHit->GetElecTime();
	     initElecRadiusNt->push_back(elecPos.r());
	     initElecCosThetaNt->push_back(elecPos.cosTheta());
	     initElecPhiNt->push_back(elecPos.phi());
	     initElecTimeNt->push_back(elecTime);
	     // Get W and Fano from first hit
	     if(aHit->GetW()>1e-19)
	       {
		 fRunAction->SetWFano(aHit->GetW(), aHit->GetFano());
	       }
	   }
	 
	   Electronics* pulseProcess = new Electronics();
	   pulseProcess->SetTimeConstant(140.);
	   pulseProcess->SetSamplingTime(0.96);
	   pulseProcess->SetfCtomV(-1.);  
	   
	   GasMixture* gas = new GasMixture();
	   gas->SetIonMobilityDir(m_ionMobDir);
	   gas->SetGas(m_gasType, 0, 0, m_pressure);
	   
	   FieldMap* fieldMap = new FieldMap();
	   fieldMap->SetGas(gas->GetGas());
	   fieldMap->SetSensorDir(m_sensorDir);
	   fieldMap->Initialise();
	   
	   double aCube = 30.; // cm 
	   double signalt0 = 0.*ns; // ns
	   
	   signalNt->resize(m_nSignalBins, 0);
	   signaltNt->resize(m_nSignalBins, 0);

	   Garfield::Sensor* sensor = new Garfield::Sensor();
	   sensor->AddComponent(fieldMap->GetFieldMap());
	   sensor->AddElectrode(fieldMap->GetFieldMap(), "readout");
	   sensor->SetArea(-aCube,-aCube,-aCube, aCube, aCube, aCube);
	   sensor->SetTimeWindow(signalt0/ns, m_signalBinSize/ns, m_nSignalBins);
	   IonDrift* ionDrift = new IonDrift();
	   ionDrift->SetSensor(sensor);
	   ionDrift->SetDriftType(DriftType::RKF);
	   ionDrift->SetDebug(m_debug);
	   ElectronDrift* electronDrift = new ElectronDrift();
	   electronDrift->SetSensor(sensor);
	   electronDrift->SetDriftType(ElectronDriftType::RKF);
	   electronDrift->SetDebug(m_debug);

	   std::vector<ChargeCarrier>* driftIonPositions = new std::vector<ChargeCarrier>;
	   std::vector<ChargeCarrier>* driftElectronPositions = new std::vector<ChargeCarrier>;

	   int avalancheSize = 0;
	   for(int i = 0; i<nHit; ++i) 
	     {
	       MyHit* aHit = (*HitsColl)[i];
	       double x = aHit->GetPos().x();
	       double y = aHit->GetPos().y();
	       double z = aHit->GetPos().z();
	       double t = aHit->GetTime();
	       double charge = aHit->GetCharge();
	       G4String label = aHit->GetLabel();
	       //std::cout << "[EventAction] Hit label is: " << label << std::endl;

	       // Do not need to worry about swapping y and z co-ordinates here as all of the spherical co-ordinate functions use our custom "ChargeCarrier" class, which already takes this into account
	       if(label == "GarfieldHit"){
		 double r_cm = sqrt((x/cm)*(x/cm) + (y/cm)*(y/cm) + (z/cm)*(z/cm));
		 if(r_cm > 25){
		   std::cerr << "[EventAction] Initial radius is greater than 25 cm, skipping hit!" << std::endl;
		   continue;
		 }
		 
		 avalancheSize += charge;
		 //std::cout << "[EventAction] x = " << x/cm << "cm, y = " << y/cm << "cm, z = " << z/cm << "cm, t = " << t/ns << " ns, charge scale = " << charge << std::endl; 
		 driftIonPositions->emplace_back();
		 driftIonPositions->at(driftIonPositions->size()-1).SetPositionCartesian(x/cm, y/cm, z/cm, t/ns);
		 driftIonPositions->at(driftIonPositions->size()-1).SetCharge(charge);
	     
		 driftElectronPositions->emplace_back();
		 driftElectronPositions->at(driftElectronPositions->size()-1).SetPositionCartesian(x/cm, y/cm, z/cm, t/ns);
		 driftElectronPositions->at(driftElectronPositions->size()-1).SetCharge(charge);
	     
		 double r = driftIonPositions->at(driftIonPositions->size()-1).r();
		 double phi = driftIonPositions->at(driftIonPositions->size()-1).phi();
		 double cosTheta = driftIonPositions->at(driftIonPositions->size()-1).cosTheta();
	     
		 initIonRadiusNt->push_back(r);
		 initIonPhiNt->push_back(phi);
		 initIonCosThetaNt->push_back(cosTheta);
		 initIonTimeNt->push_back(t);
		 ionChargeNt->push_back(charge);
	       }
	       //Putting avalancheSize here shows you the size of each individual garfield hit's avalanche
	     }
	   avalancheSizeNt->push_back(avalancheSize);
	 
	   std::cout <<"[EventAction] Will drift Ions now!" << std::endl;
	   ionDrift->DriftIons(driftIonPositions);
	   std::cout <<"[EventAction] Will drift Electrons now!" << std::endl;
	   electronDrift->DriftElectrons(driftElectronPositions);
	 
	   for (unsigned int iIon = 0; iIon<driftIonPositions->size(); ++iIon)
	     {
	       finIonRadiusNt->  push_back(driftIonPositions->at(iIon).r());
	       finIonCosThetaNt->push_back(driftIonPositions->at(iIon).cosTheta());
	       finIonPhiNt->     push_back(driftIonPositions->at(iIon).phi());
	       finIonTimeNt->    push_back(driftIonPositions->at(iIon).t());
	     }
	 
	   for (unsigned int iElec = 0; iElec<driftElectronPositions->size(); ++iElec)
	     {
	       finElecRadiusNt->  push_back(driftElectronPositions->at(iElec).r());
	       finElecCosThetaNt->push_back(driftElectronPositions->at(iElec).cosTheta());
	       finElecPhiNt->     push_back(driftElectronPositions->at(iElec).phi());
	       finElecTimeNt->    push_back(driftElectronPositions->at(iElec).t());
	     }

	   for (unsigned int iElec = 0; iElec<finElecTimeNt->size(); ++iElec)
	     {
	       G4double driftTime = finElecTimeNt->at(iElec) - initElecTimeNt->at(iElec);
	       elecDriftTimeNt->push_back(driftTime);
	     }
	 
	   if(m_doSignal){
	     for(int iBin=0; iBin<m_nSignalBins; ++iBin)
	       {
		 signalNt->at(iBin)+=sensor->GetIonSignal("readout",iBin);
		 signalNt->at(iBin)+=sensor->GetElectronSignal("readout",iBin);
		 signaltNt->at(iBin)=signalt0+iBin*m_signalBinSize/ns;
	       }       
	     sensor->ClearSignal();
	   }
	   if(m_doPulse)
	     {pulseProcess->ProcessPulse(*signalNt, *signaltNt, *pulseNt, *pulsetNt);}
	     

	   delete driftElectronPositions;
	   delete driftIonPositions;

	   delete electronDrift;
	   delete ionDrift;
	   delete sensor;
	   delete fieldMap;
	   //delete gas; //<-- belongs to fieldMap
	   delete pulseProcess;
	   }
       else {
       	 std::cout << "[EventAction] No Garfield interactions!" << std::endl;
       }
     }

    
  
  //if (nbOfFired2 >0) fRunAction->CountEvent2();

   
  //G4cout << ">>> Summary of Event " << evt->GetEventID() << G4endl;
  // get number of stored trajectories
  auto analysisManager = G4AnalysisManager::Instance();
  /**
  analysisManager->FillH1(4,1);
  //if(!(photon_energy_phantom->size()>0 || neutronEnergy->size()>0))
  if(!(photon_energy_converter->size()>0))
    return;
  
  analysisManager->FillNtupleDColumn(0, energyConverter/keV);
  //analysisManager->FillNtupleDColumn(1, energyAbsorber/keV);
  analysisManager->FillNtupleDColumn(2, edepTot/keV);
  //analysisManager->FillNtupleDColumn(3, position_cog/edepTot);
  //analysisManager->FillNtupleDColumn(4, position_max);
  analysisManager->FillNtupleDColumn(12, photon_energy_converter->size());
  if(ke_stop->size())
    {
      //need adjusting if phantom moves/changes size
      G4double xpos_stop_rel = xpos_stop->at(0) + 100;
      G4double ypos_stop_rel = ypos_stop->at(0) + 75;
      G4double zpos_stop_rel = zpos_stop->at(0);

      analysisManager->FillNtupleDColumn(16, xpos_stop_rel);
      analysisManager->FillNtupleDColumn(17, ypos_stop_rel);
      analysisManager->FillNtupleDColumn(18, zpos_stop_rel);
    }
  analysisManager->FillNtupleDColumn(19, ke_stop->size()); 
  analysisManager->FillNtupleDColumn(20, photon_energy_phantom->size()); 
  analysisManager->FillNtupleDColumn(29, photon_energy_productionconverter->size());
  analysisManager->FillNtupleDColumn(38, photon_energy_productionstrips->size());
  analysisManager->FillNtupleDColumn(47, neutronEnergy->size());
  analysisManager->FillNtupleDColumn(56, neutron_energy_converter->size());

  analysisManager->FillNtupleDColumn(64, electron_energy_production->size());
  
  analysisManager->FillNtupleDColumn(73, positron_energy_production->size());

  analysisManager->FillNtupleDColumn(82, particle_energy_production->size());

  //analysisManager->FillNtupleDColumn(5, energyActdet/keV);
  //analysisManager->FillNtupleDColumn(5, energyActdet_photon/keV);
  // analysisManager->FillNtupleDColumn(6, energyActdet_electron/keV);
  //analysisManager->FillNtupleDColumn(*energy_strips);
  //man->FillNtupleDColumn(1, fEnergyGap);
  */
  //analysisManager->FillNtupleDColumn(108, signalNt);
  //analysisManager->FillNtupleDColumn(109, signaltNt);

  analysisManager->AddNtupleRow();  
    
}
  
void EventAction::InitialElectronNumber()
{}

void EventAction::InitialElectrons()
{}

void EventAction::InitialIons()
{}

void EventAction::FinalElectrons()
{}

void EventAction::FinalIons()
{}

void EventAction::ElectronDriftTime()
{}

void EventAction::IonDriftTime()
{}

void EventAction::AvalancheSize()
{}

void EventAction::AvalCustomValues()
{}

void EventAction::GarfieldSignal()
{}

void EventAction::GarfieldPulse()
{}

// Commented out code from within loop over number of hits

  // 	  (*energy_strips).push_back(edep);
	  
  // 	  if(edep>0)
  // 	    {
  // 	      detector_energy->push_back(edep);
  // 	      detector_position_cog->push_back(posX);
  // 	      detector_position_max->push_back(posX);
  // 	    }

  // 	  position_cog+= posX*edep;	
  // 	  edepTot+=edep;
  // 	  if(energy_max<edep)
  // 	    {
  // 	      energy_max=edep;
  // 	      position_max=posX;
  // 	    }
  // 	  //std::cout << "\n  Hit " << posX << ": " << edep/keV << " keV \n";
  // 	  //if (edep > eThreshold) 
  // 	  //nbOfFired2++;	 

//Old nTuple filling functions



// void EventAction::FillPhotonsAtConverter(G4double energy,G4double xpos, G4double ypos, G4double zpos)
// {
//   photon_energy_converter->push_back(energy);
//   photon_xpos_converter->push_back(xpos);
//   photon_ypos_converter->push_back(ypos);
//   photon_zpos_converter->push_back(zpos);
//   return;
// }



// void EventAction::FillPhotonsAtDetector(G4double energy,
// 					G4double /*xpos*/, G4double /*ypos*/, G4double /*zpos*/, 
// 					G4double /*xdir*/, G4double /*ydir*/, G4double /*zdir*/)
// {
//   photon_energy_detector->push_back(energy);
//   return;
// }



// void EventAction::FillPhotonsAtPhantom(G4double energy,
// 					  G4double xpos, G4double ypos, G4double zpos, 
// 					  G4double xdir, G4double ydir, G4double zdir, G4int createprocess)
// {
//   photon_energy_phantom->push_back(energy);
//   xpos_production->push_back(xpos);
//   ypos_production->push_back(ypos);
//   zpos_production->push_back(zpos);
//   creatorprocess->push_back(createprocess);
//   photon_xdir_production->push_back(xdir);
//   photon_ydir_production->push_back(ydir);
//   photon_zdir_production->push_back(zdir);
  
//   return;
// }



// void EventAction::ProtonStoppedPhantom(G4double ke_f, G4double xpos_f, G4double ypos_f, G4double zpos_f)
// {
//   ke_stop->push_back(ke_f);
//   xpos_stop->push_back(xpos_f);
//   ypos_stop->push_back(ypos_f);
//   zpos_stop->push_back(zpos_f);
//   return;
// }



// void EventAction::PhotonDirectionConverter(G4double xdir, G4double ydir, G4double zdir)
// {
//   photon_xdir_converter->push_back(xdir);
//   photon_ydir_converter->push_back(ydir);
//   photon_zdir_converter->push_back(zdir);
//   return;
// }



// void EventAction::NeutronsProduced(G4double ke_neut, G4double x_neut, G4double y_neut, G4double z_neut, G4double xdir, G4double ydir, G4double zdir, G4int neutProcess)
// {
//   neutronEnergy->push_back(ke_neut);
//   neutronProcess->push_back(neutProcess);
//   neut_xpos->push_back(x_neut);
//   neut_ypos->push_back(y_neut);
//   neut_zpos->push_back(z_neut);
//   neutron_xdir_production->push_back(xdir);
//   neutron_ydir_production->push_back(ydir);
//   neutron_zdir_production->push_back(zdir);
//   return;
// }



// void EventAction::NeutronsConverter(G4double ke_neut, G4double x_neut, G4double y_neut, G4double z_neut, G4double xdir, G4double ydir, G4double zdir)
// {
//   neutron_energy_converter->push_back(ke_neut);
//   neutron_xpos_converter->push_back(x_neut);
//   neutron_ypos_converter->push_back(y_neut);
//   neutron_zpos_converter->push_back(z_neut);
//   neutron_xdir_converter->push_back(xdir);
//   neutron_ydir_converter->push_back(ydir);
//   neutron_zdir_converter->push_back(zdir);
//   return;
// }



// void EventAction::ElectronsProduced(G4double ke, G4double xpos, G4double ypos, G4double zpos, G4double xdir, G4double ydir, G4double zdir, G4int creatorProcess)
// {
//   electron_energy_production->push_back(ke);
//   electron_xpos_production->push_back(xpos) ;
//   electron_ypos_production->push_back(ypos);
//   electron_zpos_production->push_back(zpos);
//   electron_xdir_production->push_back(xdir);
//   electron_ydir_production->push_back(ydir);
//   electron_zdir_production->push_back(zdir);
//   electron_creatorprocess->push_back(creatorProcess);
//   return;
// }



// void EventAction::PositronsProduced(G4double ke, G4double xpos, G4double ypos, G4double zpos, G4double xdir, G4double ydir, G4double zdir, G4int creatorProcess)
// {
//   positron_energy_production->push_back(ke);
//   positron_xpos_production->push_back(xpos) ;
//   positron_ypos_production->push_back(ypos);
//   positron_zpos_production->push_back(zpos);
//   positron_xdir_production->push_back(xdir);
//   positron_ydir_production->push_back(ydir);
//   positron_zdir_production->push_back(zdir);
//   positron_creatorprocess->push_back(creatorProcess);
//   return;
// }



// void EventAction::PhotonsCreatedConverter(G4double ke, G4double xpos, G4double ypos, G4double zpos, G4double xdir, G4double ydir, G4double zdir, G4int creatorProcess)
// {
//   photon_energy_productionconverter->push_back(ke);
//   photon_xpos_productionconverter->push_back(xpos);
//   photon_ypos_productionconverter->push_back(ypos);
//   photon_zpos_productionconverter->push_back(zpos);
//   photon_xdir_productionconverter->push_back(xdir);
//   photon_ydir_productionconverter->push_back(ydir);
//   photon_zdir_productionconverter->push_back(zdir);
//   photon_creatorprocess_converter->push_back(creatorProcess);
//   return;
// }



// void EventAction::PhotonsCreatedStrips(G4double ke, G4double xpos, G4double ypos, G4double zpos, G4double xdir, G4double ydir, G4double zdir, G4int creatorProcess)
// {
//   photon_energy_productionstrips->push_back(ke);
//   photon_xpos_productionstrips->push_back(xpos);
//   photon_ypos_productionstrips->push_back(ypos);
//   photon_zpos_productionstrips->push_back(zpos);
//   photon_xdir_productionstrips->push_back(xdir);
//   photon_ydir_productionstrips->push_back(ydir);
//   photon_zdir_productionstrips->push_back(zdir);
//   photon_creatorprocess_strips->push_back(creatorProcess);
//   return;
// }



// void EventAction::ParticlesProduced(G4double ke, G4double xpos, G4double ypos, G4double zpos, G4double xdir, G4double ydir, G4double zdir, G4int creatorProcess, G4int particle)
// {
//   particle_energy_production->push_back(ke);
//   particle_xpos_production->push_back(xpos);
//   particle_ypos_production->push_back(ypos);
//   particle_zpos_production->push_back(zpos);
//   particle_xdir_production->push_back(xdir);
//   particle_ydir_production->push_back(ydir);
//   particle_zdir_production->push_back(zdir);
//   particle_creatorprocess->push_back(creatorProcess);
//   particle_name->push_back(particle);
//   return;
// }



