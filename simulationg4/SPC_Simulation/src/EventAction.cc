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
// $Id$
//
/// \file EventAction.cc
/// \brief Implementation of the EventAction class
#include "EventAction.hh"

#include <limits>

#include "Analysis.hh"
#include "ChargeCarrier.hh"
#include "ElectronDrift.hh"
#include "Electronics.hh"
#include "EventMessenger.hh"
#include "FieldMap.hh"
#include "G4Event.hh"
#include "G4HCofThisEvent.hh"
#include "G4RunManager.hh"
#include "G4SDManager.hh"
#include "G4SystemOfUnits.hh"
#include "G4THitsMap.hh"
#include "G4TrajectoryContainer.hh"
#include "G4UnitsTable.hh"
#include "G4VUserEventInformation.hh"
#include "GasMixture.hh"
#include "IonDrift.hh"
#include "MyHit.hh"
#include "PulseAnalysis.hh"
#include "RunAction.hh"
#include "Trajectory.hh"

#include "Garfield/ComponentAnsys121.hh"
#include "Garfield/ComponentUser.hh"
#include "Garfield/Sensor.hh"

#include "DetectorConstruction.hh"

EventAction::EventAction(RunAction* runAction, DetectorConstruction* detector)
    : G4UserEventAction(),
      m_doSignal(1),
      m_doPulse(1),
      m_doAnalysis(1),
      m_signalBinSize(50. * ns),
      m_nSignalBins(50000),
      aCube(30.),         // cm
      signalt0(0. * ns),  // ns
      m_debug(0),
      m_useIdealField(false),
      fRunAction(runAction),
      m_detector_construction(detector),
      fCollID_converter(-1),
      fCollID_detector(-1) {
  m_eventMessenger = new EventMessenger(this);

  // Primary Vertex information
  initialParticleTypeNt = &runAction->initialParticleTypeNt;
  initialParticleEnergyNt = &runAction->initialParticleEnergyNt;
  initialParticleRadiusNt = &runAction->initialParticleRadiusNt;
  initialParticleCosThetaNt = &runAction->initialParticleCosThetaNt;
  initialParticlePhiNt = &runAction->initialParticlePhiNt;
  initialParticleTimeNt = &runAction->initialParticleTimeNt;
  initialParticleDirRadNt = &runAction->initialParticleDirRadNt;
  initialParticleDirCosThetaNt = &runAction->initialParticleDirCosThetaNt;
  initialParticleDirPhiNt = &runAction->initialParticleDirPhiNt;
  initialParticleDirXNt = &runAction->initialParticleDirXNt;
  initialParticleDirYNt = &runAction->initialParticleDirYNt;
  initialParticleDirZNt = &runAction->initialParticleDirZNt;

  // Garfield++ values
  initElecRadiusNt = &runAction->initElecRadiusNt;
  initElecPhiNt = &runAction->initElecPhiNt;
  initElecCosThetaNt = &runAction->initElecCosThetaNt;
  initElecTimeNt = &runAction->initElecTimeNt;
  initElecStatusNt = &runAction->initElecStatusNt;
  initIonRadiusNt = &runAction->initIonRadiusNt;
  initIonPhiNt = &runAction->initIonPhiNt;
  initIonCosThetaNt = &runAction->initIonCosThetaNt;
  initIonTimeNt = &runAction->initIonTimeNt;
  initIonStatusNt = &runAction->initIonStatusNt;
  finElecRadiusNt = &runAction->finElecRadiusNt;
  finElecPhiNt = &runAction->finElecPhiNt;
  finElecCosThetaNt = &runAction->finElecCosThetaNt;
  finElecTimeNt = &runAction->finElecTimeNt;
  finElecStatusNt = &runAction->finElecStatusNt;
  finIonRadiusNt = &runAction->finIonRadiusNt;
  finIonPhiNt = &runAction->finIonPhiNt;
  finIonCosThetaNt = &runAction->finIonCosThetaNt;
  finIonTimeNt = &runAction->finIonTimeNt;
  finIonStatusNt = &runAction->finIonStatusNt;
  ionChargeNt = &runAction->ionChargeNt;
  avalancheSizeNt = &runAction->avalancheSizeNt;

  signalNt = &runAction->signalNt;
  signaltNt = &runAction->signaltNt;
  pulseNt = &runAction->pulseNt;
  pulsetNt = &runAction->pulsetNt;

  north_signalNt = &runAction->north_signalNt;
  north_pulseNt = &runAction->north_pulseNt;

  south_signalNt = &runAction->south_signalNt;
  south_pulseNt = &runAction->south_pulseNt;

  elecDriftTimeNt = &runAction->elecDriftTimeNt;
  ionDriftTimeNt = &runAction->ionDriftTimeNt;
  nInitElecNt = &runAction->nInitElecNt;
  averageGainNt = &runAction->averageGainNt;
  integrateTownsendNt = &runAction->integrateTownsendNt;

  // Primary interaction tracking
  primaryProcess = &runAction->primaryProcess;
  primaryDeltaEnergy = &runAction->primaryDeltaEnergy;
  primaryRadius = &runAction->primaryRadius;
  primaryCosTheta = &runAction->primaryCosTheta;
  primaryPhi = &runAction->primaryPhi;
  primaryVolume = &runAction->primaryVolume;

  // Secondary particle tracking
  secondaryProcess = &runAction->secondaryProcess;
  secondaryDeltaEnergy = &runAction->secondaryDeltaEnergy;
  secondaryRadius = &runAction->secondaryRadius;
  secondaryCosTheta = &runAction->secondaryCosTheta;
  secondaryPhi = &runAction->secondaryPhi;
  secondaryParent = &runAction->secondaryParent;
  secondaryID = &runAction->secondaryID;
  secondaryParticleName = &runAction->secondaryParticleName;
  secondaryParticleNameString = &runAction->secondaryParticleNameString;

  weightingCurrentIntegralNt = &runAction->weightingCurrentIntegralNt;
  weightingPulseIntegralNt = &runAction->weightingPulseIntegralNt;
  weightingAmplitudeNt = &runAction->weightingAmplitudeNt;
  weightingRisetimeNt =  &runAction->weightingRisetimeNt;
  weightingPulseWidthNt = &runAction->weightingPulseWidthNt;
  weightingIntegratedCurrentRisetimeNt = &runAction->weightingIntegratedCurrentRisetimeNt;
  weightingCurrentPeakTimeNt = &runAction->weightingCurrentPeakTimeNt;
  
}

