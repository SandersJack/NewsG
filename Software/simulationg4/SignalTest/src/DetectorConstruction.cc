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
#include "UserG4FastSimulationModel.hh"
 
#include "G4GeometryManager.hh"
#include "G4PhysicalVolumeStore.hh"
#include "G4LogicalVolumeStore.hh"
//#include "G4SolidStore.hh"
 
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4Sphere.hh"
//#include "G4Tubs.hh"
//#include "G4SubtractionSolid.hh"
#include "G4VisAttributes.hh"
#include "G4LogicalVolume.hh"
#include "G4Region.hh"
#include "G4PVPlacement.hh"
#include "G4RotationMatrix.hh"
#include "G4Transform3D.hh"
#include "G4PVReplica.hh"
 
#include "G4UserLimits.hh"
 
#include "G4SDManager.hh"
#include "G4MultiFunctionalDetector.hh"
#include "G4VPrimitiveScorer.hh"
#include "G4PSEnergyDeposit.hh"
#include "G4PSDoseDeposit.hh"
 
#include "G4PhysicalConstants.hh"
#include "G4SystemOfUnits.hh"
#include "G4SolidStore.hh"
 
#include "MyDetector.hh"
 
#include "G4Tubs.hh"


 
DetectorConstruction::DetectorConstruction(PrimaryGeneratorAction* generator)
  : G4VUserDetectorConstruction(),
    fCheckOverlaps(true),
    fStdConv(false),
    fNx(1000),
    primAction(generator)
{
  detectorConstructionMessenger = new DetectorConstructionMessenger(this);  
  fConverterThick= 1.*mm;
  fConverterMat  = "G4_Cu";
  fDetectorMat   = "G4_Ar";
  fRotation      = 0.*deg;
  fGap           = 25*cm;//76.*mm;
  fGap_x         = 0.*mm;
  m_initParams = new InitialisationParameters();
}



DetectorConstruction::~DetectorConstruction()
{ 
  delete detectorConstructionMessenger;
  delete m_initParams;
}



