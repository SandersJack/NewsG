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
// $Id: DetectorConstruction.cc 101905 2016-12-07 11:34:39Z gunter $
//
/// \file DetectorConstruction.cc
/// \brief Implementation of the DetectorConstruction class

#include "DetectorConstruction.hh"
#include "DetectorConstructionMessenger.hh"
#include "GasMixture.hh"
#include "UserG4FastSimulationModel.hh"
#include "UserG4SrimModel.hh"

#include "G4GeometryManager.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4PhysicalVolumeStore.hh"
//#include "G4SolidStore.hh"

#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4PVReplica.hh"
#include "G4Region.hh"
#include "G4RotationMatrix.hh"
#include "G4Sphere.hh"
#include "G4SubtractionSolid.hh"
#include "G4Transform3D.hh"
#include "G4Tubs.hh"
#include "G4VisAttributes.hh"

#include "G4UserLimits.hh"

#include "G4MultiFunctionalDetector.hh"
#include "G4PSDoseDeposit.hh"
#include "G4PSEnergyDeposit.hh"
#include "G4SDManager.hh"
#include "G4VPrimitiveScorer.hh"

#include "G4PhysicalConstants.hh"
#include "G4SolidStore.hh"
#include "G4SystemOfUnits.hh"

#include "MyDetector.hh"
#include "GasMixture.hh"
#include "FieldMap.hh"

#include "G4Tubs.hh"

DetectorConstruction::DetectorConstruction(PrimaryGeneratorAction* generator)
    : G4VUserDetectorConstruction(),
      fCheckOverlaps(true),
      fStdConv(false),
      fNx(1000),
      primAction(generator) {
  detectorConstructionMessenger = new DetectorConstructionMessenger(this);
  fConverterThick = 1. * mm;
  fConverterMat = "G4_Cu";
  fDetectorMat = "G4_Ar";
  fRotation = 0. * deg;
  fGap = 25 * cm;  // 76.*mm;
  fGap_x = 0. * mm;
  m_cathodeMatName = "G4_STAINLESS-STEEL";
  m_initParams = new InitialisationParameters();

  nist = G4NistManager::Instance();
}

DetectorConstruction::~DetectorConstruction() {
  delete m_gas_mixture;
  delete m_field_map;
  delete detectorConstructionMessenger;
  delete m_initParams;
}

