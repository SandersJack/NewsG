#ifndef FIELDMAP_H
#define FIELDMAP_H

#include "MediumMagboltz.hh"
#include "ComponentAnsys121.hh"

#include <string>
#include <iostream>

class FieldMap {
 public:
  FieldMap();
  ~FieldMap();

  void Initialise();

  inline void SetGas(Garfield::MediumMagboltz* gas){delete m_gas; m_gas = gas;}
  inline void SetSensorDir(std::string sensorDir)      {m_sensorDir = sensorDir;}

  inline Garfield::ComponentAnsys121* GetFieldMap(){return m_ansysMap;}
  inline Garfield::MediumMagboltz* GetGas()        {return m_gas;}
  inline std::string GetSensorDir()                    {return m_sensorDir;}

  
 private:
  Garfield::ComponentAnsys121* m_ansysMap;
  Garfield::MediumMagboltz* m_gas;
  std::string m_sensorDir;

};

#endif //FIELDMAP_H
