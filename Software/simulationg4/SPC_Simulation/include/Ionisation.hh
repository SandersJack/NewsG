#ifndef IONISATION_H
#define IONISATION_H

#include <iostream>
#include <vector>

#include "TVector3.h"

namespace Garfield {
class Sensor;
class TrackHeed;
class TrackSrim;
}  // namespace Garfield

#include "ChargeCarrier.hh"

enum class IonisationType {SingleElectrons, HEED, SRIM};
//enum class DetectorType {Small, SEDINE};

class Ionisation{
public:
  Ionisation();
  ~Ionisation();

  int GetElectrons(std::vector<ChargeCarrier>* electrons);

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
  int m_nElectrons;
  int m_stdGridPosition;

  double m_stdGridRadial[7];
  double m_stdGridCosTheta[7];

  Garfield::Sensor*    m_sensor;
  Garfield::TrackHeed* m_heed;
  Garfield::TrackSrim* m_srim;
  bool m_isAr37calib;
};

#endif //IONISATION_H