G4VPhysicalVolume* DetectorConstruction::Construct()
{  
  G4GeometryManager::GetInstance()->OpenGeometry();
  G4PhysicalVolumeStore::GetInstance()->Clean();
  G4LogicalVolumeStore::GetInstance()->Clean();
  G4SolidStore::GetInstance()->Clean();
 
  //primAction->BeamPos(fGap_x);
 
  G4NistManager* nist       = G4NistManager::Instance();
  G4Material* default_mat   = nist->FindOrBuildMaterial("G4_AIR");
 
  // World
  G4double world_sizeXY = 100*cm;
  G4double world_sizeZ  = 100*cm;
  G4Box* solidWorld = new G4Box("World",                       //its name
                0.5*world_sizeXY, 0.5*world_sizeXY, 0.5*world_sizeZ); //its size
  G4LogicalVolume* logicWorld = new G4LogicalVolume(solidWorld,          //its solid
                            default_mat,         //its material
                            "World");            //its name
  G4VPhysicalVolume* physWorld = new G4PVPlacement(0,                     //no rotation
                           G4ThreeVector(),       //at (0,0,0)
                           logicWorld,            //its logical volume
                           "World",               //its name
                           0,                     //its mother  volume
                           false,                 //no boolean operation
                           0,                     //copy number
                           fCheckOverlaps);       // checking overlaps 
  // NEWS-G Spheres
 
  // Gas Sphere
 
  G4double gas_outerRad = 30*cm;
  G4double gas_innerRad = 0.15*cm;
  //Needs some work to make changing gas compositions easy!
  //std::vector<G4String> elements = {"G4_He", "G4_Ne", "G4_METHANE"};
  //std::vector<G4double> percentages = {72.5, 25., 2.5};
  //if(elements.size()!=percentages.size())
  //  std::cout << "[DetectorConstruction] Number of components and number of percentages given are not equal!" << std::endl;
  //std::vector<G4Element*> nistElements;
  // These values are in percent by MASS, for a gas mixture percentage by NUMBER 72.5% He, 25% Ne, 2.5% CH4

      // G4Material* gas_mat = new G4Material("sedine2018", 1.29*mg/cm3, 3, kStateGas, CLHEP::STP_Temperature, 1*bar);
      // gas_mat->AddMaterial(nist->FindOrBuildMaterial("G4_He"),34.94*perCent);
      // gas_mat->AddMaterial(nist->FindOrBuildMaterial("G4_Ne"),60.24*perCent);
      // gas_mat->AddMaterial(nist->FindOrBuildMaterial("G4_METHANE"),4.82*perCent);

      G4Material* gas_mat = new G4Material("ArCh4_300mb", 0.48*kg/m3, 2, kStateGas, CLHEP::STP_Temperature, 0.3*bar);
      gas_mat->AddMaterial(nist->FindOrBuildMaterial("G4_Ar"), 99.19*perCent);
      gas_mat->AddMaterial(nist->FindOrBuildMaterial("G4_METHANE"), 0.81*perCent);
  // for(int iElement = 0; iElement < elements.size(); iElement++)
  //   {
  //     nistElements.push_back(nist->FindOrBuildMaterial(elements[iElement]));
  //     gas_mat->AddMaterial(nistElements[(nistElements.size())-1],(percentages[iElement]*perCent));
  //   }
  G4Sphere* sphereGas = new G4Sphere("gas_sphere", 
				     gas_innerRad, 
				     gas_outerRad, 
				     0., 
				     2*acos(-1), 
				     0., 
				     acos(-1));
  G4LogicalVolume* logicGas = new G4LogicalVolume(sphereGas,
						  gas_mat,
						  "gas_sphere");
  G4VPhysicalVolume* physGas = new G4PVPlacement(0,
						 G4ThreeVector(),
						 logicGas,
						 "Gas",
						 logicWorld,
						 false,
						 0,
						 fCheckOverlaps);
 
  G4Region* regionGas = new G4Region("gas_region");
  regionGas->AddRootLogicalVolume(logicGas);
 
  G4cout << "Creating user model" << G4endl;
  UserG4FastSimulationModel* UserModel = new UserG4FastSimulationModel("UserModel", regionGas, m_initParams); 
  G4cout << "User model is now initialised" << G4endl;
 
   
 
  //Anode Sphere
   
  G4double anode_innerRad = 0*cm;
  G4double anode_outerRad = 0.15*cm;
  G4Material* anode_mat = nist->FindOrBuildMaterial("G4_Cu");
  G4Sphere* sphereAnode = new G4Sphere("anode_sphere", anode_innerRad, anode_outerRad, 0., 2*acos(-1),0.,acos(-1));
  G4LogicalVolume* logicAnode = new G4LogicalVolume(sphereAnode,
                            anode_mat,
                            "anode_sphere");
  G4VPhysicalVolume* physAnode = new G4PVPlacement(0,
                           G4ThreeVector(),
                           logicAnode,
                           "Anode",
                           logicWorld,
                           false,
                           0,
                           fCheckOverlaps);
 
   
  //Cathode Sphere
 
  G4double cathode_innerRad = 30*cm;
  G4double cathode_outerRad = 33*cm;
  G4Material* cathode_mat = nist->FindOrBuildMaterial("G4_STAINLESS-STEEL");
  G4Sphere* sphereCathode = new G4Sphere("cathode_sphere", cathode_innerRad, cathode_outerRad, 0., 2*acos(-1),0.,acos(-1));
  G4LogicalVolume* logicCathode = new G4LogicalVolume(sphereCathode,
                             cathode_mat,
                             "cathode_sphere");
  G4VPhysicalVolume* physCathode = new G4PVPlacement(0,
                           G4ThreeVector(),
                           logicCathode,
                           "Cathode",
                           logicWorld,
                           false,
                           0,
                           fCheckOverlaps);
 
  // Print materials
  //G4cout << *(G4Material::GetMaterialTable()) << G4endl; 
 
  //always return the physical World
  return physWorld;
}


 
void DetectorConstruction::ConstructSDandField()
{
  std::cout << "[DetectorConstruction] Constructing sensitive detector!" << std::endl;
  delete G4SDManager::GetSDMpointer();
  G4SDManager::GetSDMpointer()->SetVerboseLevel(1);

  MyDetector* gasDetector = new MyDetector("gasDetector");
  G4SDManager::GetSDMpointer()->AddNewDetector(gasDetector);
  this->SetSensitiveDetector("gas_sphere", gasDetector);
}



// Garfield++ and detector gas initialisation
void DetectorConstruction::SetGas(std::string gasType)
{
  m_initParams->SetGas(gasType);
  //Add code here to change the geant4 gas composition
}



