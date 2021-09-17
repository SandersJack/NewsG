
#include "IonDrift.hh"

#include "Garfield/AvalancheMC.hh"
#include "Garfield/DriftLineRKF.hh"
#include "Garfield/Sensor.hh"

IonDrift::IonDrift()
  :m_sensor(NULL),
   m_avalRKF(new Garfield::DriftLineRKF()),
   m_avalancheMC(new Garfield::AvalancheMC()),
   m_driftType(DriftType::RKF),
   m_doSignal(true),
   m_debug(0)
{
  m_avalRKF->SetSignalAveragingOrder(0.);
  m_avalRKF->EnableAvalanche(0);
}



IonDrift::~IonDrift()
{
  delete m_avalRKF;
  delete m_avalancheMC;
}



void IonDrift::SetSensor(Garfield::Sensor *sensor)
{
  m_sensor=sensor;
  m_avalRKF->SetSensor(m_sensor);
  m_avalancheMC->SetSensor(m_sensor);
}



void IonDrift::DriftIons(std::vector<ChargeCarrier>* ions)
{
  if(m_driftType==DriftType::RKF)
    {
      //No way to switch off signal calculation within DriftLineRKF it seems
      for(unsigned int kk=0;kk<ions->size();kk++)
	{
	  //drift the ions
          if(ions->at(kk).GetStatus() != 1){
	  ions->at(kk).SetPositionSphere(0, 0, 0, 0);
	  ions->at(kk).SetCharge(0.);
	  ions->at(kk).SetStatus(ions->at(kk).GetStatus());
	  continue;
	  } // check the electron successfully avalanched

	  m_avalRKF->SetIonSignalScalingFactor(ions->at(kk).GetCharge());

	  bool statusDrift=m_avalRKF->DriftIon(ions->at(kk).GetX(),ions->at(kk).GetY(),ions->at(kk).GetZ(),ions->at(kk).GetTime());
	  if(m_debug>=1)
	    {
	      std::cout << "avalRKF :: Drifting ion "<< kk+1 << " of "<< ions->size()
			<< " with scaling of " << ions->at(kk).GetCharge() <<" this had a drift time of "
			<< m_avalRKF->GetDriftTime()<<" status is " << statusDrift<<std::endl;
	    }
	  ions->at(kk).SetDriftTime(m_avalRKF->GetDriftTime());
	  m_avalRKF->SetIonSignalScalingFactor(1.);

	  int status = 1000;
	  double x,y,z,t;
	  m_avalRKF->GetEndPoint(x, y, z, t, status);

	  ions->at(kk).SetPositionCartesian(x, y, z, t);

	  //std::cout << "[IonDrift] Ion Endpoint is: x = " << ions->at(kk).GetX()
	  //    << ",\t y = " << ions->at(kk).GetY() << ",\t z = " << ions->at(kk).GetZ()
	  //	    << ",\t r = " << ions->at(kk).r() << ",\t t = " << ions->at(kk).GetTime()
	  //	    << ",\t status = " << status << std::endl;
	}
    }
  else
    {
      if(m_doSignal)
	m_avalancheMC->EnableSignalCalculation(1);
      else // <-- off by default in new Garfield
      	m_avalancheMC->EnableSignalCalculation(0);
      for(unsigned int kk=0;kk<ions->size();kk++)
	{
	  //drift the ions
          if(ions->at(kk).GetStatus() != 1){
	  ions->at(kk).SetPositionSphere(0, 0, 0, 0);
	  ions->at(kk).SetCharge(0.);
	  ions->at(kk).SetStatus(ions->at(kk).GetStatus());
	  continue;
	  } // check the electron successfully avalanched
	  //drift the ions
	  if(m_debug>=1)
	    {
	      std::cout << "avalMC :: Drifting ion "<< kk+1 << " of "<< ions->size()<<std::endl;
	    }
	  m_avalancheMC->DriftIon(ions->at(kk).GetX(),ions->at(kk).GetY(),ions->at(kk).GetZ(),ions->at(kk).GetTime());
	}
    }

  /**
  if(m_doSignal)
    {
      for(int ibin=0;ibin<signal_bins;ibin++)
	{
	  signalHistNt->Fill(ibin,allArea->GetIonSignal("readout",ibin));
	  signalNt[ibin]+=allArea->GetIonSignal("readout",ibin);
	  //std::cout<< "signal "<<ibin << " "<<allArea->GetIonSignal("readout",ibin)<< " "<<signalHistNt->GetBinContent(ibin)<<std::endl;
	}

      allArea->ClearSignal();
    }
  **/
}
