#include "SteppingAction.hh"
#include "G4SteppingManager.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"

#include "math.h"
#include "Analysis.hh"
#include "Trajectory.hh"

#include "G4Track.hh"
#include "G4Step.hh"
#include "G4ios.hh"
#include "G4RunManager.hh"
#include "G4Event.hh"
#include "G4TrajectoryContainer.hh"

SteppingAction::SteppingAction(DetectorConstruction* det, RunAction* run, EventAction* event, G4int verbosity)
:detector(det), runAction(run), eventAction(event)
{
  verboseLevel = verbosity;
}



void SteppingAction::UserSteppingAction(const G4Step* step)
{ 
  // std::cout << "[SteppingAction] Start of User Step!" << std::endl;
  // get the pre and post point to the step
  G4StepPoint* prePoint      = step->GetPreStepPoint();
  G4StepPoint* postPoint     = step->GetPostStepPoint();
  G4double stepLength        = step->GetStepLength();
  G4TouchableHandle touchable= step->GetPreStepPoint()->GetTouchableHandle();
  G4int CopyNumber           = touchable->GetReplicaNumber();
  G4VPhysicalVolume* pv      = prePoint->GetPhysicalVolume();
  G4VPhysicalVolume* pv_post = postPoint->GetPhysicalVolume();

  G4String particleName = step->GetTrack()->GetDefinition()->GetParticleName();
  G4double ke       = prePoint->GetKineticEnergy()/keV;
  G4double ke_post  = postPoint->GetKineticEnergy()/keV;
  G4ThreeVector pos = prePoint->GetPosition();
  G4double x = pos.getX();
  G4double y = pos.getY();
  G4double z = pos.getZ();
  G4ThreeVector pos_post = postPoint->GetPosition();
  G4double x1 = pos_post.getX();
  G4double y1 = pos_post.getY();
  G4double z1 = pos_post.getZ();
  G4double edep = step->GetTotalEnergyDeposit();
  G4ThreeVector localPosition = touchable->GetHistory()->GetTopTransform().TransformPoint(pos); 
  G4double dx=0.;
  G4double dy=0.;
  G4double dz=0.;

  G4int createprocess=0;
  G4int particle=0;

  // Tracking primary interactions
  if(step->GetTrack()->GetParentID() == 0 && step->GetDeltaEnergy()!=0)
    {
      if(postPoint->GetProcessDefinedStep()->GetProcessName()=="eIoni")
	eventAction->PrimaryProcess(1);
      else if(postPoint->GetProcessDefinedStep()->GetProcessName()=="hIoni")
	eventAction->PrimaryProcess(2);
      else if(postPoint->GetProcessDefinedStep()->GetProcessName()=="ionIoni")
	eventAction->PrimaryProcess(3);
      else if(postPoint->GetProcessDefinedStep()->GetProcessName()=="phot")
	eventAction->PrimaryProcess(4);
      else if(postPoint->GetProcessDefinedStep()->GetProcessName()=="compt")
	eventAction->PrimaryProcess(5);
      else
	eventAction->PrimaryProcess(-1);
      eventAction->PrimaryDeltaEnergy(step->GetDeltaEnergy());
      eventAction->PrimaryRadius(pos.r());
      eventAction->PrimaryCosTheta(pos.cosTheta());
      eventAction->PrimaryPhi(pos.phi());
    }

  //G4double avalSize = (detector->GetUserModel())->GetAvalSize();
  //std::cout << "[SteppingAction] Total Avalanche Size is: " << avalSize << std::endl;

  //if(pv->GetName()=="phantom" && step->IsFirstStepInVolume())
  //std::cout<< step->GetTrack()->GetCurrentStepNumber()<< " " << particleName<<std::endl;
  
  // if(step->GetTrack()->GetCurrentStepNumber()==1)
  //   {

  //     //G4cout<<particleName << " process is "<<step->GetTrack()->GetCreatorProcess()->GetProcessName()<<"\n";
  //     //G4cout<<particleName << "\n";
  //     /*if(step->GetTrack()->GetCreatorProcess())
  // 	G4cout<<particleName << " process is "<<step->GetTrack()->GetCreatorProcess()->GetProcessName()<<"\n";
  // 	else
  // 	G4cout<<particleName << " no creator process" <<"\n";*/
  //     G4ThreeVector dir = prePoint->GetMomentumDirection();
  //     dx = dir.getX();
  //     dy = dir.getY();
  //     dz = dir.getZ();

  //     if(particleName=="gamma")
  // 	particle=1;
  //     else if(particleName=="neutron")
  // 	particle=2;
  //     else if(particleName=="e-")
  // 	particle=3;
  //     else if(particleName=="e+")
  // 	particle=-3;
  //     else if(particleName=="proton")
  // 	particle=4;
  //     else if(particleName=="alpha")
  // 	particle=5;
  //     else if(particleName=="deuteron")
  // 	particle=6;
  //     else
  // 	{
  // 	  particle=0;
  // 	  std::cout<<"untracked particle was "<<particleName<<"\n";
  // 	}

  //     if(step->GetTrack()->GetCreatorProcess())
  // 	{
  // 	  if(step->GetTrack()->GetCreatorProcess()->GetProcessName()=="protonInelastic")
  // 	    createprocess=1;
  // 	  else if(step->GetTrack()->GetCreatorProcess()->GetProcessName()=="neutronInelastic")
  // 	    createprocess=2;
  // 	  else if(step->GetTrack()->GetCreatorProcess()->GetProcessName()=="eBrem")
  // 	    createprocess=3;
  // 	  else if(step->GetTrack()->GetCreatorProcess()->GetProcessName()=="annihil")
  // 	    createprocess=4;
  // 	  else if(step->GetTrack()->GetCreatorProcess()->GetProcessName()=="hIoni")
  // 	    createprocess=5;
  // 	  else if(step->GetTrack()->GetCreatorProcess()->GetProcessName()=="eIoni")
  // 	    createprocess=6;
  // 	  else if(step->GetTrack()->GetCreatorProcess()->GetProcessName()=="compt")
  // 	    createprocess=7;
  // 	  else if(step->GetTrack()->GetCreatorProcess()->GetProcessName()=="phot")
  // 	    createprocess=8;
  // 	  else if(step->GetTrack()->GetCreatorProcess()->GetProcessName()=="conv")
  // 	    createprocess=9;
  // 	  else
  // 	    createprocess=-1;
  // 	}
  //     else
  // 	{
  // 	  createprocess=0;
  // 	}
  //     if(particleName=="gamma")
  // 	{
  // 	  if(pv->GetName()=="phantom")
  // 	    eventAction->FillPhotonsAtPhantom(ke,x,y,z,dx,dy,dz, createprocess);
  // 	  else if(pv->GetName()=="converter")
  // 	    eventAction->PhotonsCreatedConverter(ke,x,y,z,dx,dy,dz, createprocess);
  // 	  else if(pv->GetName().contains("CovX"))
  // 	    eventAction->PhotonsCreatedStrips(ke,x,y,z,dx,dy,dz,createprocess);
  // 	  else
  // 	    std::cout<<"photon produced in " << pv->GetName()<<"\n";
  // 	}
  //     if(particleName=="neutron")
  // 	{
  // 	  if(pv->GetName()=="phantom")
  // 	    eventAction->NeutronsProduced(ke,x,y,z, dx, dy, dz, createprocess);
  // 	  else
  // 	    std::cout<<"neutron produced in " << pv->GetName()<<"\n";
  // 	}
  //     if(particleName=="e-")
  // 	{
  // 	  eventAction->ElectronsProduced(ke,x,y,z,dx,dy,dz, createprocess);
  // 	}
  //     if(particleName=="e+")
  // 	{
  // 	  eventAction->PositronsProduced(ke,x,y,z,dx,dy,dz, createprocess);
  // 	}
  //     eventAction->ParticlesProduced(ke,x,y,z,dx,dy,dz,createprocess,particle);
  //   }

  // if(particleName=="gamma")
  //   {
  //     if(pv->GetName()=="xRepName" && prePoint->GetStepStatus() == fGeomBoundary)
  // 	{
  // 	  //G4cout<< ke/keV << " intial step in detector keV for photon\n ";
  // 	  //if(step->GetTrack()->GetCreatorProcess())
  // 	  //G4cout<<particleName << " "<<step->GetTrack()->GetCreatorProcess()->GetProcessName()<<"\n";
  // 	  //else
  // 	  //G4cout<<particleName << " no creator process" <<"\n";
  // 	  eventAction->FillPhotonsAtDetector(ke,x,y,z,dx,dy,dz);
  // 	  auto analysisManager = G4AnalysisManager::Instance();
  // 	  analysisManager->FillH1(1, ke);
  // 	}
  //     if(pv->GetName()=="converter" && prePoint->GetStepStatus() == fGeomBoundary)
  // 	{
  // 	  G4cout<< ke/keV << " intial step in converter keV for photon\n ";
  // 	  if(step->GetTrack()->GetCreatorProcess())
  // 	    G4cout<<particleName << " "<<step->GetTrack()->GetCreatorProcess()->GetProcessName()<<"\n";
  // 	  else
  // 	    G4cout<<particleName << " no creator process" <<"\n";

  // 	  eventAction->FillPhotonsAtConverter(ke,x,y,z);
  // 	  G4ThreeVector dir = prePoint->GetMomentumDirection();
  // 	  eventAction->PhotonDirectionConverter(dir.getX(), dir.getY(), dir.getZ());
  // 	  auto analysisManager = G4AnalysisManager::Instance();
  // 	  analysisManager->FillH1(2, ke);
  // 	} 
  //     if(pv->GetName()=="phantom" && prePoint->GetStepStatus() == fGeomBoundary)
  // 	{
  // 	  // G4cout<< ke/keV << " leaving the phantom keV for photon\n ";
  // 	  auto analysisManager = G4AnalysisManager::Instance();
  // 	  analysisManager->FillH1(3, ke);
  // 	}
    
  //   }


  // if(particleName=="proton" && step->GetTrack()->GetParentID()==0)
  //   if(ke_post==0)
  //     eventAction->ProtonStoppedPhantom(ke_post, x1,y1,z1);


  // if(particleName=="neutron")
  //   {
  //     if(pv->GetName()=="converter" && prePoint->GetStepStatus() == fGeomBoundary)
  // 	{
  // 	  G4ThreeVector dir = prePoint->GetMomentumDirection();
  // 	  dx = dir.getX();
  // 	  dy = dir.getY();
  // 	  dz =  dir.getZ();
  // 	  eventAction->NeutronsConverter(ke,x,y,z,dx,dy,dz);
  // 	}
  //   }
 
  //std::cout << "[SteppingAction] End of User Step!" << std::endl;
 
  return;
}