G4VPhysicalVolume* DetectorConstruction::Construct() {
  G4GeometryManager::GetInstance()->OpenGeometry();
  G4PhysicalVolumeStore::GetInstance()->Clean();
  G4LogicalVolumeStore::GetInstance()->Clean();
  G4SolidStore::GetInstance()->Clean();

  // primAction->BeamPos(fGap_x);
  G4Material* default_mat = nist->FindOrBuildMaterial(m_defaultMatName);

  // World
  // Set the world size to be 2 * (radius + 10cm)
  // The 10cm is just an extra little bit...
  // Set Z size to be the same as XY
  G4double world_sizeXY = 2 * ((m_initParams->GetDetectorRadius() * cm + 10 * cm));
  G4double world_sizeZ = world_sizeXY;
  G4Box* solidWorld = new G4Box("World",  // its name
                                0.5 * world_sizeXY, 0.5 * world_sizeXY,
                                0.5 * world_sizeZ);  // its size
  G4LogicalVolume* logicWorld =
      new G4LogicalVolume(solidWorld,   // its solid
                          default_mat,  // its material
                          "World");     // its name
  G4VPhysicalVolume* physWorld =
      new G4PVPlacement(0,                // no rotation
                        G4ThreeVector(),  // at (0,0,0)
                        logicWorld,       // its logical volume
                        "World",          // its name
                        0,                // its mother  volume
                        false,            // no boolean operation
                        0,                // copy number
                        fCheckOverlaps);  // checking overlaps
  // NEWS-G Spheres

  // Gas Sphere and supporting rod

  G4double gas_outerRad = m_initParams->GetDetectorRadius() * cm;  // 30*cm;
  G4double gas_innerRad = m_initParams->GetAnodeRadius() * cm;     // 0.15*cm;

  // We can setup the Geant4 gas using the Garfield/Magboltz gas
  // The things that is not so nice about this is that we initialise the gas
  // several times in the simulation. It would be good to just do it once.
  m_gas_mixture = new GasMixture();
  m_gas_mixture->SetIonMobilityDir(m_initParams->GetIonMobDir());
  m_gas_mixture->SetGas(
    m_initParams->GetGas(), 
    m_initParams->GetWValue() / eV,
    m_initParams->GetFanoFactor(), 
    m_initParams->GetPressure()
  );

  // Construct the G4 Material
  // converting pressure from Torr (Garfield) to what ever G4 uses
  constexpr double torr = 1.333 * 1e-3 * bar;
  unsigned int n_components = m_gas_mixture->GetGas()->GetNumberOfComponents();
  G4Material* gas_mat = new G4Material(                  //
      m_gas_mixture->GetGas()->GetName(),                   //
      m_gas_mixture->GetGas()->GetMassDensity() * g / cm3,  //
      n_components,                                      //
      kStateGas,                                         //
      CLHEP::STP_Temperature,                            //
      m_gas_mixture->GetGas()->GetPressure() * torr         //
  );

  // Some names are different between Garfield & G4
  // put them into this map and we will convert them
  // This is almost certainly not complete and will need to be expanded if we
  // add new gases
  std::map<std::string, std::string> map_garfield_to_geant;
  map_garfield_to_geant["CH4"] = "METHANE";
  map_garfield_to_geant["N2"] = "N";
  map_garfield_to_geant["O2"] = "O";
  map_garfield_to_geant["iC4H10"] = "BUTANE";


  // Geant 4 wants its fractions given as mass fractions, while Garfield gives
  // us partial pressures (fraction of molecules). We convert between one and
  // the other using the mass of the molecule from Geant multiplied by the
  // fraction from Garfield
  //
  // First loop through the number of compoents and add them to a vector of
  // materials along with their molecule mass * garfield fraction, also compute
  // the total mass (sum of all the fractions)
  std::vector<G4Material*> materials;
  std::vector<double> mass_fractions;
  double total_mass = 0;
  for (unsigned int i = 0; i < n_components; ++i) {
    std::string name;
    double f;
    m_gas_mixture->GetGas()->GetComponent(i, name, f);
    auto it = map_garfield_to_geant.find(name);
    if (it != map_garfield_to_geant.end()) {
      name = it->second;
    }
    G4Material* material = nist->FindOrBuildMaterial("G4_" + name);
    if (!material) {
      const std::string msg =
	("Failed to find material in G4 database.\n"
           "This is likely a mismatch between the names in Garfield/Magboltz "
           "and Geant4.\n"
           "Add a conversion to the `map_garfield_to_geant` in "
           "DetectorConstruction.cc to fix this error.");
      throw std::runtime_error(msg);
    }
    materials.push_back(material);
    double mass_frac = f * material->GetMassOfMolecule();
    mass_fractions.push_back(mass_frac);
    total_mass += mass_frac;
  }

  for (unsigned int i = 0; i < materials.size(); ++i) {
    gas_mat->AddMaterial(materials[i], mass_fractions[i] / total_mass);
  }

  // Print out the gas -- note for the confused
  // Geant4 breaks down molecules into atoms when doing
  // ElmAbundance, e.g. CH4 will be account for separately as C & H
  std::cout << "[DetectorConstruction] Geant4 gas" << std::endl;
  std::cout << gas_mat << std::endl;

  G4Sphere* sphereGas = new G4Sphere("gas_sphere", gas_innerRad, gas_outerRad,
                                     0., 2 * acos(-1), 0., acos(-1));

  // Setup the Garfield++ field map
  m_field_map = new FieldMap();
  m_field_map->SetGas(m_gas_mixture->GetGas());
  m_field_map->SetSensorDir(m_initParams->GetSensorDir());
  m_field_map->Initialise();

  // G4LogicalVolume* logicGas = new G4LogicalVolume(sphereGas,
  // 						      gas_mat,
  // 						      "gas_sphere");
  // G4VPhysicalVolume* physGas = new G4PVPlacement(0,
  // 						     G4ThreeVector(),
  // 						     logicGas,
  // 						     "Gas",
  // 						     logicWorld,
  // 						     false,
  // 						     0,
  // 						     fCheckOverlaps);
  G4double supportRod_innerRad = 0 * mm;
  G4double supportRod_outerRad = 3 * mm;  // was previously 6 mm, corrected on 29/08/19
  G4double supportRod_distanceToAnode = 4. * cm;
  G4double supportRod_halfHeight = (m_initParams->GetDetectorRadius()) * cm;  // 15*cm;
  supportRod_halfHeight =
    (supportRod_halfHeight * 0.5) -
    (supportRod_distanceToAnode *
     0.5);  // 20191024 fix - need to half the distance to the anode here
  G4Material* supportRod_mat = nist->FindOrBuildMaterial("G4_Cu");
  G4double supportRod_position = -(supportRod_halfHeight + supportRod_distanceToAnode);
  G4RotationMatrix* supportRod_rot = new G4RotationMatrix();
  supportRod_rot->rotateX(90 * deg);

  G4Tubs* supportRod = new G4Tubs("supportRod", supportRod_innerRad, supportRod_outerRad, supportRod_halfHeight,
				  0., 2 * acos(-1));
  G4SubtractionSolid* gasGap = new G4SubtractionSolid(
						      "GasGap", sphereGas, supportRod, supportRod_rot, G4ThreeVector(0, supportRod_position, 0));

  G4LogicalVolume* logicGas =
    new G4LogicalVolume(gasGap, gas_mat, "gas_sphere");
  G4VPhysicalVolume* physGas =
    new G4PVPlacement(0, G4ThreeVector(), logicGas, "Gas", logicWorld, false,
		      0, fCheckOverlaps);

  G4LogicalVolume* logicSupportRod = new G4LogicalVolume(supportRod, supportRod_mat, "supportRod_logical");
  G4VPhysicalVolume* physSupportRod =
    new G4PVPlacement(supportRod_rot, G4ThreeVector(0, supportRod_position, 0), logicSupportRod,
		      "SupportRod", logicWorld, false, 0, fCheckOverlaps);

  G4Region* regionGas = new G4Region("gas_region");
  regionGas->AddRootLogicalVolume(logicGas);

  G4cout << "Creating user model" << G4endl;
  UserG4FastSimulationModel* UserModel =
    new UserG4FastSimulationModel("UserModel", regionGas, m_initParams, this);
  if (m_initParams->GetSrimFile() != "") {
    G4cout << "[DetectorConstruction] Using SRIM" << std::endl;
    new UserG4SrimModel("SRIMModel", regionGas, m_initParams, this);
  }
  G4cout << "User model is now initialised" << G4endl;

  // Anode Sphere

  G4double anode_innerRad = 0 * cm;
  G4double anode_outerRad = m_initParams->GetAnodeRadius() * cm;  // 0.15*cm;
  G4Material* anode_mat = nist->FindOrBuildMaterial("G4_Cu");
  G4Sphere* sphereAnode =
    new G4Sphere("anode_sphere", anode_innerRad, anode_outerRad, 0.,
		 2 * acos(-1), 0., acos(-1));
  G4LogicalVolume* logicAnode =
    new G4LogicalVolume(sphereAnode, anode_mat, "anode_sphere");
  G4VPhysicalVolume* physAnode =
    new G4PVPlacement(0, G4ThreeVector(), logicAnode, "Anode", logicWorld,
		      false, 0, fCheckOverlaps);

  // Cathode Sphere

  G4double cathode_innerRad = m_initParams->GetDetectorRadius() * cm;  // 30*cm;
  G4double cathode_outerRad = m_initParams->GetDetectorRadius() * cm + 1. * cm;
  G4Material* cathode_mat = nist->FindOrBuildMaterial(m_cathodeMatName);
  G4Sphere* sphereCathode =
    new G4Sphere("cathode_sphere", cathode_innerRad, cathode_outerRad, 0.,
		 2 * acos(-1), 0., acos(-1));
  G4LogicalVolume* logicCathode =
    new G4LogicalVolume(sphereCathode, cathode_mat, "cathode_sphere");
  G4VPhysicalVolume* physCathode =
    new G4PVPlacement(0, G4ThreeVector(), logicCathode, "Cathode", logicWorld,
		      false, 0, fCheckOverlaps);

  // Print materials
  // G4cout << *(G4Material::GetMaterialTable()) << G4endl;

  // always return the physical World
  return physWorld;
}

