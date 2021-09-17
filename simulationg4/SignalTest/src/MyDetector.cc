#include "MyDetector.hh"
MyDetector::MyDetector(G4String detectorName)
 :G4VSensitiveDetector(detectorName),
  collectionID(-1)
{
  collectionName.insert("MyHitCollection");
}



MyDetector::~MyDetector()
{
}



void MyDetector::Initialize(G4HCofThisEvent* HCE)
{
  if(collectionID<0) 
    collectionID = GetCollectionID(0);
  
  //std::cout << "[MyDetector] In Initialize!" << std::endl;

  hitsCollection = new MyHitsCollection(GetName(),collectionName[0]);
  //std::cout << hitsCollection->GetName()<<" "<< collectionID<<std::endl;
  HCE->AddHitsCollection(collectionID,hitsCollection);
}



G4bool MyDetector::ProcessHits(G4Step* aStep, G4TouchableHistory* /*ROhist*/)
{

  //std::cout << "[MyDetector] In Process Hits!" << std::endl;

  MyHit* aHit = new MyHit();
  // Ions
  G4StepPoint* prePoint = aStep->GetPreStepPoint();
  aHit->SetPos(prePoint->GetPosition());
  G4double time = aStep->GetPreStepPoint()->GetGlobalTime();
  aHit->SetTime(time);
  G4double charge = aStep->GetPreStepPoint()->GetCharge();
  aHit->SetCharge(charge);
  // Electrons
  G4StepPoint* postPoint = aStep->GetPostStepPoint();
  aHit->SetElecPos(postPoint->GetPosition());
  G4double elecTime = aStep->GetPostStepPoint()->GetGlobalTime();
  aHit->SetElecTime(elecTime);
  G4double elecCharge = aStep->GetPostStepPoint()->GetCharge();
  aHit->SetElecCharge(charge);
  if(aStep->GetTrack()->GetUserInformation() != NULL)
    {
      G4String label = aStep->GetTrack()->GetUserInformation()->GetType();
      aHit->SetLabel(label);
      // Save W and Fano on first hit
      if(postPoint->GetSafety()>1e-19)
	{
	  aHit->SetW(postPoint->GetSafety());
	  aHit->SetFano(postPoint->GetWeight());
	}
    }
  else
    {
      aHit->SetLabel("Geant4Hit");
    }
  hitsCollection->insert(aHit);
  return true;

  delete aHit;
}



void MyDetector::EndOfEvent(G4HCofThisEvent* /*HCE*/)
{
  // std::cout << "[MyDetector] In End of Event!" << std::endl;
}



//====== Commented out energy deposition from ProcessHits ======
// G4double eDep = aStep->GetTotalEnergyDeposit();
// aHit->SetEnergyDep(eDep);


//====== Various commented out couts ======

// std::cout << "[MyDetector] Step: x = " << aStep->GetPreStepPoint()->GetPosition().x()/cm << "cm, y = " << aStep->GetPreStepPoint()->GetPosition().y()/cm << "cm, z = " << aStep->GetPreStepPoint()->GetPosition().z()/cm << "cm" << std::endl;
// std::cout << "[MyDetector] x = " << aHit->GetPos().x()/cm << "cm, y = " << aHit->GetPos().y()/cm << "cm, z = " << aHit->GetPos().z()/cm << "cm" << std::endl; 
// std::cout << "[MyDetector] Energy deposited is: " << eDep/keV << " keV" << std::endl;
// std::cout << "[MyDetector] Global time is: " << time/ns << " ns" << std::endl;

