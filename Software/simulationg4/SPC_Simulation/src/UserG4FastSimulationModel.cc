#include "UserG4FastSimulationModel.hh"

#include "Garfield/ComponentAnsys121.hh"
#include "Garfield/ComponentUser.hh"
#include "Garfield/Sensor.hh"
#include "Garfield/TrackHeed.hh"

#include "G4TransportationManager.hh"
#include "MyDetector.hh"
#include "DetectorConstruction.hh"

UserG4FastSimulationModel::UserG4FastSimulationModel(
    const G4String& name, G4Region* region, InitialisationParameters* params, DetectorConstruction* detector)
    : G4VFastSimulationModel(name, region),
      m_sensor(new Garfield::Sensor()),
      m_initialElectrons(new Ionisation()),
      m_avalanche(new ElectronAvalanche()),
      m_drift(new IonDrift()),
      m_debug(1),
      m_useGarfield(1),
      m_detector_construction(detector) {
  // std::cout << "[UserG4FastSimulationModel] Creating User Model!" <<
  // std::endl;
  this->Initialise(params);
  m_gotWFano = false;
  if (m_avalanche) m_avalanche->EnableSafetyCounter();

  if (m_debug >= 1) m_trackHeed.EnableDebugging();
  m_trackHeed.EnableDeltaElectronTransport();
}

UserG4FastSimulationModel::~UserG4FastSimulationModel() {
  delete m_sensor;
  delete m_initialElectrons;
  delete m_avalanche;
  delete m_drift;
}

G4bool UserG4FastSimulationModel::IsApplicable(
    const G4ParticleDefinition& particleType) {
  // Case B
  // std::cout << "[UserG4FastSimulationModel] IsApplicable() has been used" <<
  // std::endl;

  // if(&particleType == G4Electron::ElectronDefinition())
  //   std::cout << "It is applicable!" << std::endl;
  // else
  //   std::cout << "It is not applicable!" << std::endl;
  if (m_useGarfield){
    return &particleType == G4Electron::ElectronDefinition();
  }
  else
    return false;
}

G4bool UserG4FastSimulationModel::ModelTrigger(const G4FastTrack& fastTrack) {
  // Case B
  // std::cout << "[UserG4FastSimulationModel] ModelTrigger() has been used" <<
  // std::endl;

  double ekin = fastTrack.GetPrimaryTrack()->GetKineticEnergy() / keV;
  // double ekin = fastTrack.GetPrimaryTrack()->GetKineticEnergy()/eV;
  // std::cout << "Kinetic energy is: " << ekin << " keV" << std::endl;
  // if(ekin < 100) //<100 eV

  if (ekin < 2)  //<2 keV
  {
    // std::cout << "Kinetic energy is low enough!" << std::endl;
    return true;
  } else {
    // std::cout << "Kinetic energy is not low enough!" << std::endl;
    return false;
  }
}