void DetectorConstruction::ConstructSDandField() {
  std::cout << "[DetectorConstruction] Constructing sensitive detector!"
            << std::endl;
  delete G4SDManager::GetSDMpointer();
  G4SDManager::GetSDMpointer()->SetVerboseLevel(1);

  MyDetector* gasDetector = new MyDetector("gasDetector");
  G4SDManager::GetSDMpointer()->AddNewDetector(gasDetector);
  this->SetSensitiveDetector("gas_sphere", gasDetector);
}

// Garfield++ and detector gas initialisation
void DetectorConstruction::SetGas(std::string gasType) {
  m_initParams->SetGas(gasType);
  // Add code here to change the geant4 gas composition
}

void DetectorConstruction::SetSensorDir(std::string sensorDir) {
  m_initParams->SetSensorDir(sensorDir);

  m_initParams->SetAnodeVoltage(
				1);  // *** this needs to be fixed for all sensors!!!  ***

  if (sensorDir == "BasicSensor")  // Need to check .mac file to confirm these
    {
      m_initParams->SetDetectorRadius(15.);
      m_initParams->SetAnodeRadius(0.1);
      m_initParams->SetAnodeVoltage(2000);
    }
  else if (sensorDir == "UmbrellaSensor") {
    m_initParams->SetDetectorRadius(30.);
    m_initParams->SetAnodeRadius(0.15);
    m_initParams->SetAnodeVoltage(1850);
  }
    else if (sensorDir == "UmbrellaSensorPaper") {
    m_initParams->SetDetectorRadius(30.);
    m_initParams->SetAnodeRadius(0.15);
    m_initParams->SetAnodeVoltage(2000);
  }
  else if (sensorDir == "ACHINOS_135cm_1p7mm_11anode") {
    m_initParams->SetDetectorRadius(67.5);
    m_initParams->SetAnodeRadius(2);
    m_initParams->SetAnodeVoltage(2030);
  }
  else if (sensorDir == "ACHINOS_300cm_1mm_11anode_DarkSPHERE") {
    m_initParams->SetDetectorRadius(150);
    m_initParams->SetAnodeRadius(11);
    m_initParams->SetAnodeVoltage(3000);
  }
  else if (sensorDir == "ACHINOS_30cm_1mm_11anode_DifferentVoltages") {
    m_initParams->SetDetectorRadius(15);
    m_initParams->SetAnodeRadius(2); //PK: Left this the same as previous achinos. Should this be 2 or the anode radius?
    m_initParams->SetAnodeVoltage(2200);
  }
  else if (sensorDir == "ACHINOS_300cm_1mm_60anode_DarkSPHERE_norod"||sensorDir == "ACHINOS_300cm_1mm_60anode_DarkSPHERE_norRodFiner") {
    m_initParams->SetDetectorRadius(150);
    m_initParams->SetAnodeRadius(11); //PK: Left this the same as previous achinos. Should this be 2 or the anode radius?
    m_initParams->SetAnodeVoltage(3000);
  }
  else if (sensorDir == "ACHINOS_300cm_1mm_60anode_DarkSPHERE_noRod_moreVolumes"||sensorDir == "ACHINOS_300cm_1mm_60anode_DarkSPHERE_noRod_moreVolumes2"){
    m_initParams->SetDetectorRadius(150);
    m_initParams->SetAnodeRadius(12); //PK: Left this the same as previous achinos. Should this be 2 or the anode radius?
    m_initParams->SetAnodeVoltage(3000);
  }
   else if (sensorDir == "ACHINOS_30cm_1p7mm_11anode_Boulby_2200V" ||
	   sensorDir == "ACHINOS_30cm_1p7mm_11anode_Boulby_2200V_1pc" ||
	   sensorDir == "ACHINOS_30cm_1p7mm_11anode_Boulby_2200V_1p5pc" ||
	   sensorDir == "ACHINOS_30cm_1p7mm_11anode_Boulby_2200V_2pc" 
	   ) {
    m_initParams->SetDetectorRadius(15);
    m_initParams->SetAnodeRadius(2); //PK: Left this the same as previous achinos. Should this be 2 or the anode radius?
    m_initParams->SetAnodeVoltage(2200);
  }

  else if (sensorDir == "ACHINOS_30cm_1p7mm_11anode_Boulby_2300V" ||
	   sensorDir == "ACHINOS_30cm_1p7mm_11anode_Boulby_2300V_1pc" ||
	   sensorDir == "ACHINOS_30cm_1p7mm_11anode_Boulby_2300V_1p5pc" ||
	   sensorDir == "ACHINOS_30cm_1p7mm_11anode_Boulby_2300V_2pc" 
	   ) {
    m_initParams->SetDetectorRadius(15);
    m_initParams->SetAnodeRadius(2); //PK: Left this the same as previous achinos. Should this be 2 or the anode radius?
    m_initParams->SetAnodeVoltage(2300);
  }
  else if (sensorDir == "ACHINOS_30cm_1p7mm_11anode_Boulby_2400V" ||
	   sensorDir == "ACHINOS_30cm_1p7mm_11anode_Boulby_2400V_1pc" ||
	   sensorDir == "ACHINOS_30cm_1p7mm_11anode_Boulby_2400V_1p5pc" ||
	   sensorDir == "ACHINOS_30cm_1p7mm_11anode_Boulby_2400V_2pc"
	   ) {
    m_initParams->SetDetectorRadius(15);
    m_initParams->SetAnodeRadius(2); //PK: Left this the same as previous achinos. Should this be 2 or the anode radius?
    m_initParams->SetAnodeVoltage(2400);
  }
     else if (sensorDir == "ACHINOS_30cm_1p7mm_11anode_Boulby_1500V" ||
	   sensorDir == "ACHINOS_30cm_1p7mm_11anode_Boulby_1500V_1pc" ||
	   sensorDir == "ACHINOS_30cm_1p7mm_11anode_Boulby_1500V_1p5pc" ||
	   sensorDir == "ACHINOS_30cm_1p7mm_11anode_Boulby_1500V_2pc"     ||
	   sensorDir == "ACHINOS_30cm_1p7mm_11anode_Boulby_1500V_2p5pc" ||
	   sensorDir == "ACHINOS_30cm_1p7mm_11anode_Boulby_1500V_3pc" ||
	   sensorDir == "ACHINOS_30cm_1p7mm_11anode_Boulby_1500V_5pc" 
	   ) {
    m_initParams->SetDetectorRadius(15);
    m_initParams->SetAnodeRadius(2); //PK: Left this the same as previous achinos. Should this be 2 or the anode radius?
    m_initParams->SetAnodeVoltage(1500);
  }
       else if (sensorDir == "ACHINOS_30cm_1p7mm_11anode_Boulby_3000V" ||
	   sensorDir == "ACHINOS_30cm_1p7mm_11anode_Boulby_3000V_1pc" ||
	   sensorDir == "ACHINOS_30cm_1p7mm_11anode_Boulby_3000V_1p5pc" ||
	   sensorDir == "ACHINOS_30cm_1p7mm_11anode_Boulby_3000V_2pc"     ||
	   sensorDir == "ACHINOS_30cm_1p7mm_11anode_Boulby_3000V_2p5pc" ||
	   sensorDir == "ACHINOS_30cm_1p7mm_11anode_Boulby_3000V_3pc" ||
	   sensorDir == "ACHINOS_30cm_1p7mm_11anode_Boulby_3000V_5pc" 
	   ) {
    m_initParams->SetDetectorRadius(15);
    m_initParams->SetAnodeRadius(2); //PK: Left this the same as previous achinos. Should this be 2 or the anode radius?
    m_initParams->SetAnodeVoltage(3000);
  }
       else if (sensorDir == "ACHINOS_30cm_1p7mm_11anode_Boulby_2250V" ||
	   sensorDir == "ACHINOS_30cm_1p7mm_11anode_Boulby_2250V_1pc" ||
	   sensorDir == "ACHINOS_30cm_1p7mm_11anode_Boulby_2250V_1p5pc" ||
	   sensorDir == "ACHINOS_30cm_1p7mm_11anode_Boulby_2250V_2pc"     ||
	   sensorDir == "ACHINOS_30cm_1p7mm_11anode_Boulby_2250V_2p5pc" ||
	   sensorDir == "ACHINOS_30cm_1p7mm_11anode_Boulby_2250V_3pc" ||
	   sensorDir == "ACHINOS_30cm_1p7mm_11anode_Boulby_2250V_5pc" 
	   ) {
    m_initParams->SetDetectorRadius(15);
    m_initParams->SetAnodeRadius(2); //PK: Left this the same as previous achinos. Should this be 2 or the anode radius?
    m_initParams->SetAnodeVoltage(2250);
  }
  else if (sensorDir == "ACHINOS_30cm_1mm_11anode") {
    m_initParams->SetDetectorRadius(15);
    m_initParams->SetAnodeRadius(2); //PK: Left this the same as previous achinos. Should this be 2 or the anode radius?
    m_initParams->SetAnodeVoltage(2200);
  }
   else if (sensorDir == "ACHINOS_30cm_1mm_11anode_NeutronStudy") {
    m_initParams->SetDetectorRadius(15);
    m_initParams->SetAnodeRadius(2); //PK: Left this the same as previous achinos. Should this be 2 or the anode radius?
    m_initParams->SetAnodeVoltage(4500);
  }
 else if (sensorDir == "ACHINOS_30cm_1p7mm_11anode_Boulby_DifferentVoltages") {
    m_initParams->SetDetectorRadius(15);
    m_initParams->SetAnodeRadius(2); //PK: Left this the same as previous achinos. Should this be 2 or the anode radius?
    m_initParams->SetAnodeVoltage(2200);
  }
  else if (sensorDir == "ACHINOS_30cm_1p7mm_11anode_Boulby") {
    m_initParams->SetDetectorRadius(15);
    m_initParams->SetAnodeRadius(2); //PK: Left this the same as previous achinos. Should this be 2 or the anode radius?
    m_initParams->SetAnodeVoltage(2200);
  }

   else if (sensorDir == "basicAchinos") {
    m_initParams->SetDetectorRadius(65.);
    m_initParams->SetAnodeRadius(2);
    m_initParams->SetAnodeVoltage(2030);
  }

  else if (sensorDir == "NITROGEN_15cm_3mm_5000V") {
    m_initParams->SetDetectorRadius(15.);
    m_initParams->SetAnodeRadius(0.15);
    m_initParams->SetAnodeVoltage(5000);
  }
  else if (sensorDir == "NITROGEN_15cm_3mm_3500V") {
    m_initParams->SetDetectorRadius(15.);
    m_initParams->SetAnodeRadius(0.15);
    m_initParams->SetAnodeVoltage(3500);
  }
  else if (sensorDir == "bordeaux_20cm_2mm_720V") {
    m_initParams->SetDetectorRadius(20.);
    m_initParams->SetAnodeRadius(0.1);
    m_initParams->SetAnodeVoltage(720);
  }
  else if (sensorDir == "bordeaux_20cm_2mm_720V_m150") {
    m_initParams->SetDetectorRadius(20.);
    m_initParams->SetAnodeRadius(0.1);
    m_initParams->SetAnodeVoltage(720);
  }
  else if (sensorDir == "bordeaux_20cm_2mm_2000V") {
    m_initParams->SetDetectorRadius(20.);
    m_initParams->SetAnodeRadius(0.1);
    m_initParams->SetAnodeVoltage(2000);
  }

 else if (sensorDir == "BOULBY_15cm_1p7mm_3800V") {
    m_initParams->SetDetectorRadius(15.);
    m_initParams->SetAnodeRadius(0.085);
    m_initParams->SetAnodeVoltage(3800);
  }

  else if (sensorDir == "SNOGLOBE_65cm_3mm_1100V") {
    m_initParams->SetDetectorRadius(65.);
    m_initParams->SetAnodeRadius(0.15);
    m_initParams->SetAnodeVoltage(1100);
  }
  else if (sensorDir == "SNOGLOBE_135cm_3mm_1100V") {
    m_initParams->SetDetectorRadius(67.5);
    m_initParams->SetAnodeRadius(0.15);
    m_initParams->SetAnodeVoltage(1100);
  }
  else if (sensorDir == "UmbrellaSensor1750V") {
    m_initParams->SetDetectorRadius(30.);
    m_initParams->SetAnodeRadius(0.15);
    m_initParams->SetAnodeVoltage(1750);
  }
  else if (sensorDir == "UmbrellaSensor1800V") {
    m_initParams->SetDetectorRadius(30.);
    m_initParams->SetAnodeRadius(0.15);
    m_initParams->SetAnodeVoltage(1800);
  }
  else if (sensorDir == "UmbrellaSensor1850V") {
    m_initParams->SetDetectorRadius(30.);
    m_initParams->SetAnodeRadius(0.15);
    m_initParams->SetAnodeVoltage(1850);
  }
  else if (sensorDir == "UmbrellaSensor1900V") {
    m_initParams->SetDetectorRadius(30.);
    m_initParams->SetAnodeRadius(0.15);
    m_initParams->SetAnodeVoltage(1900);
  }
  else if (sensorDir == "Segmented9030Length0V15" ||
	   sensorDir == "Segmented9030Length23rds15" ||
	   sensorDir == "Segmented3090Lengthave15" ||
	   sensorDir == "Segmented3090Length23rds15" ||
	   sensorDir == "SegmentedEqualLengthave15" ||
	   sensorDir == "SegmentedEqualLength23rds15") {
    m_initParams->SetDetectorRadius(15.);  // cm
    m_initParams->SetAnodeRadius(0.15);    // cm
    m_initParams->SetAnodeVoltage(2000);
  }
  else if (sensorDir == "Umbrella15cm2mm" ||
	   sensorDir == "Umbrella15cm2mm1430V" ||
	   sensorDir == "Segmented3090Lengthave15cm2mm" ||
	   sensorDir == "Segmented3090Length23rds15cm2mm" ||
	   sensorDir == "Segmented9030Length0V15cm2mm" ||
	   sensorDir == "Segmented3090Lengthave15cm2mm1430V" ||
	   sensorDir == "Segmented3090Length0V15cm2mm1430V") {
    m_initParams->SetDetectorRadius(15.);  // cm
    m_initParams->SetAnodeRadius(0.10);    // cm
    m_initParams->SetAnodeVoltage(1430);
  }
  else {
    std::cout << "[InitialisationParameters] ERROR: Unrecognised sensor name!"
              << std::endl;
  }

  std::cout << "[InitialisationParameters] INFO:: To avoid confusion the "
    "detector radius is "
            << m_initParams->GetDetectorRadius()
            << " and the anode radius is: " << m_initParams->GetAnodeRadius()
            << std::endl;
}
