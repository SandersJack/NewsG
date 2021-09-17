#ifndef ELECTRONAVALANCHE_H
#define ELECTRONAVALANCHE_H
#include <limits.h>
#include <cmath>
#include <iostream>
#include <vector>

#include "TF1.h"
#include "TVector3.h"

#include "ChargeCarrier.hh"

namespace Garfield {
  class Sensor;
  class AvalancheMicroscopic;
  class AvalancheMC;
}

enum class avalType { Microscopic, MC, Custom };
enum class avalMCStepType { nColl, dStep, tStep };

class ElectronAvalanche {
 public:
  ElectronAvalanche();
  ~ElectronAvalanche();

  void SetSensors(std::vector<Garfield::Sensor *> sensorList);
  void Avalanche(std::vector<ChargeCarrier> &electronsIn);

  inline void SetAvalType(avalType theType) { m_avalType = theType; }
  inline void SetMCStepType(avalMCStepType theType) {
    m_avalMCStepType = theType;
  }
  inline void SetSensorRadius(double r) { m_sensorRadius = r; }
  inline void SetMicroMaxAvalanche(int maxAval) { m_maxAval = maxAval; }
  inline void SetMCStepSize(double step) { m_step = step; }
  inline void SetCustomStepSize(double stepSize) { m_stepSize = stepSize; }
  inline void SetDebug(int level) { m_debug = level; }

  inline int GetAvalancheSize() { return m_neTot; }
  inline std::vector<double> GetIntegratedTowns() { return m_intTowns; }
  inline std::vector<double> GetAverageGain() { return m_avGain; }
  inline std::vector<ChargeCarrier> *GetElectrons() { return m_elecsOut; }
  inline std::vector<ChargeCarrier> *GetIons() { return m_ionsOut; }

  inline void EnableDiffusion() { m_diffusion = true; }
  inline void DisableDiffusion() { m_diffusion = false; }
  inline void EnableSingleIon() { m_singleIon = true; }
  inline void DisableSingleIon() { m_singleIon = false; }
  inline void EnableSingleElectron() { m_singleElectron = true; }
  inline void DisableSingleElectron() { m_singleElectron = false; }
  inline void EnableMaxAvalanche() { m_enableMaxAval = true; }
  inline void DisableMaxAvalanche() { m_enableMaxAval = false; }
  inline void EnableSafetyCounter() { m_safetyMax = 40; }
  inline void DisableSafetyCounter() { m_safetyMax = INT_MAX; }

 private:
  Garfield::AvalancheMicroscopic *m_avalancheMicro;
  Garfield::AvalancheMC *m_avalancheMC;
  std::vector<Garfield::Sensor *> m_sensors;
  bool m_doSignal;
  avalType m_avalType;
  avalMCStepType m_avalMCStepType;
  double m_sensorRadius;
  bool m_diffusion;
  bool m_singleIon;
  bool m_singleElectron;
  bool m_enableMaxAval;
  std::vector<ChargeCarrier> *m_ionsOut;
  std::vector<ChargeCarrier> *m_elecsOut;
  int m_debug;
  long int m_safetyMax;

  int m_ne = 0;
  int m_ni = 0;
  int m_np = 0;
  int m_neTot = 0;
  unsigned int m_maxAval = 100000;
  double m_step = 10000;
  double m_stepSize = 0.01;
  std::vector<double> m_intTowns;
  std::vector<double> m_avGain;

  int AvalancheMicroscopic(double &x0, double &y0, double &z0, double &t0,
                           double &e0, double &dx0, double &dy0, double &dz0);
  int AvalancheMC(double &x0, double &y0, double &z0, double &t0, double &e0,
                  double &dx0, double &dy0, double &dz0);
  int AvalancheCustom(double &x0, double &y0, double &z0, double &t0,
                      double &e0, double &dx0, double &dy0, double &dz0);
};

#endif  // ELECTRONAVALANCHE_H