void UserG4FastSimulationModel::DoIt(const G4FastTrack& fastTrack,
                                     G4FastStep& fastStep) {
  int trackID = fastTrack.GetPrimaryTrack()->GetTrackID();
  if (trackID % 100 == 0)
    std::cout << "[UserG4FastSimulation] Track ID is: " << trackID << std::endl;

  TStopwatch timer;
  timer.Start();
  // std::cout << "[UserG4FastSimulation] Starting Garfield++ simulation" <<
  // std::endl;

  // this->ClearVariables();
  // this->BookTree(trackID);

  // G4LogicalVolume* logicVol = fastTrack.GetEnvelopeLogicalVolume();
  // G4VSensitiveDetector* sensDet = logicVol->GetSensitiveDetector();
  // std::cout << "[UserG4FastSimulationModel] SD collection name is: " <<
  // sensDet->GetCollectionName(0) << std::endl;

  const G4ThreeVector localPosition =
      fastTrack.GetPrimaryTrackLocalPosition();  // Same as global position
  const G4ThreeVector globalPosition =
      fastTrack.GetPrimaryTrack()->GetPosition();
  G4ThreeVector localDirection = fastTrack.GetPrimaryTrackLocalDirection();
  double globalTime =
      fastTrack.GetPrimaryTrack()->GetGlobalTime();  // Same as local time
  double eKinetic = fastTrack.GetPrimaryTrack()->GetKineticEnergy();
  double x = localPosition.x();
  double y = localPosition.y();
  double z = localPosition.z();
  double dx = localDirection.x();
  double dy = localDirection.y();
  double dz = localDirection.z();

  // std::cout << "start of garfield " << x/cm << " " << y/cm << " " << z/cm <<
  // std::endl;

  fastStep.KillPrimaryTrack();

  // Remove any electrons not in the gas volume
  Garfield::Medium* gasDummy;
  if (!m_sensor->GetMedium(x / cm, y / cm, z / cm, gasDummy)) {
    std::cout
        << "[UserG4FSM] No medium found at initial position! Skipping Garfield."
        << std::endl;
    return;
  } else if (!gasDummy->IsIonisable()) {
    std::cout
        << "[UserG4FSM] Medium exists but is non-ionisable! Skipping Garfield."
        << std::endl;
    return;
  }

  // double r_cm = sqrt(x/cm*x/cm + y/cm*y/cm + z/cm*z/cm);
  // if(r_cm > 29.9999 || r_cm < 0.1501)
  //   {
  //     std::cout << "[UserG4FSM] Electron is not in sphere - skipping
  //     Garfield" << std::endl; return;
  //   }
  // else if(y/cm < -0.1501 && sqrt(x/cm*x/cm + z/cm*z/cm) < 0.3001)
  //   {
  //     std::cout << "[UserG4FSM] Electron is in bar - skipping Garfield" <<
  //     std::endl; return;
  //   }

  // Garfield::TrackHeed* trackHeed = new Garfield::TrackHeed();
  m_trackHeed.SetSensor(m_sensor);

  // No. of electrons produced in a collision
  int ne = 0;

  // Case B in Geant4/Garfield++ paper
  // Garfield++ requires the variables be in certain units, hence the conversion
  // factors (e.g /cm)
  m_trackHeed.TransportDeltaElectron(x / cm, y / cm, z / cm, globalTime / ns,
                                     eKinetic / eV, dx, dy, dz, ne);
  // std::cout << "[UserG4FastSimulationModel] Number of HEED generated
  // electrons is: " << ne << std::endl;

  std::vector<ChargeCarrier>* electrons = new std::vector<ChargeCarrier>;

  if (m_doGeant4) {
    for (int iElectron = 0; iElectron < ne; iElectron++) {
      double xe, ye, ze, te;
      double ee, dxe, dye, dze;
      m_trackHeed.GetElectron(iElectron, xe, ye, ze, te, ee, dxe, dye, dze);

      // std::cout << "[UserG4FastSimulationModel] Initial Position is: x = " <<
      // xe << " cm\t y = " << ye << " cm\t z = " << ze << " cm" << std::endl;

      electrons->emplace_back();
      electrons->at(electrons->size() - 1).SetPositionCartesian(xe, ye, ze, te);
    }

  } else
    m_initialElectrons->GetElectrons(electrons);

  // for (unsigned int iElectrons = 0; iElectrons < electrons->size();
  //      iElectrons++) {
  //   // this is in cm because of Garfield
  //   initElecRadiusNt.push_back((electrons->at(iElectrons)).GetRadius());
  //   initElecPhiNt.push_back((electrons->at(iElectrons)).GetPhi());
  //   initElecCosThetaNt.push_back((electrons->at(iElectrons)).GetCosTheta());
  //   initElecTimeNt.push_back((electrons->at(iElectrons)).GetTime());
  // }
  std::vector<ChargeCarrier>* initialElectrons = electrons;
  m_avalanche->Avalanche(*electrons);

  // avalancheSizeNt = m_avalanche->GetAvalancheSize();
  // averageGainNt = m_avalanche->GetAverageGain();
  // integrateTownsendNt = m_avalanche->GetIntegratedTowns();

  if (m_doIons) {
    G4VUserTrackInformation* garfieldLabel =
        new G4VUserTrackInformation("GarfieldHit");
    for (unsigned int iIons = 0; iIons < (*m_avalanche->GetIons()).size();
         iIons++) {
      ChargeCarrier ion = m_avalanche->GetIons()->at(iIons);
      ChargeCarrier electron = initialElectrons->at(iIons);

      // initIonRadiusNt.push_back(ion.GetRadius());
      // initIonPhiNt.push_back(ion.GetPhi());
      // initIonCosThetaNt.push_back(ion.GetCosTheta());
      // initIonTimeNt.push_back(ion.GetTime());

      G4ThreeVector ionPosition(ion.GetX() * cm, ion.GetY() * cm,
                                ion.GetZ() * cm);
      G4ThreeVector electronPosition(electron.GetX() * cm, electron.GetY() * cm,
                                     electron.GetZ() * cm);
      // std::cout << "Ion Position: " <<  ionPosition.x()/cm << "\t" <<
      // ionPosition.y()/cm << "\t" << ionPosition.z()/cm << std::endl;

      // Pass information to EventAction to construct signals
      G4Track* fakeTrack = new G4Track();
      G4Step* fakeStep = new G4Step();
      G4Navigator* navigator = new G4Navigator();
      G4TouchableHandle touchableHandle = NULL;

      navigator->SetWorldVolume(
          G4TransportationManager::GetTransportationManager()
              ->GetNavigatorForTracking()
              ->GetWorldVolume());
      navigator->LocateGlobalPointAndUpdateTouchableHandle(
          globalPosition,  // localPosition,
          localDirection, touchableHandle, false);
      G4StepPoint* fakePreStepPoint = fakeStep->GetPreStepPoint();
      G4StepPoint* fakePostStepPoint = fakeStep->GetPostStepPoint();
      // Ions
      fakePreStepPoint->SetTouchableHandle(touchableHandle);
      fakePreStepPoint->SetPosition(ionPosition);
      // std::cout << "Ion Position: " << fakePreStepPoint->GetPosition().x()/cm
      // << "\t" << fakePreStepPoint->GetPosition().y()/cm << "\t" <<
      // fakePreStepPoint->GetPosition().z()/cm << std::endl;

      fakePreStepPoint->SetGlobalTime(ion.GetTime() * ns);
      fakePreStepPoint->SetCharge(ion.GetCharge());
      fakePreStepPoint->SetSafety(m_avalanche->GetAverageGain().at(iIons));
      fakePreStepPoint->SetStepStatus((G4StepStatus)ion.GetStatus());

      // Electrons
      // Store W and Fano in first hit only
      if (!m_gotWFano) {
        fakePostStepPoint->SetSafety(m_trackHeed.GetW());
        fakePostStepPoint->SetWeight(m_trackHeed.GetFanoFactor());
        m_gotWFano = true;
      }

      fakePostStepPoint->SetTouchableHandle(touchableHandle);
      fakePostStepPoint->SetPosition(electronPosition);
      fakePostStepPoint->SetGlobalTime(electron.GetTime() * ns);
      fakePostStepPoint->SetCharge(electron.GetCharge());
      fakePostStepPoint->SetStepStatus((G4StepStatus)electron.GetStatus());

      fakeTrack->SetUserInformation(garfieldLabel);
      fakeStep->SetTrack(fakeTrack);

      // std::cout << "[UserG4FastSimulationModel] Track label is: " <<
      // fakeStep->GetTrack()->GetUserInformation()->GetType() << std::endl;
      // fakeStep->SetTotalEnergyDeposit(9*MeV); <-- Set energy deposit here if
      // needed

      // std::cout << "[UserG4FastSimulationModel] LocalPosition: x = " <<
      // ionPosition.x()/cm << "cm, y = " << ionPosition.y()/cm << "cm, z = " <<
      // ionPosition.z()/cm << "cm, t = " << ion.GetTime()  << " ns, charge scale
      // = " << ion.GetCharge() << std::endl; std::cout <<
      // "[UserG4FastSimulationModel] Step: x = " <<
      // fakeStep->GetPreStepPoint()->GetPosition().x()/cm << "cm, y = " <<
      // fakeStep->GetPreStepPoint()->GetPosition().y()/cm << "cm, z = " <<
      // fakeStep->GetPreStepPoint()->GetPosition().z()/cm << "cm, t = " <<
      // fakeStep->GetPreStepPoint()->GetGlobalTime()/ns << " ns, charge scale =
      // " << ion.GetCharge() << std::endl;

      G4VPhysicalVolume* currentVolume =
          fakeStep->GetPreStepPoint()->GetPhysicalVolume();
      G4VSensitiveDetector* sensitiveDet;

      if (currentVolume != 0) {
        // std::cout << "[UserG4FastSimulationModel] Volume found! Physical: "
        // << currentVolume->GetName()<<  std::endl; std::cout <<
        // "[UserG4FastSimulationModel] Volume found! Logical: " <<
        // currentVolume->GetLogicalVolume()->GetName() <<  std::endl;
        sensitiveDet =
            currentVolume->GetLogicalVolume()->GetSensitiveDetector();
        if (sensitiveDet != 0) {
          // std::cout << "[UserG4FastSimulationModel] SD collection name is: "
          // << sensitiveDet->GetCollectionName(0) << std::endl;
          sensitiveDet->Hit(fakeStep);
        }
      }

      delete navigator;
      delete fakeStep;
      // delete fakeTrack;
    }
    delete garfieldLabel;
  }

  // if (m_doElectronics) {
  //   m_pulseProcess->ProcessPulse(signalNt, signaltNt, pulseNt, pulsetNt);
  // }

  // for (unsigned int iElecs = 0; iElecs < (*m_avalanche->GetElectrons()).size();
  //      iElecs++) {
  //   finElecRadiusNt.push_back(
  //       (*m_avalanche->GetElectrons())[iElecs].GetRadius());
  //   finElecPhiNt.push_back((*m_avalanche->GetElectrons())[iElecs].GetPhi());
  //   finElecCosThetaNt.push_back(
  //       (*m_avalanche->GetElectrons())[iElecs].GetCosTheta());
  //   finElecTimeNt.push_back((*m_avalanche->GetElectrons())[iElecs].GetTime());
  // }

  // for (unsigned int iElecs = 0; iElecs < (*electrons).size(); iElecs++) {
  //   elecDriftTimeNt.push_back((*electrons).at(iElecs).GetDriftTime());
  // }

  // if (m_doIons) {
  //   for (unsigned int iIons = 0; iIons < (*m_avalanche->GetIons()).size();
  //        iIons++) {
  //     finIonRadiusNt.push_back((*m_avalanche->GetIons())[iIons].GetRadius());
  //     finIonPhiNt.push_back((*m_avalanche->GetIons())[iIons].GetPhi());
  //     finIonCosThetaNt.push_back(
  //         (*m_avalanche->GetIons())[iIons].GetCosTheta());
  //     finIonTimeNt.push_back((*m_avalanche->GetIons())[iIons].GetTime());
  //     ionDriftTimeNt.push_back((*m_avalanche->GetIons())[iIons].GetDriftTime());
  //   }
  // }

  // nElecHeedNt.push_back(electrons->size());
  // std::cout << "[UserG4FastSimulationModel] Number of electrons = " <<
  // electrons->size() << std::endl;

  timer.Stop();
  // cpuTimeNt = timer.CpuTime();
  // realTimeNt = timer.RealTime();
  if (m_debug >= 1) {
    std::cout << "[UserG4FastSimulationModel] Cpu time " << timer.CpuTime()
              << std::endl;
    std::cout << "[UserG4FastSimulationModel] Wall time " << timer.RealTime()
              << std::endl;
  }

  // m_tree->Fill();

  delete electrons;
  // delete trackHeed;

  // m_tree->Write("",TObject::kOverwrite);
  // m_file->Close();
}

