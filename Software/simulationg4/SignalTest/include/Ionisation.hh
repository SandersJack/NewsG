#ifndef IONISATION_H
#define IONISATION_H

#include "TRandom3.h"
#include "TrackHeed.hh"
#include "TrackSrim.hh"
#include "Medium.hh"
#include "Sensor.hh"

#include <iostream>
#include <vector>

#include "TVector3.h"
#include "TrackElectron.hh"

#include "ChargeCarrier.hh"

enum class IonisationType {SingleElectrons, HEED, SRIM};
//enum class DetectorType {Small, SEDINE};

class Ionisation{
public:
  Ionisation();
  explicit Ionisation(TRandom3* rndm);
  ~Ionisation();
 
  int GetElectrons(std::vector<ChargeCarrier>* electrons);
  
  inline void SetRNDM(TRandom3* rndm)               {m_rndm=rndm;}
  inline void SetIonisationType(IonisationType type){m_ionisationType=type;}
  inline void SetNelectrons(int elec)               {m_nElectrons=elec;}
  inline void SetGridPosition(int grid)             {m_stdGridPosition=grid;}
  inline void SetSensor(Garfield::Sensor* sensor)   {m_sensor=sensor;}

  inline void EnableAr37calib() {m_isAr37calib=true;}
  inline void DisableAr37calib(){m_isAr37calib=false;}
  
  //inline void SetDetectorType(DetectorType type){m_detectorType=type;}

private:
  IonisationType m_ionisationType;
  //DetectorType m_detectorType;
  
  Garfield::TrackHeed* m_heed;
  bool m_isAr37calib;
  
  int m_nElectrons;
  int m_stdGridPosition;

  double m_stdGridRadial[7];
  double m_stdGridCosTheta[7];
  TRandom3* m_rndm;

  Garfield::Sensor*    m_sensor;
  Garfield::TrackSrim* m_srim;
};

#endif //IONISATION_H
