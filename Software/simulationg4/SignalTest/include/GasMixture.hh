#ifndef GASMIXTURE_H
#define GASMIXTURE_H

#include "MediumMagboltz.hh"
#include <string>
#include <iostream>

class GasMixture {
public:
  GasMixture();
  ~GasMixture();

  void SetGas(std::string filename, double wValue = 0.0, double fanoFactor = 0.0, double pressure = 750.062);

  inline void SetIonMobilityDir(std::string filename){m_dirIonMob = filename;}
 
  inline std::string GetIonMobilityDir()       {return m_dirIonMob;}
  inline Garfield::MediumMagboltz* GetGas(){return m_gas;}
  
private:
  Garfield::MediumMagboltz* m_gas;
  std::string m_label;
  std::string m_dirIonMob;
};

#endif //GASMIXTURE_H