void UserG4FastSimulationModel::Initialise(InitialisationParameters* params) {
  int debug = params->GetDebug();
  m_debug = debug;

  if (m_debug >= 1) {
    std::cout << "[UserG4FastSimulationModel] Now initializing Garfield++"
              << std::endl;
    std::cout << "[UserG4FastSimulationModel] Initialisation Parameters are: "
              << std::endl;
    params->Print();
  }

  // Inititialisation parameter inputs

  std::string generationType(params->GetGenerationType());
  bool doAr37Calib = params->GetAr37Calib();
  int nElec = params->GetnElec();
  int gridPos = params->GetGridPos();
  std::string initAvalType(params->GetAvalType());
  bool doMicroMax = params->GetMicroMaxState();
  int microMaxSize = params->GetMicroMaxSize();
  std::string MCStepType(params->GetMCStepType());
  int nColl = params->GetMCnColl();
  double MCStepSize = params->GetMCStepSize();
  double customStepSize = params->GetCustomStepSize();
  std::string gasType(params->GetGas());
  std::string ionMobDir(params->GetIonMobDir());
  std::string sensorDir(params->GetSensorDir());
  bool doDiffusion = params->GetDiffusion();
  m_doIons = params->GetIonTracking();
  std::string ionDriftType = params->GetIonDriftType();
  m_doSignal = params->GetSignalCalc();
  m_doElectronics = params->GetPulseCalc();
  m_signalBinSize = params->GetSignalBinSize() / ns;
  m_signalnBins = params->GetSignalnBins();
  bool doSingleElec = params->GetSingleElec();
  bool doSingleIon = params->GetSingleIon();
  bool doFieldPlot = params->GetFieldPlot();
  bool doSafetyCounter = params->GetSafetyCounter();
  bool useIdealField = params->GetIdealField();
  m_useGarfield = params->GetUseGarfield();

  sensor_radius   = params->GetAnodeRadius();
  detector_radius = params->GetDetectorRadius();
  aCube           = detector_radius*1.1;
  anode_voltage   = params->GetAnodeVoltage();

  FieldMap* fieldMap = m_detector_construction->GetFieldMap();

  std::cout << "[UserG4FSM] CREATING SENSORS!" << std::endl;
  if(useIdealField){
    std::cout << "[UserG4FSM] Using ideal electric field!" << std::endl;
    aCube = 15*1.1; // hardcoded for now as ideal is 15cm sphere
    this->FindAmplificationArea(fieldMap->GetIdealFieldMap());   // these two lines for ideal
    this->CreateSensors(fieldMap->GetIdealFieldMap());
    m_sensor->AddComponent(fieldMap->GetIdealFieldMap());
  }
  else {
    std::cout << "[UserG4FSM] Using ANSYS electric field!" << std::endl;
    this->FindAmplificationArea(fieldMap->GetFieldMap());  // these two lines for imported
    this->CreateSensors(fieldMap->GetFieldMap());
    m_sensor->AddComponent(fieldMap->GetFieldMap());
  }

  m_sensor->EnableDelayedSignal(0);

  // avalanche SET UP

  m_avalanche->SetSensors(m_sensors);
  m_avalanche->SetDebug(debug);

  // The MC Avalanche is used for both drifting and (if option enabled) the
  // avalanche We might want to change this in the future, but for now set the
  // settings of both here
  if (MCStepType == "nColl") {
    m_avalanche->SetMCStepType(avalMCStepType::nColl);
    m_avalanche->SetMCStepSize(nColl);
  } else if (MCStepType == "tStep") {
    m_avalanche->SetMCStepType(avalMCStepType::tStep);
    m_avalanche->SetMCStepSize(MCStepSize / ns);
  } else if (MCStepType == "dStep") {
    m_avalanche->SetMCStepType(avalMCStepType::dStep);
    m_avalanche->SetMCStepSize(MCStepSize / cm);
  } else {
    // By default use nColl step size
    m_avalanche->SetMCStepType(avalMCStepType::nColl);
    m_avalanche->SetMCStepSize(nColl);
  }

  doSingleElec ? m_avalanche->EnableSingleElectron()
               : m_avalanche->DisableSingleElectron();

  doSingleIon ? m_avalanche->EnableSingleIon()
              : m_avalanche->DisableSingleIon();

  doSafetyCounter ? m_avalanche->EnableSafetyCounter()
                  : m_avalanche->DisableSafetyCounter();

  if (initAvalType == "MC") {
    m_avalanche->SetAvalType(avalType::MC);
  } else if (initAvalType == "Custom") {
    m_avalanche->SetAvalType(avalType::Custom);
    m_avalanche->SetCustomStepSize(customStepSize / cm);
  } else {
    // By default use microscopic avalanches
    m_avalanche->SetAvalType(avalType::Microscopic);
    if (doMicroMax) {
      m_avalanche->EnableMaxAvalanche();
      m_avalanche->SetMicroMaxAvalanche(microMaxSize);
    } else
      m_avalanche->DisableMaxAvalanche();
  }
  m_avalanche->SetSensorRadius(sensor_radius);  // cm
  doDiffusion ? m_avalanche->EnableDiffusion()
              : m_avalanche->DisableDiffusion();

  if (generationType == "Geant4")
    m_doGeant4 = TRUE;
  else {
    m_doGeant4 = FALSE;
    if (generationType == "HEED") {
      m_initialElectrons->SetIonisationType(IonisationType::HEED);
      m_initialElectrons->SetSensor(m_sensorIons);
      if (doAr37Calib) m_initialElectrons->EnableAr37calib();
    } else if (generationType == "Electrons") {
      m_initialElectrons->SetIonisationType(IonisationType::SingleElectrons);
      m_initialElectrons->SetGridPosition(gridPos);
      m_initialElectrons->SetNelectrons(nElec);
    } else if (generationType == "SRIM") {
      m_initialElectrons->SetIonisationType(IonisationType::SRIM);
      m_initialElectrons->SetSensor(m_sensorIons);
    } else {
      // Use HEED by default
      m_initialElectrons->SetIonisationType(IonisationType::HEED);
      m_initialElectrons->SetSensor(m_sensorIons);
    }
  }

  if (doFieldPlot) CalculateEFieldDiff(fieldMap->GetFieldMap());
}

