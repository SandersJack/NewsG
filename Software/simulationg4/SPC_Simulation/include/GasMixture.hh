#ifndef GASMIXTURE_H
#define GASMIXTURE_H

#include <string>
#include <iostream>

namespace Garfield {
  class MediumMagboltz;
}

class GasMixture {
public:
  GasMixture();
  ~GasMixture();

  void SetGas(std::string filename, double wValue = 0.0, double fanoFactor = 0.0, double pressure = 750.062);

  inline void SetIonMobilityDir(std::string filename){m_dirIonMob = filename;}
  inline void SetDebug(int level){m_debug = level;}

  inline std::string GetIonMobilityDir()       {return m_dirIonMob;}
  inline Garfield::MediumMagboltz* GetGas(){return m_gas;}

private:
  Garfield::MediumMagboltz* m_gas;
  std::string m_label;
  std::string m_dirIonMob;
  int m_debug;
};

#endif //GASMIXTURE_H
