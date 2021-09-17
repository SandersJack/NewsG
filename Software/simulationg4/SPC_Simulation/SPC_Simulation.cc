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
// $Id: exampleB3a.cc 100941 2016-11-03 11:14:13Z gcosmo $
//
/// \file exampleB3a.cc
/// \brief Main program of the B3a example

//#ifdef G4MULTITHREADED
//#include "G4MTRunManager.hh"
//#else
#include "G4RunManager.hh"
//#endif

#include "G4UImanager.hh"

#include "Randomize.hh"
#include "Garfield/Random.hh"

#include "DetectorConstruction.hh"
#include "PhysicsList.hh"
#include "RunAction.hh"
#include "EventAction.hh"
#include "PrimaryGeneratorAction.hh"
#include "StackingAction.hh"
#include "SteppingAction.hh"
#include "TrackingAction.hh"
#include "Trajectory.hh"
#include "TrajectoryPoint.hh"

#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

int main(int argc,char** argv)
{
  // Detect interactive mode (if no arguments) and define UI session
  //
  G4UIExecutive* ui = 0;
  if ( argc == 1 ) {
    ui = new G4UIExecutive(argc, argv);
  }

  // Choose the Random engine
  //
  G4Random::setTheEngine(new CLHEP::RanecuEngine);
  Garfield::randomEngine.Seed(1);

  // Construct the default run manager
  //
  //#ifdef G4MULTITHREADED
  //G4MTRunManager* runManager = new G4MTRunManager;
  //#else
  G4RunManager* runManager = new G4RunManager;
  //#endif

  // Set mandatory initialization classes
  //

  runManager->SetUserInitialization(new PhysicsList);
  PrimaryGeneratorAction* primAction = new PrimaryGeneratorAction();

  DetectorConstruction* det = new DetectorConstruction(primAction);
  runManager->SetUserInitialization(det);
  //runManager->SetUserInitialization(new PhysicsList);

  // Set user action initialization
  RunAction* runAction = new RunAction(det);
  runManager->SetUserAction(runAction);

  EventAction* eventAction = new EventAction(runAction, det);
  runManager->SetUserAction(eventAction);

  SteppingAction* stepAction = new SteppingAction(det, runAction, eventAction);
  runManager->SetUserAction(stepAction);

  //PrimaryGeneratorAction* primAction = new PrimaryGeneratorAction();
  runManager->SetUserAction(primAction);
  runManager->SetUserAction(new StackingAction);

  TrackingAction* trackAction = new TrackingAction(primAction);
  runManager->SetUserAction(trackAction);

  // Initialize visualization
  //
  G4VisManager* visManager = new G4VisExecutive;
  // G4VisExecutive can take a verbosity argument - see /vis/verbose guidance.
  // G4VisManager* visManager = new G4VisExecutive("Quiet");
  visManager->Initialize();

  // Get the pointer to the User Interface manager
  G4UImanager* UImanager = G4UImanager::GetUIpointer();

  // Process macro or start UI session
  //
  if ( ! ui ) {
    // batch mode
    runAction->Macro(argv[1]);
    G4String command = "/control/execute ";
    G4String fileName = argv[1];
    UImanager->ApplyCommand(command+fileName);
  }
  else {
    // interactive mode
    UImanager->ApplyCommand("/control/execute init_vis.mac");
    ui->SessionStart();
    delete ui;
  }

  // Job termination
  // Free the store: user actions, physics_list and detector_description are
  // owned and deleted by the run manager, so they should not be deleted
  // in the main() program !

  delete visManager;
  delete runManager;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo.....