// Private Functions

void UserG4FastSimulationModel::FindAmplificationArea(
    Garfield::ComponentFieldMap* ansysMap) {
  // find region to start microscopic tracking
  // will start microcopic tracking when field is larger than 700 V/cm
  // avalanche begins at about 1kV/cm
  // looking at field above the sensor (along y), where it should be strongest
  {
    Garfield::Medium* gasDummy;
    int statusDummy;
    if (m_debug >= 1) std::cout << "CHECKS of Efield " << std::endl;
    double ex = 0., ey = 0., ez = 0.;
    if (m_debug >= 1)
      std::cout << "Sensor radius = " << sensor_radius << std::endl;
    double r = 2 * sensor_radius;
    // double = 0.3;
    double phi = 1 * acos(-1) / 4;
    ansysMap->ElectricField(r * cos(phi), -5 * sensor_radius, r * sin(phi), ex,
                            ey, ez, gasDummy, statusDummy);
    if (m_debug >= 1) {
      if (gasDummy)
        std::cout << "Test field is inside drift medium!" << std::endl;
      else
        std::cout << "Test field is outside drift medium!" << std::endl;

      std::cout << " electric field at check point"
                << " (Ex,Ey,Ez)= (" << ex << " " << ey << " " << ez
                << "), Magnitude =  " << sqrt(ex * ex + ey * ey + ez * ez)
                << std::endl;
    }
  }

  const double fieldTarget = 800.;

  double radiusLarge = 10. * sensor_radius;
  double radiusSmall = 1. * sensor_radius;
  do {
    Garfield::Medium* gasDummy;
    int statusDummy;
    double ex = 0., ey = 0., ez = 0.;
    double radiusBisect = 0.5 * (radiusLarge + radiusSmall);
    ansysMap->ElectricField(0.0, radiusBisect, 0.0, ex, ey, ez, gasDummy,
                            statusDummy);
    if (m_debug >= 1) {
      std::cout << " electric field at " << radiusBisect / sensor_radius
                << " sensor radii or " << radiusBisect
                << " cm above sensor (Ex,Ey,Ez)= (" << ex << " " << ey << " "
                << ez << "), Magnitude =  " << sqrt(ex * ex + ey * ey + ez * ez)
                << std::endl;
    }
    double fieldTmp = sqrt(ex * ex + ey * ey + ez * ez);
    if (fieldTmp - fieldTarget > 0.)
      radiusSmall = radiusBisect;
    else
      radiusLarge = radiusBisect;
  } while ((radiusLarge - radiusSmall) > 0.01 * sensor_radius);

  aBar = 0.5 * (radiusLarge + radiusSmall);
  if (m_debug >= 1)
    std::cout << "This will be the area (aBar variable)= " << aBar << std::endl;
  return;
}

