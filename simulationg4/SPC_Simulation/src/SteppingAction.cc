#include "SteppingAction.hh"
#include "G4SteppingManager.hh"
#include "G4SystemOfUnits.hh"
#include "G4UnitsTable.hh"

#include "Analysis.hh"
#include "Trajectory.hh"
#include "math.h"

#include "G4Event.hh"
#include "G4RunManager.hh"
#include "G4Step.hh"
#include "G4Track.hh"
#include "G4TrajectoryContainer.hh"
#include "G4ios.hh"

SteppingAction::SteppingAction(DetectorConstruction* det, RunAction* run,
                               EventAction* event, G4int verbosity)
    : detector(det), runAction(run), eventAction(event) {
  verboseLevel = verbosity;
}

void SteppingAction::UserSteppingAction(const G4Step* step) {
  // std::cout << "[SteppingAction] Start of User Step!" << std::endl;

  // get the pre and post point to the step
  G4StepPoint* prePoint = step->GetPreStepPoint();
  G4StepPoint* postPoint = step->GetPostStepPoint();
  //G4double stepLength = step->GetStepLength();
  G4TouchableHandle touchable = step->GetPreStepPoint()->GetTouchableHandle();
  //G4int CopyNumber = touchable->GetReplicaNumber();
  G4VPhysicalVolume* pv = prePoint->GetPhysicalVolume();
  //G4VPhysicalVolume* pv_post = postPoint->GetPhysicalVolume();

  G4String particleName = step->GetTrack()->GetDefinition()->GetParticleName();
  G4double ke = prePoint->GetKineticEnergy() / keV;
  G4double ke_post = postPoint->GetKineticEnergy() / keV;
  G4ThreeVector pos = prePoint->GetPosition();
  //G4double x = pos.getX();
  //G4double y = pos.getY();
  //G4double z = pos.getZ();
  G4ThreeVector pos_post = postPoint->GetPosition();
  G4double x1 = pos_post.getX();
  G4double y1 = pos_post.getY();
  G4double z1 = pos_post.getZ();
  G4double edep = step->GetTotalEnergyDeposit();
  G4ThreeVector localPosition = touchable->GetHistory()->GetTopTransform().TransformPoint(pos);

  if(pv->GetName() == "Gas"  && (ke-ke_post) > 0)
              {
                G4RunManager::GetRunManager()->rndmSaveThisEvent();
              }	
double SP = step->GetTrack()->GetDynamicParticle()->GetPDGcode();
if(true) { 
 if( step->GetDeltaEnergy() != 0 && pv->GetName() != "World" && (ke-ke_post) > 0 && SP != 11) {
		std::ofstream outfile;
        	outfile.open("data.txt", std::ios_base::app); // append instead of overwrite
		double SParticle = step->GetTrack()->GetDynamicParticle()->GetPDGcode();
		G4String PVolume = pv->GetName();
		G4String PProcess=  postPoint->GetProcessDefinedStep()->GetProcessName();
		//G4String SProcess = postPoint->GetProcessDefinedStep()->GetProcessName();
		G4ThreeVector newPos = G4ThreeVector(x1, z1, y1);
		double SParent = step->GetTrack()->GetParentID();
		double SRadius = (newPos.r() / cm);
		double theta = newPos.cosTheta();
		double phi = newPos.phi();
		//double ket = ke-ke_post;
		outfile << std::fixed;
		if( step->GetTrack()->GetParentID() == 0 ) {
        	outfile << "Primary "<< ',' <<  PVolume  << ',' << PProcess << ',' << SParticle  << ',' << SRadius <<',' << theta << ',' << phi << ',' << SParent << ',' << edep << std::endl;  
       		outfile.close(); 
		} else if (step->GetTrack()->GetParentID() != 0) {
		outfile << "Secondary " <<  PVolume  << ',' << PProcess << ',' << SParticle  << ',' << SRadius <<',' << theta << ',' << phi << ',' << SParent << ',' << edep << std::endl;
                outfile.close();

};
     };
};
  // Tracking primary interactions
  if (step->GetTrack()->GetParentID() == 0 && /*step->GetDeltaEnergy() < 0 &&*/
      pv->GetName() != "World") {
    std::string primary_process_name =
        postPoint->GetProcessDefinedStep()->GetProcessName();

    if (primary_process_name == "eIoni") {
      eventAction->PrimaryProcess(1);
    } else if (primary_process_name == "hIoni") {
      eventAction->PrimaryProcess(2);
    } else if (primary_process_name == "ionIoni") {
      eventAction->PrimaryProcess(3);
    } else if (primary_process_name == "phot") {
      eventAction->PrimaryProcess(4);
    } else if (primary_process_name == "compt") {
      eventAction->PrimaryProcess(5);
    } else if (primary_process_name == "G4FSMP") {
      eventAction->PrimaryProcess(6);
    } else if (primary_process_name == "msc") {
      eventAction->PrimaryProcess(7);
    } else if (primary_process_name == "Transportation") {
      eventAction->PrimaryProcess(8);
    } else if (primary_process_name == "eBrem") {
      eventAction->PrimaryProcess(9);
    } else if (primary_process_name == "hadElastic") {
      eventAction->PrimaryProcess(10);
    } else if (primary_process_name == "neutronInelastic") {
      eventAction->PrimaryProcess(11);
    } else if (primary_process_name == "nCapture") {
      eventAction->PrimaryProcess(12);
    } else if (primary_process_name == "Rayl") {
      eventAction->PrimaryProcess(13);
    } else {
      std::cout << "Unknown primary process: " << primary_process_name
                << std::endl;
      eventAction->PrimaryProcess(-1);
    }
    eventAction->PrimaryDeltaEnergy(step->GetDeltaEnergy());
    G4ThreeVector newPos = G4ThreeVector(x1, z1, y1);
    eventAction->PrimaryRadius(newPos.r() / cm);
    eventAction->PrimaryCosTheta(newPos.cosTheta());
    eventAction->PrimaryPhi(newPos.phi());
    if (pv->GetName() == "Gas") {
      eventAction->PrimaryVolume(0);
    } else if (pv->GetName() == "Anode") {
      eventAction->PrimaryVolume(1);
    } else if (pv->GetName() == "Cathode") {
      eventAction->PrimaryVolume(2);
    } else if (pv->GetName() == "SupportRod") {
      eventAction->PrimaryVolume(3);
    } else {
      std::cout << "Unknown primary volume: " << pv->GetName() << std::endl;
      eventAction->PrimaryVolume(-1);
    }
  }
  // Tracking secondary particles
  if(false)
    {if (step->GetTrack()->GetParentID() != 0 && step->GetDeltaEnergy() != 0 &&
	 pv->GetName() != "World") {
	eventAction->SecondaryParent(step->GetTrack()->GetParentID());
	eventAction->SecondaryID(step->GetTrack()->GetTrackID());
	eventAction->SecondaryParticleName(
					   step->GetTrack()->GetDynamicParticle()->GetPDGcode()
					   );

	eventAction->SecondaryParticleNameString(particleName);
	std::string secondary_process_name =
	  postPoint->GetProcessDefinedStep()->GetProcessName();
	if (secondary_process_name == "eIoni") {
	  eventAction->SecondaryProcess(1);
	} else if (secondary_process_name == "hIoni") {
	  eventAction->SecondaryProcess(2);
	} else if (secondary_process_name == "ionIoni") {
	  eventAction->SecondaryProcess(3);
	} else if (secondary_process_name == "phot") {
	  eventAction->SecondaryProcess(4);
	} else if (secondary_process_name == "compt") {
	  eventAction->SecondaryProcess(5);
	} else if (secondary_process_name == "G4FSMP") {
	  eventAction->SecondaryProcess(6);
	} else if (secondary_process_name == "msc") {
	  eventAction->SecondaryProcess(7);
	} else if (secondary_process_name == "Transportation") {
	  eventAction->SecondaryProcess(8);
	} else if (secondary_process_name == "eBrem") {
	  eventAction->SecondaryProcess(9);
	} else {
	  std::cout << "Unknown secondary particle process: "
		    << secondary_process_name << std::endl;
	  eventAction->SecondaryProcess(-1);
	}
	eventAction->SecondaryDeltaEnergy(step->GetDeltaEnergy());
	G4ThreeVector newPos = G4ThreeVector(x1, z1, y1);
	eventAction->SecondaryRadius(newPos.r() / cm);
	eventAction->SecondaryCosTheta(newPos.cosTheta());
	eventAction->SecondaryPhi(newPos.phi());

	if (step->GetTrack()->GetParentID() == 1) {
	  double delta_energy = step->GetDeltaEnergy();
	  if (pv->GetName() == "Gas") {
	    eventAction->AddGasEnergy(delta_energy);
	  }
	  eventAction->AddDetectorEnergy(delta_energy);
	}

      }
    }
  return;
}