EventAction::~EventAction() { delete m_eventMessenger; }

void EventAction::BeginOfEventAction(const G4Event* evt) {
  // Primary vertex information
  initialParticleTypeNt->clear();
  initialParticleEnergyNt->clear();
  initialParticleRadiusNt->clear();
  initialParticleCosThetaNt->clear();
  initialParticlePhiNt->clear();
  initialParticleTimeNt->clear();
  initialParticleDirRadNt->clear();
  initialParticleDirCosThetaNt->clear();
  initialParticleDirPhiNt->clear();
  initialParticleDirXNt->clear();
  initialParticleDirYNt->clear();
  initialParticleDirZNt->clear();

  // Garfield++ values
  initElecRadiusNt->clear();
  initElecPhiNt->clear();
  initElecCosThetaNt->clear();
  initElecTimeNt->clear();
  initElecStatusNt->clear();
  initIonRadiusNt->clear();
  initIonPhiNt->clear();
  initIonCosThetaNt->clear();
  initIonTimeNt->clear();
  initIonStatusNt->clear();
  finElecRadiusNt->clear();
  finElecPhiNt->clear();
  finElecCosThetaNt->clear();
  finElecTimeNt->clear();
  finElecStatusNt->clear();
  finIonRadiusNt->clear();
  finIonPhiNt->clear();
  finIonCosThetaNt->clear();
  finIonTimeNt->clear();
  finIonStatusNt->clear();
  ionChargeNt->clear();
  avalancheSizeNt->clear();

  signalNt->clear();
  signaltNt->clear();
  pulseNt->clear();
  pulsetNt->clear();

  north_signalNt->clear();
  north_pulseNt->clear();

  south_signalNt->clear();
  south_pulseNt->clear();

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
  primaryVolume->clear();

  // Secondary particle tracking
  secondaryProcess->clear();
  secondaryDeltaEnergy->clear();
  secondaryRadius->clear();
  secondaryCosTheta->clear();
  secondaryPhi->clear();
  secondaryParent->clear();
  secondaryID->clear();
  secondaryParticleName->clear();
  secondaryParticleNameString->clear();

  for (const auto readout :
       m_detector_construction->GetFieldMap()->GetWeightingFieldNames()) {
    weightingCurrentIntegralNt->at(readout).clear();
    weightingPulseIntegralNt->at(readout).clear();
    weightingAmplitudeNt->at(readout).clear();
    weightingRisetimeNt->at(readout).clear();
    weightingPulseWidthNt->at(readout).clear();
    weightingIntegratedCurrentRisetimeNt->at(readout).clear();
    weightingCurrentPeakTimeNt->at(readout).clear();
  }

  m_gas_energy = 0;
  m_detector_energy = 0;

  G4int evtNb = evt->GetEventID();
  std::cout << "================= EVENT " << evtNb + 1
            << " =================" << std::endl;

if(true) {
 std::ofstream outfile;
 outfile.open("data.txt", std::ios_base::app);
 //std::ofstream outfile("data");
 //outfile.open("test.txt", std::ios_base::app); // append instead of overwrite
 outfile << "================= EVENT " << evtNb + 1
            << " =================" << std::endl; 
 outfile.close();
};
 bIsPhoton = false;
  bIsElectron = false;
}