void UserG4FastSimulationModel::CreateSensors(
    Garfield::Component* ansysMap) {
  m_sensors.clear();
  delete m_sensorIons;
  // Create sensors for different strength analysis
  // barArea is the area near sensor/rod where microcopic tracking of electrons
  // is taking place rest areas are filling the remaining of the sphere
  Garfield::Sensor* centralArea = new Garfield::Sensor();
  centralArea->AddComponent(ansysMap);
  centralArea->AddElectrode(ansysMap, "readout");
  centralArea->SetTimeWindow(m_signalt0, m_signalBinSize, m_signalnBins);
  centralArea->EnableDelayedSignal(0);
  // intentionally made centralArea a bit larger, to avoid electrons going
  // backwards too much incomging electron will be relatively quite a bit in the
  // final area when microscopic trcking begins.
  centralArea->SetArea(-aBar * 1.10, -aCube, -aBar * 1.10, aBar * 1.10,
                        aBar * 1.10, aBar * 1.10);

  // also other areas no need to not overlap, since we do avalMC anyways
  // boundaries create issues with electrons going from area to area
  Garfield::Sensor* idealAreaPosX = new Garfield::Sensor();
  idealAreaPosX->AddComponent(ansysMap);
  idealAreaPosX->SetArea(aBar, -aCube, -aCube, aCube, aCube, aCube);

  Garfield::Sensor* idealAreaNegX = new Garfield::Sensor();
  idealAreaNegX->AddComponent(ansysMap);
  idealAreaNegX->SetArea(-aCube, -aCube, -aCube, -aBar, aCube, aCube);

  Garfield::Sensor* idealAreaPosY = new Garfield::Sensor();
  idealAreaPosY->AddComponent(ansysMap);
  idealAreaPosY->SetArea(-aCube, aBar, -aCube, aCube, aCube, aCube);

  Garfield::Sensor* idealAreaPosZ = new Garfield::Sensor();
  idealAreaPosZ->AddComponent(ansysMap);
  idealAreaPosZ->SetArea(-aCube, -aCube, aBar, aCube, 1.15 * aBar, aCube);

  Garfield::Sensor* idealAreaNegZ = new Garfield::Sensor();
  idealAreaNegZ->AddComponent(ansysMap);
  idealAreaNegZ->SetArea(-aCube, -aCube, -aCube, aCube, 1.15 * aBar, -aBar);

  m_sensorIons = new Garfield::Sensor();
  m_sensorIons->AddComponent(ansysMap);
  m_sensorIons->AddElectrode(ansysMap, "readout");
  m_sensorIons->SetArea(-aCube, -aCube, -aCube, aCube, aCube, aCube);
  m_sensorIons->SetTimeWindow(m_signalt0, m_signalBinSize, m_signalnBins);
  m_sensorIons->EnableDelayedSignal(0);

  m_sensors.push_back(centralArea);
  m_sensors.push_back(idealAreaPosX);
  m_sensors.push_back(idealAreaNegX);
  m_sensors.push_back(idealAreaPosY);
  m_sensors.push_back(idealAreaPosZ);
  m_sensors.push_back(idealAreaNegZ);
}

