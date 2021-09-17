#ifndef ELECTRONDRIFT_H
#define ELECTRONDRIFT_H

#include <iostream>
#include <vector>

#include "ChargeCarrier.hh"

namespace Garfield {
  class AvalancheMC;
  class DriftLineRKF;
  class Sensor;
}

enum class ElectronDriftType {RKF, MCdrift};

class ElectronDrift
{
public:
  ElectronDrift();
  ~ElectronDrift();

  inline void SetDriftType(ElectronDriftType type){m_driftType = type;}
  inline void SetDebug(int level)                 {m_debug = level;}

  inline void EnableSignal() {m_doSignal = true;}
  inline void DisableSignal(){m_doSignal = false;}

  void SetSensor(Garfield::Sensor *sensor);
  void DriftElectrons(std::vector<ChargeCarrier>* electrons);

private:
  Garfield::Sensor*       m_sensor;
  Garfield::DriftLineRKF* m_avalRKF;
  Garfield::AvalancheMC*  m_avalancheMC;
  ElectronDriftType       m_driftType;
  bool m_doSignal;
  int  m_debug;
};

#endif //ELECTRONDRIFT_H
