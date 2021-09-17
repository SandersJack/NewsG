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
/// \file electromagnetic/TestEm1/src/TrackingAction.cc
/// \brief Implementation of the TrackingAction class
//
// $Id: TrackingAction.cc 79976 2014-03-27 15:13:45Z gcosmo $
// 
 
#include "TrackingAction.hh"
#include "PrimaryGeneratorAction.hh"
#include "RunAction.hh"
#include "G4RunManager.hh"
#include "G4Track.hh"
#include "Trajectory.hh"
#include "G4TrackingManager.hh"
#include "G4SystemOfUnits.hh"
#include "G4UnitsTable.hh"

TrackingAction::TrackingAction(PrimaryGeneratorAction* genAction)
 : G4UserTrackingAction(),
   fPrimaryGeneratorAction(genAction)
{}
 

 
void TrackingAction::PreUserTrackingAction(const G4Track* /*aTrack*/)
{
  //fpTrackingManager->SetStoreTrajectory(true);
  //fpTrackingManager->SetTrajectory(new Trajectory(aTrack));        
}
 

 
void TrackingAction::PostUserTrackingAction(const G4Track* /*aTrack*/)
{
  // G4cout << " In the TRACKING ACTION " <<G4endl;
  // //increase nb of processed tracks 
  // //count nb of steps of this track
  // G4int   nbSteps = aTrack->GetCurrentStepNumber();
  // G4double Trleng = aTrack->GetTrackLength();
}

