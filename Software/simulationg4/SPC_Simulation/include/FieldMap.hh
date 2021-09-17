#ifndef FIELDMAP_H
#define FIELDMAP_H

#include <string>
#include <iostream>

#include "Garfield/MediumMagboltz.hh"

namespace Garfield {
class ComponentUser;
class ComponentFieldMap;
}  // namespace Garfield

class FieldMap {
 public:
  FieldMap();
  ~FieldMap();

  void Initialise();

  inline void SetGas(Garfield::MediumMagboltz* gas) {
    if (m_owns_gas) {
      delete m_gas;
    }
    m_owns_gas = false;
    m_gas = gas;
  }
  // inline void SetGasIdeal(Garfield::MediumMagboltz* gas){delete m_gasIdeal;
  // m_gasIdeal = gas;}
  inline void SetSensorDir(std::string sensorDir) { m_sensorDir = sensorDir; }

  // inline void SetIdealVoltage(double voltage){m_voltage = voltage;}
  // inline void SetIdealAnodeRadius(double rAnode){m_rAnode = rAnode;}
  // inline void SetIdealCathodeRadius(double rCathode){m_rCathode = rCathode;}

  inline Garfield::ComponentFieldMap* GetFieldMap() { return m_fieldMap; }
  inline Garfield::ComponentUser* GetIdealFieldMap() { return m_idealMap; }
  inline Garfield::MediumMagboltz* GetGas() { return m_gas; }
  inline std::string GetSensorDir() { return m_sensorDir; }
  double GetMaxBoundingBox();

  inline std::vector<std::string> GetWeightingFieldNames() { return m_weighting_field_names; }

 private:
  Garfield::ComponentFieldMap* m_fieldMap;
  // Garfield::ComponentAnsys121* m_ansysMap;
  Garfield::ComponentUser* m_idealMap;
  Garfield::MediumMagboltz* m_gas;
  // Garfield::MediumMagboltz* m_gasIdeal;
  std::string m_sensorDir;

  std::vector<std::string> m_weighting_field_names;

  // Functions for ideal E-field setup
  static constexpr double m_rAnode = 0.1;    // cm anode radius
  static constexpr double m_rCathode = 15.;  // cm cathode radius
  static constexpr double m_voltage = 1430;  // 1600.;

  // static double m_rAnode;// = 0.1; //cm anode radius
  // static double m_rCathode;// = 15.; //cm cathode radius
  // static double m_voltage;// = 1430;//1600.;

  static void Efield(const double x, const double y, const double z, double& ex,
                     double& ey, double& ez);
  static void Wfield(const double x, const double y, const double z, double& wx,
                     double& wy, double& wz, const std::string);
  // static void DelayedWfield(const double x, const double y, const double z,
  // const double t, double& wx, double& wy, double& wz, const std::string);

  std::string find_sensor_dir();

  bool m_owns_gas = false;

};

#endif  // FIELDMAP_H
