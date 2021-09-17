#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4Allocator.hh"
#include "G4ThreeVector.hh"
class MyHit : public G4VHit
{
public:
  MyHit();
  explicit MyHit(const MyHit& right);
  virtual ~MyHit();

  const MyHit& operator=(const MyHit& right);
  G4int operator==(const MyHit& right) const;
  
  //virtual void Draw();
  inline void SetEnergyDep(G4double eDep){m_eDep = eDep;}
  inline void SetPos(G4ThreeVector xyz){m_pos = xyz;}
  inline void SetElecPos(G4ThreeVector xyz){m_elecPos = xyz;}
  inline void SetTime(G4double time){m_time = time;}
  inline void SetElecTime(G4double time){m_elecTime = time;}
  inline void SetCharge(G4double charge){m_charge = charge;}
  inline void SetElecCharge(G4double charge){m_elecCharge = charge;}
  inline void SetLabel(G4String label){m_label = label;}
  inline void SetW(double value){m_wValue = value;}
  inline void SetFano(double value){m_fano = value;}

  inline G4double      GetEnergyDep(){return m_eDep;}
  inline G4ThreeVector GetPos(){return m_pos;}
  inline G4ThreeVector GetElecPos(){return m_elecPos;}
  inline G4double      GetTime(){return m_time;}
  inline G4double      GetElecTime(){return m_elecTime;}
  inline G4double      GetCharge(){return m_charge;}
  inline G4double      GetElecCharge(){return m_elecCharge;}
  inline G4String      GetLabel(){return m_label;}
  inline double        GetW(){return m_wValue;}
  inline double        GetFano(){return m_fano;}

private:
  G4double      m_eDep;
  G4ThreeVector m_pos;
  G4ThreeVector m_elecPos;
  G4double      m_time;
  G4double      m_elecTime;
  G4double      m_charge;
  G4double      m_elecCharge;
  G4String      m_label;
  double        m_wValue=0;
  double        m_fano=0;
};

typedef G4THitsCollection<MyHit> MyHitsCollection;