void EventAction::EndOfEventAction(const G4Event* evt) {
  // PrimaryVertex information
  G4PrimaryVertex* primary_vertex = evt->GetPrimaryVertex();
  G4PrimaryParticle* initParticle = primary_vertex->GetPrimary();
  G4ThreeVector initPos = primary_vertex->GetPosition();
  G4ThreeVector initDir = initParticle->GetMomentumDirection();

  if (m_debug >= 1) {
    std::cout << "[EventAction] Initial position: x = " << initPos.x() / cm
              << " cm, y = " << initPos.y() / cm
              << " cm, z = " << initPos.z() / cm << " cm" << std::endl;
  }

  // Swap to our spherical co-ordinates
  G4ThreeVector initPosSwapped{initPos.x(), initPos.z(), initPos.y()};
  if (m_debug >= 1) {
    std::cout << "[EventAction] Initial position: r = "
              << initPosSwapped.r() / cm
              << " cm, cosTheta = " << initPosSwapped.cosTheta()
              << ", phi = " << initPosSwapped.phi() << std::endl;
  }

  // Need to swap y and z so that the G4ThreeVector functions give the correct
  // values (z is usually the phi axis, not y as in our case because of the bar)
  initialParticleRadiusNt->push_back(initPosSwapped.r() / cm);
  initialParticleCosThetaNt->push_back(initPosSwapped.cosTheta());
  initialParticlePhiNt->push_back(initPosSwapped.phi());

  // Swap to our spherical co-ordinates
  G4ThreeVector initDirSwapped{initDir.x(), initDir.z(), initDir.y()};
  if (m_debug >= 1) {
    std::cout << "[EventAction] Initial direction cartesian: x = "
              << initDir.x() << ", y = " << initDir.y()
              << ", z = " << initDir.z() << std::endl;
    std::cout << "[EventAction] Initial direction spherical: r = "
              << initDirSwapped.r() / cm
              << " cm, cosTheta = " << initDirSwapped.cosTheta()
              << ", phi = " << initDirSwapped.phi() << std::endl;
  }

  initialParticleDirRadNt->push_back(initDirSwapped.r());
  initialParticleDirCosThetaNt->push_back(initDirSwapped.cosTheta());
  initialParticleDirPhiNt->push_back(initDirSwapped.phi());
  initialParticleDirXNt->push_back(initDir.x());
  initialParticleDirYNt->push_back(initDir.y());
  initialParticleDirZNt->push_back(initDir.z());

  G4double initTime = primary_vertex->GetT0();
  if (m_debug >= 1) {
    std::cout << "[EventAction] Initial time is: " << initTime / ns
              << std::endl;
  }

  initialParticleTimeNt->push_back(initTime / ns);

  G4double initEnergy = initParticle->GetKineticEnergy();
  initialParticleTypeNt->push_back(initParticle->GetPDGcode());
  initialParticleEnergyNt->push_back(initEnergy / keV);

  if (m_debug >= 1) {
    std::cout << "[EventAction] Name of initial particle is: "
              << initParticle->GetParticleDefinition()->GetParticleName()
              << std::endl;
    std::cout << "[EventAction] Initial energy is: " << initEnergy / keV
              << " keV" << std::endl;
  }

  // End of initial particle stuff

  // Hits collections
  G4HCofThisEvent* HCE = evt->GetHCofThisEvent();
  if (!HCE) return;

  // Get hits collections IDs
  G4SDManager* SDMan = G4SDManager::GetSDMpointer();

  fCollID_detector = SDMan->GetCollectionID("gasDetector/MyHitCollection");
  MyHitsCollection* HitsColl =
      (MyHitsCollection*)(HCE->GetHC(fCollID_detector));
  if (m_debug >= 1) {
    std::cout << "[EventAction] Retrieved hit collection!" << std::endl;
  }

  if (!HitsColl) {
    // If no hits collection write out what we have and move on
    std::cout << "[EventAction] No hit collection!" << std::endl;
    G4AnalysisManager::Instance()->AddNtupleRow();
    return;
  }

  int nHit = HitsColl->entries();
  if (m_debug >= 1) {
    G4cout << "My detector has " << nHit << " hits." << G4endl;
  }

  // Check if any garfield hits
  bool hasGarfieldHits = false;
  for (int i = 0; i < nHit; ++i) {
    G4String label = static_cast<MyHit*>(HitsColl->GetHit(i))->GetLabel();
    if (label == "GarfieldHit") {
      hasGarfieldHits = true;
      break;
    }
  }

  if (!hasGarfieldHits) {
    // If no Garfield interactions, we can just write out the initial particle
    // info and return (move to next event)
    std::cout << "[EventAction] No Garfield interactions!" << std::endl;
    G4AnalysisManager::Instance()->AddNtupleRow();
    return;
  }

  static Electronics* pulseProcess = nullptr;
  if (!pulseProcess) {
    pulseProcess = new Electronics(140., 0.96, -1.);
  }

  static PulseAnalysis* pulseAnalysis = nullptr;
  if (!pulseAnalysis) {
    pulseAnalysis = new PulseAnalysis();
    pulseAnalysis->SetSamplingTime(0.96);
  }

  static FieldMap* fieldMap = nullptr;
  if (!fieldMap) {
    fieldMap = m_detector_construction->GetFieldMap();
    SetaCube(fieldMap->GetMaxBoundingBox());
  }

  signalNt->resize(m_nSignalBins, 0);
  signaltNt->resize(m_nSignalBins, 0);

  // std::cout << "debugging reached sensors" << std::endl;
  static Garfield::Sensor* sensor = nullptr;
  if (!sensor) {
    sensor = new Garfield::Sensor();
    if (m_useIdealField) {
      std::cout << "[EventAction] Using ideal electric field!" << std::endl;
      SetaCube(15.);  // Hardcoded for now!
      sensor->AddComponent(fieldMap->GetIdealFieldMap());
      sensor->AddElectrode(fieldMap->GetIdealFieldMap(), "readout");
    } else {
      std::cout << "[EventAction] Using ANSYS electric field!" << std::endl;
      sensor->AddComponent(fieldMap->GetFieldMap());
      for (const auto& readout : fieldMap->GetWeightingFieldNames()) {
        sensor->AddElectrode(fieldMap->GetFieldMap(), readout);
      }
    }
    sensor->SetArea(-aCube, -aCube, -aCube, aCube, aCube, aCube);
    sensor->SetTimeWindow(signalt0 / ns, m_signalBinSize / ns, m_nSignalBins);
    sensor->EnableDelayedSignal(0);
  }
  // std::cout << "debugging finished sensors, initialising ion drift" <<
  // std::endl;
  static IonDrift* ionDrift = nullptr;
  if (!ionDrift) {
    ionDrift = new IonDrift();
    ionDrift->SetSensor(sensor);
    ionDrift->SetDriftType(DriftType::RKF);
    ionDrift->EnableSignal();
    ionDrift->SetDebug(m_debug);
  }
  // std::cout << "debugging ion drift initialised, initialising electron
  // drift" << std::endl;
  static ElectronDrift* electronDrift = nullptr;
  if (!electronDrift) {
    electronDrift = new ElectronDrift();
    electronDrift->SetSensor(sensor);
    electronDrift->SetDriftType(ElectronDriftType::RKF);
    electronDrift->SetDebug(m_debug);
    electronDrift->EnableSignal();
  }
  // std::cout << "debugging electron drift initialised" << std::endl;

  std::vector<ChargeCarrier>* driftIonPositions =
      new std::vector<ChargeCarrier>;
  std::vector<ChargeCarrier>* driftElectronPositions =
      new std::vector<ChargeCarrier>;
  // Set the start time to something very large
  signalt0 = std::numeric_limits<float>::max();

  int avalancheSize = 0;
  for (int i = 0; i < nHit; ++i) {
    MyHit* aHit = static_cast<MyHit*>(HitsColl->GetHit(i));
    G4String label = aHit->GetLabel();

    // Do not need to worry about swapping y and z co-ordinates here as all
    // of the spherical co-ordinate functions use our custom "ChargeCarrier"
    // class, which already takes this into account
    if (label == "GarfieldHit") {
      G4ThreeVector elecPos = aHit->GetElecPos();
      G4ThreeVector elecPosSwapped{elecPos.x(), elecPos.z(), elecPos.y()};
      G4double elecTime = aHit->GetElecTime();
      initElecRadiusNt->push_back(elecPosSwapped.r() / cm);
      // Need to swap y and z so cosTheta and phi are correct
      initElecCosThetaNt->push_back(elecPosSwapped.cosTheta());
      initElecPhiNt->push_back(elecPosSwapped.phi());
      initElecTimeNt->push_back(elecTime);
      initElecStatusNt->push_back(aHit->GetElecStatus());
      // Get W and Fano from first hit
      if (aHit->GetW() > 1e-19) {
        fRunAction->SetWFano(aHit->GetW(), aHit->GetFano());
      }
      averageGainNt->push_back(aHit->GetGain());

      double x = aHit->GetPos().x();
      double y = aHit->GetPos().y();
      double z = aHit->GetPos().z();
      double t = aHit->GetTime();
      double charge = aHit->GetCharge();
      double status = aHit->GetStatus();

      if (aHit->GetPos().r() > 25 * cm && status == 1) {
        std::cerr << "[EventAction] WARNING: Avalanche radius is greater "
                     "than 25 cm!"
                  << std::endl;
      }

      // Do this y - z swap so that we can make use of the G4ThreeVector
      // cosTheta and phi functions
      G4ThreeVector ionPos = aHit->GetPos();
      G4ThreeVector ionPosSwapped{ionPos.x(), ionPos.z(), ionPos.y()};

      initIonRadiusNt->push_back(ionPosSwapped.r() / cm);
      initIonPhiNt->push_back(ionPosSwapped.phi());
      initIonCosThetaNt->push_back(ionPosSwapped.cosTheta());
      initIonTimeNt->push_back(t / ns);
      initIonStatusNt->push_back(status);
      ionChargeNt->push_back(charge);

      // Check avalanche was successful before adding the charge to the
      // avalanche total
      if (status == 1) {
        avalancheSize += charge;
      }
      // std::cout << "[EventAction] x = " << x/cm << "cm, y = " << y/cm <<
      // "cm, z = " << z/cm << "cm, t = " << t/ns << " ns, charge scale = "
      // << charge << std::endl;

      /////////
      // Pass in Cartesian coordinates here so as to not deal with swapped
      // cosTheta and phi definitions this is to be given to Garfield,
      // that's why in cm
      driftIonPositions->emplace_back();
      driftIonPositions->back().SetPositionCartesian(x / cm, y / cm, z / cm,
                                                     t / ns);
      driftIonPositions->back().SetCharge(charge);
      driftIonPositions->back().SetStatus(status);
      // Only take the t0 if ion is "good" and has charge (not sure if 0 charge
      // is okay but we have some)
      if (status == 1 && charge != 0) {
        signalt0 = std::min(signalt0, t / ns);
      }

      // this is to be given to Garfield, that's why in cm
      driftElectronPositions->emplace_back();
      driftElectronPositions->back().SetPositionCartesian(x / cm, y / cm,
                                                          z / cm, t / ns);
      driftElectronPositions->back().SetCharge(charge);
      driftElectronPositions->back().SetStatus(status);
    }
    // Putting avalancheSize here shows you the size of each individual
    // garfield hit's avalanche
  }

  // If avalanche size is 0 then set t0 to 0
  if (avalancheSize == 0) {
    signalt0 = 0;
  }

  // Set t0 to minimum ion time - 25% of window
  float window = (m_signalBinSize / ns) * m_nSignalBins;
  signalt0 = signalt0 - (window * 0.25);    
  // signalt0 = std::max(signalt0, 0.0);
  sensor->SetTimeWindow(signalt0 / ns, m_signalBinSize / ns, m_nSignalBins);

  nInitElecNt->push_back(initElecRadiusNt->size());
  avalancheSizeNt->push_back(avalancheSize);
  // std::cout << "debugging reached ion drift" << std::endl;
  if (m_debug >= 1)
    std::cout << "[EventAction] Will drift Ions now!" << std::endl;
  ionDrift->DriftIons(driftIonPositions);
  // std::cout << "debugging done ion drift, starting electron drift" <<
  // std::endl;
  if (m_debug >= 1)
    std::cout << "[EventAction] Will drift Electrons now!" << std::endl;
  electronDrift->DriftElectrons(driftElectronPositions);
  // std::cout << "debugging finished electron drift" << std::endl;

  for (unsigned int iIon = 0; iIon < driftIonPositions->size(); ++iIon) {
    finIonRadiusNt->push_back(
        driftIonPositions->at(iIon)
            .r());  // this are in cm because the come back from garfield
    finIonCosThetaNt->push_back(driftIonPositions->at(iIon).cosTheta());
    finIonPhiNt->push_back(driftIonPositions->at(iIon).phi());
    finIonTimeNt->push_back(driftIonPositions->at(iIon).t());
    finIonStatusNt->push_back(driftIonPositions->at(iIon).status());
    ionDriftTimeNt->push_back(
        finIonTimeNt->at(iIon) -
        initIonTimeNt->at(
            iIon));  // this are in ns because the come back from garfield
  }

  for (unsigned int iElec = 0; iElec < driftElectronPositions->size();
       ++iElec) {
    finElecRadiusNt->push_back(
        driftElectronPositions->at(iElec)
            .r());  // this are in cm because the come back from garfield
    finElecCosThetaNt->push_back(driftElectronPositions->at(iElec).cosTheta());
    finElecPhiNt->push_back(driftElectronPositions->at(iElec).phi());
    finElecTimeNt->push_back(
        driftElectronPositions->at(iElec)
            .t());  // this are in ns because the come back from garfield
    finElecStatusNt->push_back(driftElectronPositions->at(iElec).status());
    elecDriftTimeNt->push_back(finElecTimeNt->at(iElec) -
                               initElecTimeNt->at(iElec));
  }

  auto analysisManager = G4AnalysisManager::Instance();
  analysisManager->FillNtupleFColumn(
      fRunAction->m_ntuple_column_ids.at("energy_deposited_gas"),
      m_gas_energy * -1000);

  analysisManager->FillNtupleFColumn(
      fRunAction->m_ntuple_column_ids.at("energy_deposited_detector"),
      m_detector_energy * -1000);

  bool has_north = false;
  bool has_south = false;
  if (m_doSignal) {
    for (const auto& readout : fieldMap->GetWeightingFieldNames()) {
      if (readout == "North") has_north = true;
      if (readout == "South") has_south = true;
    }

    if (has_north) {
      north_signalNt->resize(m_nSignalBins, 0);
    }
    if (has_south) {
      south_signalNt->resize(m_nSignalBins, 0);
    }

    for (int iBin = 0; iBin < m_nSignalBins; ++iBin) {
      for (const auto& readout : fieldMap->GetWeightingFieldNames()) {
        if (readout == "North") {
          north_signalNt->at(iBin) += sensor->GetIonSignal(readout, iBin);
          north_signalNt->at(iBin) += sensor->GetElectronSignal(readout, iBin);
        }
        if (readout == "South") {
          south_signalNt->at(iBin) += sensor->GetIonSignal(readout, iBin);
          south_signalNt->at(iBin) += sensor->GetElectronSignal(readout, iBin);
        }
      }
    }

    // This will analyse every single weighting field that we have defined
    // This should replace anything specific to North/South that is above/below
    std::vector<double> signal(m_nSignalBins), time(m_nSignalBins);
    // Setup the time vector
    for (int ibin=0; ibin < m_nSignalBins; ++ibin) {
      double t = signalt0 + ibin * m_signalBinSize / ns;
      time.at(ibin) = t;
      // This is the ntuple output time
      signaltNt->at(ibin) = t;
    }
    // Loop through all the weighting fields and do the pulse analysis
    for (const auto& readout : fieldMap->GetWeightingFieldNames()) { 
      for (int ibin=0; ibin < m_nSignalBins; ++ibin) {
        // Can get total signal / can also get Ion/Electron signal individually
        double total_signal = sensor->GetSignal(readout, ibin);
        signal.at(ibin) = total_signal;
        if (readout == "readout") {
          signalNt->at(ibin) = total_signal;
        }
      }
      std::vector<double> pulse(0), pulse_time(0);
      // Process the pulses through the FFT
      pulseProcess->ProcessPulseFFT(signal, time, pulse, pulse_time);
      
      if (m_doAnalysis) {        
        pulseAnalysis->AnalysePulse(signal, time, pulse, pulse_time);

        weightingCurrentIntegralNt->at(readout).push_back(pulseAnalysis->currentIntegral());
        weightingPulseIntegralNt->at(readout).push_back(pulseAnalysis->pulseIntegral());
        weightingAmplitudeNt->at(readout).push_back(pulseAnalysis->amplitude());
        weightingRisetimeNt->at(readout).push_back(pulseAnalysis->risetime());
        weightingPulseWidthNt->at(readout).push_back(pulseAnalysis->pulseWidth());
        weightingIntegratedCurrentRisetimeNt->at(readout).push_back(pulseAnalysis->currentIntegratedRisetime());
        weightingCurrentPeakTimeNt->at(readout).push_back(pulseAnalysis->currentPeakingTime());
      }
    }

    sensor->ClearSignal();
  }

  delete driftElectronPositions;
  delete driftIonPositions;

  G4AnalysisManager::Instance()->AddNtupleRow();
}
