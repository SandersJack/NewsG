#include "G4VSensitiveDetector.hh"
#include "MyHit.hh"
#include "G4SystemOfUnits.hh"
#include <vector>

class G4Step;
class G4HCofThisEvent;
class MyDetector : public G4VSensitiveDetector
{
public:
  explicit MyDetector(G4String name);
  virtual ~MyDetector();
  
  virtual void Initialize(G4HCofThisEvent*HCE) override;
  virtual G4bool ProcessHits(G4Step*aStep,
			     G4TouchableHistory*ROhist) override; 
  virtual void EndOfEvent(G4HCofThisEvent*HCE) override;
  
private:
  MyHitsCollection * hitsCollection;
  G4int collectionID;
};
