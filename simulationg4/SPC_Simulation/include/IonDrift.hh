#ifndef IONDRIFT_H
#define IONDRIFT_H

#include <iostream>
#include <vector>

#include "ChargeCarrier.hh"

namespace Garfield {
class AvalancheMC;
class DriftLineRKF;
class Sensor;
}  // namespace Garfield

enum class DriftType  {RKF, MCdrift};

class IonDrift
{
public:
  IonDrift();
  ~IonDrift();
  inline void SetDriftType(DriftType type){m_driftType = type;}
  inline void SetDebug(int level)         {m_debug = level;}
  inline void EnableSignal() {m_doSignal = true;}
  inline void DisableSignal(){m_doSignal = false;}

  void SetSensor(Garfield::Sensor *sensor);
  void DriftIons(std::vector<ChargeCarrier>* ions);

private:
  Garfield::Sensor*       m_sensor;
  Garfield::DriftLineRKF* m_avalRKF;
  Garfield::AvalancheMC*  m_avalancheMC;
  DriftType               m_driftType;
  bool m_doSignal;
  int  m_debug;
};

#endif //IONDRIFT_H

/**
   TCanvas*c0=new TCanvas("c0","",600,600);
   ViewSignal* signalView = new ViewSignal();//signal_t0,signal_dt,signal_bins);
   signalView->SetSensor(allArea);
   signalView->SetCanvas(c0);
   signalView->PlotSignal("readout");
   TString plotname="signal_";
   plotname+=Form("%d",iEvents);
   file->WriteTObject(c0,plotname);
   plotname+=".png";
   c0->Print(plotname);
   delete c0;
**/