void UserG4FastSimulationModel::FindAmplificationArea(
    Garfield::ComponentUser* idealMap) {
  // find region to start microscopic tracking
  // will start microcopic tracking when field is larger than 700 V/cm
  // avalanche begins at about 1kV/cm
  // looking at field above the sensor (along y), where it should be strongest
  {
    Garfield::Medium* gasDummy;
    int statusDummy;
    if (m_debug >= 1) std::cout << "CHECKS of Efield " << std::endl;
    double ex = 0., ey = 0., ez = 0.;
    if (m_debug >= 1)
      std::cout << "Sensor radius = " << sensor_radius << std::endl;
    double r = 2 * sensor_radius;
    // double = 0.3;
    double phi = 1 * acos(-1) / 4;
    idealMap->ElectricField(r * cos(phi), -5 * sensor_radius, r * sin(phi), ex,
                            ey, ez, gasDummy, statusDummy);
    if (m_debug >= 1) {
      if (gasDummy)
        std::cout << "Test field is inside drift medium!" << std::endl;
      else
        std::cout << "Test field is outside drift medium!" << std::endl;

      std::cout << " electric field at check point"
                << " (Ex,Ey,Ez)= (" << ex << " " << ey << " " << ez
                << "), Magnitude =  " << sqrt(ex * ex + ey * ey + ez * ez)
                << std::endl;
    }
  }

  const double fieldTarget = 800.;

  double radiusLarge = 10. * sensor_radius;
  double radiusSmall = 1. * sensor_radius;
  do {
    Garfield::Medium* gasDummy;
    int statusDummy;
    double ex = 0., ey = 0., ez = 0.;
    double radiusBisect = 0.5 * (radiusLarge + radiusSmall);
    idealMap->ElectricField(0.0, radiusBisect, 0.0, ex, ey, ez, gasDummy,
                            statusDummy);
    if (m_debug >= 1) {
      std::cout << " electric field at " << radiusBisect / sensor_radius
                << " sensor radii or " << radiusBisect
                << " cm above sensor (Ex,Ey,Ez)= (" << ex << " " << ey << " "
                << ez << "), Magnitude =  " << sqrt(ex * ex + ey * ey + ez * ez)
                << std::endl;
    }
    double fieldTmp = sqrt(ex * ex + ey * ey + ez * ez);
    if (fieldTmp - fieldTarget > 0.)
      radiusSmall = radiusBisect;
    else
      radiusLarge = radiusBisect;
  } while ((radiusLarge - radiusSmall) > 0.01 * sensor_radius);

  aBar = 0.5 * (radiusLarge + radiusSmall);
  if (m_debug >= 1)
    std::cout << "This will be the area = " << aBar << std::endl;
  return;
}