void DetectorConstruction::SetIsoPercentage(G4double z)
{
  if (perN+z<1.){
    perIso = z;
    fGasMixtureModified=true;
  }
  else {
    G4cout<<"Attention!!! n = "<<perN*100.
	  <<"% and you are trying to add "<<z*100.
	  <<"% Methane! Reconsider!!!"<<G4endl;
  }
}



void DetectorConstruction::SetNPercentage(G4double z)
{
  if (perIso+z<1.){
    perN=z;
    fGasMixtureModified=true;
  }
  else{ 
    G4cout<<"Attention!!! isobutane = "<<perIso*100.
	     <<"% and you are trying to add "<<z*100.
	     <<"% N! Reconsider!!!"<<G4endl;
  }
}



void DetectorConstruction::SetGasPressure(G4double z)
{
  gasPressure=z;
  fGasMixtureModified=true;
}



// ====== Commented code from ConstructSDandField() ======

/**
   G4MultiFunctionalDetector* converter = new G4MultiFunctionalDetector("converter");
   G4SDManager::GetSDMpointer()->AddNewDetector(converter);
   G4VPrimitiveScorer* primitiv0 = new G4PSEnergyDeposit("edep");
   converter->RegisterPrimitive(primitiv0);
   SetSensitiveDetector("converter_log",converter);
   
   MyDetector* detector=new MyDetector("xRepName");
   G4SDManager::GetSDMpointer()->AddNewDetector(detector);
   
   if(fStdConv)
   {
   //G4MultiFunctionalDetector* detector = new G4MultiFunctionalDetector("xRepName");//detector");
   //G4SDManager::GetSDMpointer()->AddNewDetector(detector);
   //G4VPrimitiveScorer* primitiv1 = new G4PSEnergyDeposit("edep");
   //detector->RegisterPrimitive(primitiv1);
   SetSensitiveDetector("RepX",detector);
   }
   else
   {
   for(G4int i=0;i<fNx/2;i++)
   {
   G4String xRepName("RepX");
   char buff[100];
   snprintf(buff, sizeof(buff), "_%d",i);
   xRepName+=buff;
   
   G4String detectorName("xRepName");
   detectorName+=buff;
   SetSensitiveDetector(xRepName,detector);
   
   }
   }
   // G4MultiFunctionalDetector* actdet = new G4MultiFunctionalDetector("actdet");
   // G4SDManager::GetSDMpointer()->AddNewDetector(actdet);
   // G4VPrimitiveScorer* primitiv2 = new G4PSEnergyDeposit("edep");
   // actdet->RegisterPrimitive(primitiv2);
   // SetSensitiveDetector("actdet_log",actdet);
   **/



// ====== Commented out commands from previous Gamma Camera simulation ======

// void DetectorConstruction::SetConverterThickness(G4double val)
// {
//   //G4cout<<"old conv thickness=" << fConverterThick<<"\n";
//   fConverterThick = val;
//   //G4cout<<"new conv thickness=" << fConverterThick<<"\n";
//   G4RunManager::GetRunManager()->ReinitializeGeometry();
// }
// void DetectorConstruction::SetConverterMaterial(G4String val)
// {
//   // G4cout<<"old =" << fConverterMat<<"\n";
//   fConverterMat = val;
//   // G4cout<<"new =" << fConverterMat<<"\n";
//   G4RunManager::GetRunManager()->ReinitializeGeometry();
// }
// void DetectorConstruction::SetDetectorMaterial(G4String val)
// {
//   fDetectorMat = val;
//   G4RunManager::GetRunManager()->ReinitializeGeometry();
// }
// void DetectorConstruction::SetRotation(G4double val)
// {
//   //G4cout<<"old rotation=" << fRotation<<"\n";
//   fRotation = val;
//   //G4cout<<"new rotation=" << fRotation<<"\n";
//   G4RunManager::GetRunManager()->ReinitializeGeometry();
// }
// void DetectorConstruction::SetGap(G4double val)
// {
//   //G4cout<<"old gap=" << fGap<<"\n";
//   fGap = val;
//   //G4cout<<"new gap=" << fGap<<"\n";
//   G4RunManager::GetRunManager()->ReinitializeGeometry();
// }
 
// void DetectorConstruction::SetGapX(G4double val)
// {
//   //G4cout<<"old gap=" << fGap<<"\n";
//   fGap_x = val;
//   //G4cout<<"new gap=" << fGap<<"\n";
//   G4RunManager::GetRunManager()->ReinitializeGeometry();
// }
