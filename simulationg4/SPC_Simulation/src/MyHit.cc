#include "MyHit.hh"

extern G4Allocator<MyHit> MyHitAllocator;
MyHit::MyHit() {}
MyHit::~MyHit() {}



MyHit::MyHit(const MyHit& right)
: G4VHit() {
  m_eDep = right.m_eDep;
  m_pos = right.m_pos;
  m_time = right.m_time;
  m_charge = right.m_charge;
  m_status = right.m_status;
  m_elecPos = right.m_elecPos;
  m_elecTime = right.m_elecTime;
  m_elecCharge = right.m_elecCharge;
  m_elecStatus = right.m_elecStatus;
  m_label = right.m_label;
  m_wValue = right.m_wValue;
  m_fano = right.m_fano;
  m_avgGain = right.m_avgGain;
}



const MyHit& MyHit::operator=(const MyHit& right) 
{
  m_eDep = right.m_eDep;
  m_pos = right.m_pos;
  m_time = right.m_time;
  m_charge = right.m_charge;
  m_status = right.m_status;
  m_elecPos = right.m_elecPos;
  m_elecTime = right.m_elecTime;
  m_elecCharge = right.m_elecCharge;
  m_elecStatus = right.m_elecStatus;
  m_label = right.m_label;
  m_wValue = right.m_wValue;
  m_fano = right.m_fano;
  m_avgGain = right.m_avgGain;
  return *this;
}



G4int MyHit::operator==(const MyHit& right) const {
return (this == &right) ? 1 : 0;
}