void UserG4FastSimulationModel::CalculateEFieldDiff(
    Garfield::ComponentFieldMap* ansysMap) {
  // nPoints is used to make a square grid in radius and cosTheta
  double nPoints = 100;
  double radiusStep = (detector_radius - sensor_radius) / (nPoints - 1);
  double cosThetaStep = (1 - (-1)) / (nPoints - 1);
  double radius = 0;
  double cosTheta = 0;

  // Constant in ideal E-field - uses global variables
  double geometricConst = anode_voltage / (detector_radius - sensor_radius) *
                          (detector_radius * sensor_radius);

  // Set up canvas and histogram
  TCanvas* c1 = new TCanvas(
      "c1", "Relative difference between Ansys and Ideal E-Fields", 600, 600);
  TH2F* h2d = new TH2F("h2d",
                       "Relative difference between Ansys and Ideal E-Fields; "
                       "Radius (cm); cosTheta",
                       nPoints, sensor_radius, detector_radius, nPoints, -1, 1);
  h2d->GetXaxis()->SetTitleOffset(1.2);
  h2d->GetYaxis()->SetTitleOffset(1.25);
  h2d->SetStats(0);
  // h2d->SetContour(99);
  // gStyle->SetPalette(kCool);

  // E-field variables
  double idealField = 0;
  double ansysField = 0;
  double eFieldDiff = 0;

  // Variables for ansysMap->ElectricField(...)
  Garfield::Medium* gasDummy;
  int statusDummy;
  double ex = 0., ey = 0., ez = 0.;

  // Calculate eField difference and fill histogram
  for (unsigned int iPoint = 0; iPoint < nPoints; iPoint++) {
    radius = sensor_radius + iPoint * radiusStep;
    for (unsigned int jPoint = 0; jPoint < nPoints; jPoint++) {
      cosTheta = -1 + jPoint * cosThetaStep;

      idealField = geometricConst / (radius * radius);

      ansysMap->ElectricField(radius * sin(acos(cosTheta)), radius * cosTheta,
                              0.0, ex, ey, ez, gasDummy, statusDummy);
      ansysField = sqrt(ex * ex + ey * ey + ez * ez);

      eFieldDiff = (ansysField - idealField) / idealField;
      h2d->Fill(radius, cosTheta, eFieldDiff);
    }
  }

  // Save plot
  h2d->Draw("colz");
  c1->Print("eFieldDiffColz.png");
}





