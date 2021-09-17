#ifndef TRANSPORTPARAMETERS_H
#define TRANSPORTPARAMETERS_H

#include <iostream>
#include "TString.h"
//#include "Medium.hh"
#include "MediumMagboltz.hh"

class TransportParameters {
  
  public:
  // Constructor
  TransportParameters(Garfield::MediumMagboltz*pure, TString name);
  TransportParameters(Garfield::MediumMagboltz*pure,Garfield::MediumMagboltz*O2,Garfield::MediumMagboltz*H2O,TString name);
  // Destructor
  ~TransportParameters();

  void SetWaterFile(Garfield::MediumMagboltz* H2O){m_H2O = H2O;};
  void SetPureGasFile(Garfield::MediumMagboltz* pure){m_pure = pure;}
  
  double GetElectronTownsend(double electricField, double pressureBar, int impurityType);
  double GetElectronAttachment(double electricField, double pressureBar, int impurityType);
  double GetElectronAttachment(double electricField, double pressureBar, int impurityType, double O2ppm, double refPurity=50.);
  double GetElectronDriftVelocity(double electricField, double pressureBar, int impurityType);
  double GetElectronTransverseDiffusion(double electricField, double pressureBar, int impurityType);
  double GetElectronLongitudinalDiffusion(double electricField, double pressureBar, int impurityType);

private:
  Garfield::MediumMagboltz* m_pure;
  Garfield::MediumMagboltz* m_O2;
  Garfield::MediumMagboltz* m_H2O;
  TString m_label;
};


#endif