// void UserG4FastSimulationModel::BookTree(int trackID) {
//   m_file = new TFile(Form("garfieldOutput/output%d.root", trackID), "RECREATE");
//   m_tree = new TTree("simul", "simul");

//   m_tree->Branch("Event", &eventNt, "Event/I");
//   m_tree->Branch("InitElecRadius", &initElecRadiusNt);
//   m_tree->Branch("InitElecPhi", &initElecPhiNt);
//   m_tree->Branch("InitElecCosTheta", &initElecCosThetaNt);
//   m_tree->Branch("InitElecTime", &initElecTimeNt);
//   m_tree->Branch("InitIonRadius", &initIonRadiusNt);
//   m_tree->Branch("InitIonPhi", &initIonPhiNt);
//   m_tree->Branch("InitIonCosTheta", &initIonCosThetaNt);
//   m_tree->Branch("InitIonTime", &initIonTimeNt);
//   m_tree->Branch("FinElecRadius", &finElecRadiusNt);
//   m_tree->Branch("FinElecPhi", &finElecPhiNt);
//   m_tree->Branch("FinElecCosTheta", &finElecCosThetaNt);
//   m_tree->Branch("FinElecTime", &finElecTimeNt);
//   m_tree->Branch("FinIonRadius", &finIonRadiusNt);
//   m_tree->Branch("FinIonPhi", &finIonPhiNt);
//   m_tree->Branch("FinIonCosTheta", &finIonCosThetaNt);
//   m_tree->Branch("FinIonTime", &finIonTimeNt);
//   m_tree->Branch("AvalancheSize", &avalancheSizeNt, "AvalancheSize/D");
//   m_tree->Branch("Status", &statusNt, "Status/I");
//   m_tree->Branch("Signal", &signalNt);
//   m_tree->Branch("Signalt", &signaltNt);
//   m_tree->Branch("Pulse", &pulseNt);
//   m_tree->Branch("Pulset", &pulsetNt);
//   m_tree->Branch("ElecDriftTime", &elecDriftTimeNt);
//   m_tree->Branch("IonDriftTime", &ionDriftTimeNt);
//   m_tree->Branch("NumElecHeed", &nElecHeedNt);
//   m_tree->Branch("AverageGain", &averageGainNt, "AverageGain/D");
//   m_tree->Branch("IntegratedTownsend", &integrateTownsendNt,
//                  "IntegratedTownsend/D");
//   m_tree->Branch("cpuTime", &cpuTimeNt, "cpuTime/D");
//   m_tree->Branch("realTime", &realTimeNt, "realTime/D");
// }

// void UserG4FastSimulationModel::ClearVariables() {
//   eventNt = 0.;
//   initElecRadiusNt.clear();
//   initElecPhiNt.clear();
//   initElecCosThetaNt.clear();
//   initElecTimeNt.clear();

//   initIonRadiusNt.clear();
//   initIonPhiNt.clear();
//   initIonCosThetaNt.clear();
//   initIonTimeNt.clear();

//   avalancheSizeNt = 0.;
//   statusNt = 1000;
//   ionDriftTimeNt.clear();
//   elecDriftTimeNt.clear();
//   nElecHeedNt.clear();
//   averageGainNt = 0.;
//   integrateTownsendNt = 0.;

//   finElecRadiusNt.clear();
//   finElecPhiNt.clear();
//   finElecCosThetaNt.clear();
//   finElecTimeNt.clear();

//   finIonRadiusNt.clear();
//   finIonPhiNt.clear();
//   finIonCosThetaNt.clear();
//   finIonTimeNt.clear();

//   cpuTimeNt = 0;
//   realTimeNt = 0;

//   for (unsigned int i = 0; i < signalNt.size(); i++) {
//     signalNt[i] = 0;
//     signaltNt[i] = m_signalt0 + i * m_signalBinSize;
//   }
//   pulseNt.clear();
//   pulsetNt.clear();

//   delete signalHistNt;
//   signalHistNt = new TH1D("signalHistNt", ":t[ns]:", m_signalnBins, m_signalt0,
//                           m_signalt0 + m_signalBinSize * m_signalnBins);
//   delete signalHistAvalNt;
//   signalHistAvalNt =
//       new TH1D("signalHistAvalNt", ":t[ns]:", m_signalnBins, m_signalt0,
//                m_signalt0 + m_signalBinSize * m_signalnBins);
// }
